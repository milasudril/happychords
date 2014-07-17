#ifdef __WAND__
target[name[generator.o] type[object]]
#endif

#include "generator.h"
#include "waveform.h"
#include <herbs/include_binary/include_binary.h>

INCLUDE_BINARY(g_osc_phase_init,"phase_init_data.dat");

#include <cstdio>

namespace
	{
	class OscillatorInit
		{
		public:
			OscillatorInit(const uint32_t* phase_init_begin
				,const uint32_t* phase_init_end
				,const Happychords::Waveform& waveform):
				m_phase(phase_init_begin),m_phase_end(phase_init_end)
				,m_waveform(waveform.data),m_n_frames(waveform.n_frames)
				{}
			
			void operator()(Synthmod::Oscillator* v,size_t n,size_t N)
				{
				new(v)Synthmod::Oscillator(m_waveform,m_n_frames);
				if(m_phase!=m_phase_end)
					{
					v->phaseSet(*m_phase);
					++m_phase;
					}
				}
			
		private:
			const uint32_t* m_phase;
			const uint32_t* m_phase_end;
			const float* m_waveform;
			size_t m_n_frames;
		};
	}

Happychords::Generator::Generator(const Waveform& audio_waveform):
	sources(11,OscillatorInit(
		 (const uint32_t*)g_osc_phase_init_begin
		,(const uint32_t*)g_osc_phase_init_end
		,audio_waveform))
	,G(0),G_f(0),m_val(0)
	{
	fsSet(48000.0f);
	filterCutoffKeySet(63.0f);
	filterResonanceSet(2.0f);
	}

Vector::Vector2d<float> Happychords::Generator::operator()()
	{
	Vector::Vector2d<float> ret={0.0f,0.0f};
	auto source=sources.begin();
	int k=0;
	while(source!=sources.end())
		{
		float xi=float(k)/(sources.length()-1);
		auto val=(*source)();
	
		ret.x+=xi*val;
		ret.y+=(1.0f-xi)*val;
		++k;
		++source;
		}
	ret*=2.0f*m_val*G/sources.length();
	ret.x=filter_L(ret.x);
	ret.y=filter_R(ret.y);
	G=envelope(G);
	G_f=env_filter(G_f);
	return ret;
	}

void Happychords::Generator::play(int key,float value)
	{
	key_held=key;
	m_val=value;
	G=0.0f;
	G_f=0.0f;
	freqsUpdate();
	envelope.attack();
	env_filter.attack();
	}

void Happychords::Generator::freqsUpdate()
	{
	auto source=sources.begin();
	int k=0;
	while(source!=sources.end())
		{
		float xi=float(k)/(sources.length()-1);
		float key_offset=(xi-0.5f)*m_detune;
		float key=key_held-12*(k%2)*suboct + key_offset;
		source->frequencySet(Synthmod::keyToFrequency(key ,f_s));
		++source;
		++k;
		}
	}