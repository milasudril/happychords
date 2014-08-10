#ifdef __WAND__
target[name[generator.h] type[include]]
dependency[generator.o]
#endif

#ifndef HAPPYCHORDS_PLUGIN_GENERATOR_H
#define HAPPYCHORDS_PLUGIN_GENERATOR_H

#include <vector/vector2d.h>
#include <synthmod/oscillator.h>
#include <synthmod/utilities.h>
#include <synthmod/filter_adsr.h>
#include <synthmod/filter_adsr_linear.h>
#include <synthmod/filter_lp2.h>
#include <mathext/constants.h>
#include <herbs/array_fixedsize/array_fixedsize.h>

namespace Happychords
	{
	namespace Plugin
		{
		struct Waveform;

		class Generator
			{
			public:
				Generator(const Waveform& audio_waveform);

				Vector::Vector2d<float> operator()();

				void play(int key,float value);

				bool keyRelease(int key)
					{
					if(key==key_held)
						{
						envelope.release();
						env_filter.release();
						return 1;
						}
					return 0;
					}

				bool released() const
					{return envelope.stateGet()==envelope.State::RELEASE;}

				float amplitude() const
					{return m_val*G;}

				void fsSet(float f_s_new)
					{
					f_s=f_s_new;
					filter_L.dtSet(1.0f/f_s);
					filter_R.dtSet(1.0f/f_s);
					}


			//	Choir ops
				void sourceDump() const
					{sources[0].dump();}

				void detune(float detune)
					{
					m_detune=detune;
					freqsUpdate();
					}

				void suboctSet(bool state_new)
					{suboct=state_new?1.0f:0.0f;}


			//	Filter ops
				void filterCutoffKeySet(float key_c)
					{
					auto f_c=Synthmod::keyToFrequency(key_c + env*G_f + keysense*key_held
						,1.0f);
					auto omega=2*f_c*MathExt::PI;
					filter_L.frequencySet(omega);
					filter_R.frequencySet(omega);
					}

				void filterEnvSet(float value)
					{
					env=value;
					}

				void filterKeysenseSet(float value)
					{keysense=value;}

				void filterAttackSet(float time)
					{env_filter.A=time*f_s;}

				void filterDecaySet(float time)
					{env_filter.D=time*f_s;}

				void filterSustainSet(float value)
					{env_filter.S=value;}

				void filterReleaseSet(float time)
					{env_filter.R=time*f_s;}

				void filterResonanceSet(float Q)
					{
					filter_L.qualitySet(Q);
					filter_R.qualitySet(Q);
					}



			//	Envelope ops
				void attackSet(float time)
					{envelope.A=time*f_s;}

				void decaySet(float time)
					{envelope.D=time*f_s;}

				void sustainSet(float value)
					{envelope.S=value;}

				void releaseSet(float time)
					{envelope.R=time*f_s;}


			private:
				Herbs::ArrayFixedsize<Synthmod::Oscillator> sources;
				Synthmod::FilterAdsr envelope;
				Synthmod::FilterAdsrLinear env_filter;
				Synthmod::FilterLp2 filter_L;
				Synthmod::FilterLp2 filter_R;
				float f_s;
				int key_held;
				float G;
				float G_f;
				float env;
				float keysense;
				float m_val;
				float m_detune;
				float suboct;

			//	Helper functions
				void freqsUpdate();
			};
		}
	}

#endif

