//@	{
//@	"targets":
//@		[{
//@		 "name":"../happychords.so","type":"lib_dynamic"
//@		,"dependencies":
//@			[
//@				 {"ref":"lv2plug","rel":"external"}
//@				,{"ref":"../patterns/gallop_backwards.txt","rel":"file"}
//@			]
//@		}]
//@	}

#include <maike/targetinclude.hpp>
#include MAIKE_TARGET(../plugindescriptor.hpp)
#include "voice.hpp"
#include "sawtooth.hpp"
#include "sine.hpp"
#include "gatesequence.hpp"
#include "gate.hpp"
#include "../common/blob.hpp"
#include "ringbuffer.hpp"
#include "idgenerator.hpp"
#include <lv2plug/lv2plug.hpp>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>
#include <cmath>
#include <utility>
#include <algorithm>
#include <random>
#include <unistd.h>

using namespace Happychords;

static constexpr auto waveform=Happychords::sawtooth();
static constexpr auto waveform_lfo=Happychords::sine();

BLOB(pattern_init,"patterns/gallop_backwards.txt");

namespace
	{
	struct Features
		{
		static constexpr const char* content[]=
			{
			 LV2_MIDI__MidiEvent
			,LV2_ATOM__Blank
			,LV2_ATOM__Object
			,LV2_TIME__Position
			,LV2_TIME__beat
			,LV2_TIME__barBeat
			,LV2_TIME__beatsPerMinute
			,LV2_TIME__beatsPerBar
			,LV2_TIME__bar
			,LV2_ATOM__Float
			,LV2_ATOM__Long
			,LV2_TIME__speed
			};
		static constexpr size_t size() noexcept
			{return sizeof(content)/sizeof(const char*);}

		static constexpr const char* get(size_t k) noexcept
			{return content[k];}
		};
	constexpr const char* Features::content[];
	}

class PRIVATE Engine:public LV2Plug::Plugin<PluginDescriptor>
	{
	public:
		typedef Features FeatureRequest;

		Engine(double fs,const char* path_bundle
			,LV2Plug::FeatureDescriptor<FeatureRequest>&& features):
			 m_fs(fs),m_tempo(144.0),m_speed(0.0f),m_beat_old(0.0)
			,m_gate_seq(reinterpret_cast<const int8_t*>(pattern_init_begin)
				,reinterpret_cast<const int8_t*>(pattern_init_end))
			,m_gate(m_gate_seq,m_tempo,fs),m_features(features)
			{voice_alloc.fill();}

		void process(size_t n_frames) noexcept;

		static void* operator new(size_t size)
			{
			void* ret;
			if(posix_memalign(&ret,64,size))
				{throw "Bad malloc";}
			return ret;
			}

		static void operator delete(void* pointer)
			{free(pointer);}

	private:
		double m_fs;
		float m_tempo;
		float m_speed;
		double m_beat_old;

		double lfo_freq;
		FunctionGenerator<float,waveform_lfo.size()> LFO;
		ArrayStatic<float,64> buffer_lfo;
		ArrayStatic<Voice<waveform.size()>,16> voices;
		
		ArrayStatic<float,64> buffer_in;
		ArrayStatic<ArrayStatic<Framepair,32>,3> bufftemp;
		GateSequence m_gate_seq;
		Gate m_gate;

		IdGenerator< RingBuffer<uint8_t,decltype(voices)::size()> > voice_alloc;
		ArrayStatic<uint8_t,128> keys;
		LV2Plug::FeatureDescriptor<FeatureRequest> m_features;

		void generate(size_t n_frames) noexcept;
		void processEvents() noexcept;
		void voiceActivate(int8_t key,float amplitude) noexcept;
		void positionUpdate(const LV2_Atom_Object& obj) noexcept;
		void voiceDeactivate(int8_t key) noexcept;
		void lfoFreqUpdate() noexcept
			{
			lfo_freq=static_cast<double>(m_tempo)
				/(60.0*m_fs*static_cast<double>(portmap().get<Ports::LFO_PERIOD>()/12.0));
			}
	};

static float frequencyGet(float key) noexcept
	{
	return 440.0f*std::exp2((key - 69.0f)/12.0f);
	}

void Engine::voiceActivate(int8_t key,float amplitude) noexcept
	{
	auto id=voice_alloc.idGet();
	keys[key]=id;
	if(id==voice_alloc.id_null)
		{return;}
	voices[id].start(frequencyGet(key)/m_fs,amplitude
		,portmap().get<Ports::FILTER_KEYB>(),key);
	}

void Engine::voiceDeactivate(int8_t key) noexcept
	{
	auto id=keys[key];
	if(id==voice_alloc.id_null)
		{return;}
	voices[id].stop(key);
	keys[key]=voice_alloc.id_null;
	voice_alloc.idRelease(id);
	}

void Engine::processEvents() noexcept
	{
	auto midi_in=portmap().get<Ports::MIDI_IN>();
	if(midi_in==nullptr)
		{return;}

	LV2_Atom_Event* ev = lv2_atom_sequence_begin(&(midi_in->body));
	while(!lv2_atom_sequence_is_end(&(midi_in->body)
		,midi_in->atom.size,ev))
		{
		if(ev->body.type==m_features.get<LV2Plug::make_key(LV2_MIDI__MidiEvent)>())
			{
			const uint8_t* const msg=(const uint8_t*)(ev + 1);
			switch(lv2_midi_message_type(msg))
				{
				case LV2_MIDI_MSG_NOTE_ON:
					voiceActivate(msg[1],msg[2]/127.0f);
					break;

				case LV2_MIDI_MSG_NOTE_OFF:
					voiceDeactivate(msg[1]);
					break;
				default:
					break;
				}
			}
		else
		if(ev->body.type==m_features.get<LV2Plug::make_key(LV2_ATOM__Blank)>()
			|| ev->body.type==m_features.get<LV2Plug::make_key(LV2_ATOM__Object)>())
			{
			auto obj=reinterpret_cast<const LV2_Atom_Object*>(&ev->body);
			if(obj->body.otype==m_features.get<LV2Plug::make_key(LV2_TIME__Position)>())
				{positionUpdate(*obj);}
			}
		ev=lv2_atom_sequence_next(ev);
		}
	}

static inline bool make_bool(float value)
	{return value>0.0f;}

static Filter::Params filterSetup(float filter_base,float keytrack,float Q,double dt)
	{
	Filter::Params filter;
	filter.dt()=dt;
	filter.Q()=Q;
	auto omega_c=2.0f*std::acos(-1.0f)
		*440.0f*std::exp2((filter_base - (1.0f - keytrack)*69.0f)/12.0f);
	auto freq_factor=Q<1.0f/sqrt(2.0f)?sqrt(2.0f):2.0f*Q/std::sqrt(4.0f*Q*Q - 1.0f);
	filter.omega_0()=freq_factor*omega_c;
	return filter;
	}

void Engine::positionUpdate(const LV2_Atom_Object& obj) noexcept
	{
	LV2_Atom* bpm=nullptr;
	LV2_Atom* speed=nullptr;
	LV2_Atom* bar=nullptr;
	LV2_Atom* barbeat=nullptr;
	LV2_Atom* beatsperbar=nullptr;

	lv2_atom_object_get(&obj
		,m_features.get<LV2Plug::make_key(LV2_TIME__beatsPerMinute)>(),&bpm
		,m_features.get<LV2Plug::make_key(LV2_TIME__speed)>(),&speed
		,m_features.get<LV2Plug::make_key(LV2_TIME__bar)>(),&bar
		,m_features.get<LV2Plug::make_key(LV2_TIME__barBeat)>(),&barbeat
		,m_features.get<LV2Plug::make_key(LV2_TIME__beatsPerBar)>(),&beatsperbar
		,NULL);
	
	auto speed_val=1.0f;
	if(speed && speed->type==m_features.get<LV2Plug::make_key(LV2_ATOM__Float)>())
		{
		auto temp=reinterpret_cast<const LV2_Atom_Float*>(speed);
		static_assert(std::is_same<decltype(temp->body),decltype(m_tempo)>::value
			,"Speed has wrong type");
		speed_val=temp->body;
		}

	if(bpm && bpm->type==m_features.get<LV2Plug::make_key(LV2_ATOM__Float)>())
		{
		auto temp=reinterpret_cast<const LV2_Atom_Float*>(bpm);
		auto tempo=temp->body;
		static_assert(std::is_same<decltype(tempo),decltype(m_tempo)>::value
			,"Tempo has wrong type");
		if(tempo!=m_tempo)
			{
			m_tempo=tempo;
			lfoFreqUpdate();
			m_gate.timescaleSet(tempo,m_fs);
			}
		}

	if(barbeat && barbeat->type==m_features.get<LV2Plug::make_key(LV2_ATOM__Float)>()
		&& bar && bar->type==m_features.get<LV2Plug::make_key(LV2_ATOM__Long)>()
		&& beatsperbar && beatsperbar->type==m_features.get<LV2Plug::make_key(LV2_ATOM__Float)>())
		{

		auto beatval=reinterpret_cast<const LV2_Atom_Float*>(barbeat);
		auto barval=reinterpret_cast<const LV2_Atom_Long*>(bar);
		auto bpbval=reinterpret_cast<const LV2_Atom_Float*>(beatsperbar);

		auto beat=beatval->body + static_cast<double>(bpbval->body)
			*static_cast<double>(barval->body);

	//	Detect when to reposition LFO and gate cursors. Only update cursors
	//	when
	//		1. The head has moved backwards (This cannot be regular playback)
	//		2. Playback is stopped, and the position is updated
	//		3. The playback has started
	//		4. The head has moved an unexpected distance into the future
		if(beat<m_beat_old
			|| (speed_val!=1.0f && beat!=m_beat_old)
			|| (speed_val!=m_speed)
			|| (beat - m_beat_old > static_cast<double>(bpbval->body) ) )
			{
		//	Update positions
			m_gate.positionSet(beat);
		//	The LFO measure time in frames not beats. Fix this?
			LFO.phaseSet(m_fs*beat/(60.0*m_tempo),lfo_freq);
			}
		m_beat_old=beat;
		}


	m_speed=speed_val;
	}

void Engine::generate(size_t n_frames) noexcept
	{
	auto buffer_l=portmap().get<Ports::OUTPUT_L>();
	auto buffer_r=portmap().get<Ports::OUTPUT_R>();
	auto detune=portmap().get<Ports::VOICE_DETUNE>();
	auto suboct=make_bool( portmap().get<Ports::VOICE_SUBOCT>() );
	auto voice_adsr=Adsr::Params(m_fs
		,portmap().get<Ports::MAIN_ATTACK>()
		,portmap().get<Ports::MAIN_DECAY>()
		,portmap().get<Ports::MAIN_SUSTAIN>()
		,portmap().get<Ports::MAIN_RELEASE>());

	auto filter_adsr=AdsrScaler::Params(m_fs
		,std::exp2(portmap().get<Ports::FILTER_ENVELOPE>()/12.0f)
		,portmap().get<Ports::FILTER_ATTACK>()
		,portmap().get<Ports::FILTER_DECAY>()
		,portmap().get<Ports::FILTER_SUSTAIN>()
		,portmap().get<Ports::FILTER_RELEASE>());

	auto filter=filterSetup(portmap().get<Ports::FILTER_BASE>()
		,portmap().get<Ports::FILTER_KEYB>()
		,portmap().get<Ports::FILTER_RES>()
		,1.0/m_fs);
	auto filter_lfo=portmap().get<Ports::FILTER_LFO>()/12.0f;
	auto lfo_phase=waveform_lfo.size()*portmap().get<Ports::LFO_PHASE>();
	lfoFreqUpdate();
	auto main_gain=portmap().get<Ports::MAIN_GAIN>();
	auto gate_adsr=Adsr::Params(m_fs
		,portmap().get<Ports::GATE_ATTACK>()
		,portmap().get<Ports::GATE_DECAY>()
		,portmap().get<Ports::GATE_SUSTAIN>()
		,portmap().get<Ports::GATE_RELEASE>());

	memset(bufftemp[2].begin(),0,sizeof(bufftemp)/bufftemp.size());
	while(n_frames!=0)
		{
		auto n=std::min(n_frames,buffer_in.size());
		LFO.generate(lfo_freq,1.0f,lfo_phase,waveform_lfo,buffer_lfo.begin(),n);
		std::transform(buffer_lfo.begin(),buffer_lfo.end(),buffer_lfo.begin()
			,[filter_lfo](float x)
				{return std::exp2(x*filter_lfo);}
			);
		for(size_t k=0;k<voices.size();++k)
			{
			if(voices[k].amplitude()>1e-3f || voices[k].started())
				{
				memset(bufftemp[0].begin(),0,sizeof(bufftemp)/bufftemp.size());
				voices[k].generate(waveform
					,detune,suboct,buffer_in.begin(),bufftemp[0].begin(),n);
				voices[k].filterApply(bufftemp[0].begin(),filter,filter_adsr
					,buffer_lfo.begin(),bufftemp[1].begin(),n);
				voices[k].modulate(bufftemp[1].begin(),voice_adsr,bufftemp[0].begin(),n);
				
				addToMix(bufftemp[0].begin(),bufftemp[2].begin(),n);
				}
			}
		
		m_gate.modulate(bufftemp[2].begin(),gate_adsr,bufftemp[1].begin(),n);
		mix(bufftemp[2].begin(),bufftemp[1].begin(),portmap().get<Ports::GATE_DEPTH>()
			,bufftemp[1].begin(),n);

		std::transform(bufftemp[1].begin(),bufftemp[1].begin() + n/2,bufftemp[1].begin()
			,[main_gain](Framepair x)
				{return main_gain*x;}
			);
		demux(bufftemp[1].begin(),buffer_l,buffer_r,n);


		n_frames-=n;
		buffer_l+=n;
		buffer_r+=n;
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
