//@	{
//@	"targets":
//@		[{
//@		 "name":"happychords2.so","type":"lib_dynamic"
//@		,"dependencies":
//@			[
//@				 {"ref":"lv2plug","rel":"external"}
//@			]
//@		}]
//@	}


#include <maike/targetinclude.hpp>
#include MAIKE_TARGET(plugindescriptor.hpp)
#include "blob.hpp"
#include "functiongenerator.hpp"
#include "sawtooth.hpp"
#include <lv2plug/lv2plug.hpp>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <cmath>
#include <utility>
#include <algorithm>
#include <random>

using namespace Happychords;


static constexpr auto waveform=Happychords::sawtooth();

template<size_t N>
using GeneratorArray=ArrayStatic<FunctionGenerator<float,waveform.size()>,N>;

class PRIVATE Engine:public LV2Plug::Plugin<PluginDescriptor>
	{
	public:
		Engine(double fs,const char* path_bundle
			,LV2Plug::FeatureDescriptor&& features):m_features(features)
			,m_fs(fs),m_amplitude(0),m_key(0)
			{
			std::random_device rd;
			std::uniform_real_distribution<double> U(0,waveform.size());
			for(size_t k=0;k<generators.size();++k)
				{generators[k].phaseSet(U(rd));}
			}

		void process(size_t n_frames) noexcept;

	private:
		LV2Plug::FeatureDescriptor m_features;
		double m_fs;
		float m_amplitude;
		uint8_t m_key;
		GeneratorArray<11> generators;
		ArrayStatic<ArrayStatic<float,64>,4> bufftemp;
		void generate(size_t n_frames) noexcept;
		void processEvents() noexcept;
	};

static float frequencyGet(float key) noexcept
	{
	return 440.0f*std::exp2((key - 69.0f)/12.0f);
	}

static void addToMix(const float* src,float scale_factor,float xi
	,float* buffer_left,float* buffer_right
	,size_t n)
	{
	auto xi_comp=1.0f - xi;
	while(n!=0)
		{
		auto v=*src;
		*buffer_left+=xi_comp*v/scale_factor;
		*buffer_right+=xi*v/scale_factor;
		++buffer_left;
		++buffer_right;
		++src;
		--n;
		}
	}

static void voiceGenerate(GeneratorArray<11>& generators,double f_base
	,double detune,float a,bool suboct,float* buffer_temp,float* buffer_left
	,float* buffer_right,size_t n)
	{
	static_assert(generators.size()!=0,"No generators?");

	auto d_xi=1.0/(generators.size() - 1);
	auto df=std::exp2(detune*d_xi/12.0);
	auto f_0=exp2(-0.5*detune/12.0);
	f_base*=f_0;

	if(suboct)
		{
		for(size_t k=0;k<generators.size();++k)
			{
			generators[k].generate(k%2?0.5f*f_base:f_base,a,waveform,buffer_temp,n);
			f_base*=df;
			addToMix(buffer_temp,generators.size(),k*d_xi,buffer_left,buffer_right,n);
			}
		}
	else
		{
		for(size_t k=0;k<generators.size();++k)
			{
			generators[k].generate(f_base,a,waveform,buffer_temp,n);
			f_base*=df;
			addToMix(buffer_temp,generators.size(),k*d_xi,buffer_left,buffer_right,n);
			}
		}
	}

static inline bool make_bool(float value)
	{return value>0.0f;}

void Engine::generate(size_t n_frames) noexcept
	{
	auto buffer_l=portmap().get<Ports::OUTPUT_L>();
	auto buffer_r=portmap().get<Ports::OUTPUT_R>();
	auto detune=portmap().get<Ports::VOICE_DETUNE>();
	auto suboct=make_bool( portmap().get<Ports::VOICE_SUBOCT>() );

	memset(buffer_l,0,sizeof(*buffer_l)*n_frames);
	memset(buffer_r,0,sizeof(*buffer_l)*n_frames);

	auto f=frequencyGet(m_key)/m_fs;
	auto a=m_amplitude;

	while(n_frames!=0)
		{
		auto n=std::min(n_frames,bufftemp[0].size());
		voiceGenerate(generators,f,detune,a,suboct,bufftemp[0].begin()
			,buffer_l,buffer_r,n);


		n_frames-=n;
		buffer_l+=n;
		buffer_r+=n;
		}
	}

void Engine::processEvents()noexcept
	{
	auto midi_in=portmap().get<Ports::MIDI_IN>();
	if(midi_in==nullptr)
		{return;}

	LV2_Atom_Event* ev = lv2_atom_sequence_begin(&(midi_in->body));
	while(!lv2_atom_sequence_is_end(&(midi_in->body)
		,midi_in->atom.size,ev))
		{
		if(ev->body.type==m_features.midi())
			{
			const uint8_t* const msg=(const uint8_t*)(ev + 1);
			switch(lv2_midi_message_type(msg))
				{
				case LV2_MIDI_MSG_NOTE_ON:
					m_key=msg[1];
					m_amplitude=msg[2]/127.0f;
					break;

				case LV2_MIDI_MSG_NOTE_OFF:
					if(m_key==msg[1])
						{m_amplitude=0.0f;}
					break;

				default:
					break;
				}
			}
		ev = lv2_atom_sequence_next(ev);
		}
}


void Engine::process(size_t n_frames) noexcept
	{
	processEvents();
	generate(n_frames);
	}


const LV2_Descriptor& LV2Plug::main()
	{
	return LV2Plug::descriptorGet<Engine>();
	}