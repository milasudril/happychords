#ifdef __WAND__
target[name[client.h] type[include]]
dependency[client.o]
#endif

#ifndef HAPPYCHORDS_CLIENT_H
#define HAPPYCHORDS_CLIENT_H

#include "generator.h"
#include "gate.h"
#include "gatecontrolloop.h"
#include <lv2plug/feature_descriptor.h>
#include <mustudio/midi_sequence.h>
#include <mustudio/midi_event.h>
#include <herbs/array_fixedsize/array_fixedsize.h>
#include <lv2/lv2plug.in/ns/ext/atom/atom.h>
#include <lv2/lv2plug.in/ns/ext/atom/util.h>
#include <lv2/lv2plug.in/ns/ext/midi/midi.h>

namespace Happychords
	{
	class Client
		{
		public:
			static constexpr const char* URI="http://example.org/happychords";
			
			static Client* create(double f_s,const char* path_bundle
				,const LV2Plug::FeatureDescriptor& features)
				{
				return new Client(f_s,path_bundle,features);
				}
			
			void destroy()
				{delete this;}
			
			void portConnect(uint32_t port,void* data);

			void activate()
				{}
				
			void deactivate()
				{}
				
			void process(uint32_t n_frames);

			static const void* extensionDataGet(const char* uri)
				{return nullptr;}
				
		private:
			Client(double _f_s,const char* _path_bundle
				,const LV2Plug::FeatureDescriptor& _features);
			
		//	Resources
			LV2Plug::FeatureDescriptor features;
			double f_s;
			double tempo;
			MuStudio::MIDI::Sequence pattern;
			Herbs::ArrayFixedsize<float> waveform;
			Herbs::ArrayFixedsize<Generator> generators;
			Herbs::ArrayFixedsize<float> waveform_LFO;
			Synthmod::Oscillator LFO;
			Gate gate;
			GateControlLoop gate_ctrl;			
			
		//	Ports
			const LV2_Atom_Sequence* midi_in;
			float* output_L;
			float* output_R;
			const float* choir_detune;
			const float* choir_suboct;
			const float* lfo_period;
			const float* lfo_phase;
			
			const float* filter_cutoff;
			const float* filter_env;
			const float* filter_attack;
			const float* filter_decay;
			const float* filter_sustain;
			const float* filter_release;
			const float* filter_lfodepth;
			const float* filter_resonance;
			
			const float* choir_attack;
			const float* choir_decay;
			const float* choir_sustain;
			const float* choir_release;
			
			const float* gate_attack;
			const float* gate_decay;
			const float* gate_sustain;
			const float* gate_release;
			const float* gate_depth;
			
		
		//	Helper functions
			void parametersUpdate();	
			void noteStart(int key,int velocity);
			void noteStop(int note);
			void positionUpdate(const LV2_Atom_Object& obj);
			Vector::Vector2d<float> generatorsMix();
			void tempoUpdate();
		};
	}

#endif
