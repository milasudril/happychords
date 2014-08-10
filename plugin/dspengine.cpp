#ifdef __WAND__
target[name[dspengine.o] type[object]]
#endif

#include "dspengine.h"
#include "waveform.h"
#include <herbs/include_binary/include_binary.h>
#include <herbs/memoryin/memoryin.h>

INCLUDE_BINARY(g_pattern_0,"plugin/pattern_0.mid");

namespace
	{
	class GeneratorInit
		{
		public:
			GeneratorInit(const Herbs::ArrayFixedsize<float>& waveform,float f_s):
				m_waveform(waveform),m_fs(f_s)
				{}

			void operator()(Happychords::Plugin::Generator* v,size_t n,size_t N) const
				{
				new(v)Happychords::Plugin::Generator({m_waveform.begin(),m_waveform.length()});
				v->fsSet(m_fs);
				}

		private:
			const Herbs::ArrayFixedsize<float>& m_waveform;
			float m_fs;
		};

	static const float lfo_period_default=12*16;
	}

Happychords::Plugin::DspEngine::DspEngine(double _f_s,const char* _path_bundle
	,const LV2Plug::FeatureDescriptor& _features):
	features(_features),f_s(_f_s)
	,waveform(64)
	,generators(8,GeneratorInit(waveform,_f_s))
	,waveform_LFO(64)
	,LFO(waveform_LFO.begin(),waveform_LFO.length())
	,gate_ctrl(gate)
	,midi_in(nullptr)
	,lfo_period(&lfo_period_default)
	{
	size_t k=0;
	auto sample=waveform.begin();
	while(sample!=waveform.end())
		{
		*sample=-1.0f*(1.0f -  k/63.0f) + 1.0f*k/63.0f;
		++k;
		++sample;
		}

	k=0;
	sample=waveform_LFO.begin();
	while(sample!=waveform_LFO.end())
		{
		*sample=cos(2*MathExt::PI*k/64.0f);
		++k;
		++sample;
		}

	Herbs::MemoryIn pattern_seq(g_pattern_0_begin
		,g_pattern_0_end-g_pattern_0_begin);
	pattern.load(pattern_seq);
	pattern.tracksMerge();
	gate_ctrl.sequenceSet(
		{
		 pattern.tracksBegin()->begin()
		,pattern.tracksBegin()->end()
		,pattern.timeDivisionGet()
		,pattern.lengthGet()
		});
	tempo=120;
	tempoUpdate();
//	LFO.dump();
	}


void Happychords::Plugin::DspEngine::portConnect(uint32_t port,void* data)
	{
	switch(port)
		{
		case 0:
			midi_in=(const LV2_Atom_Sequence*)data;
			break;
		case 1:
			output_L=(float*)data;
			break;
		case 2:
			output_R=(float*)data;
			break;

		case 3:
			choir_detune=(const float*)data;
			break;
		case 4:
			choir_suboct=(const float*)data;
			break;

		case 5:
			lfo_period=(const float*)data;
			break;
		case 6:
			lfo_phase=(const float*)data;
			break;

		case 7:
			filter_cutoff=(const float*)data;
			break;
		case 8:
			filter_env=(const float*)data;
			break;
		case 9:
			filter_attack=(const float*)data;
			break;
		case 10:
			filter_decay=(const float*)data;
			break;
		case 11:
			filter_sustain=(const float*)data;
			break;
		case 12:
			filter_release=(const float*)data;
			break;
		case 13:
			filter_lfodepth=(const float*)data;
			break;
		case 14:
			filter_keysense=(const float*)data;
			break;
		case 15:
			filter_resonance=(const float*)data;
			break;

		case 16:
			choir_attack=(const float*)data;
			break;
		case 17:
			choir_decay=(const float*)data;
			break;
		case 18:
			choir_sustain=(const float*)data;
			break;
		case 19:
			choir_release=(const float*)data;
			break;

		case 20:
			gate_attack=(const float*)data;
			break;
		case 21:
			gate_decay=(const float*)data;
			break;
		case 22:
			gate_sustain=(const float*)data;
			break;
		case 23:
			gate_release=(const float*)data;
			break;
		case 24:
			gate_depth=(const float*)data;
			break;
		}
	}

void Happychords::Plugin::DspEngine::process(uint32_t n_frames)
	{
	if(!midi_in)
		{
		/* eg. ARDOUR::LV2Plugin::latency_compute_run()
		* -> midi ports are not yet connected
		*/
		return;
		}

	parametersUpdate();

	/* process events on the midi_in port */
	LV2_Atom_Event* ev = lv2_atom_sequence_begin(&(midi_in->body));
	while(!lv2_atom_sequence_is_end(&(midi_in->body)
		,midi_in->atom.size,ev))
		{
		if(ev->body.type==features.midi())
			{
			const uint8_t* const msg=(const uint8_t*)(ev + 1);
			switch(lv2_midi_message_type(msg))
				{
				case LV2_MIDI_MSG_NOTE_ON:
					noteStart(msg[1],msg[2]);
					break;
				case LV2_MIDI_MSG_NOTE_OFF:
					noteStop(msg[1]);
					break;
				default:
					break;
				}
			}
		else
		if(ev->body.type==features.AtomBlank()
			|| ev->body.type==features.AtomObject())
			{
			const LV2_Atom_Object* obj = (LV2_Atom_Object*)&ev->body;
			if (obj->body.otype == features.position())
				{positionUpdate(*obj);}
			}
		else
			{printf("I do not know what type %d is\n",ev->body.type);}

		ev = lv2_atom_sequence_next(ev);
		}

	auto L=output_L;
	auto R=output_R;
	while(n_frames)
		{
		auto v_gate=gate();
		auto v_gen=generatorsMix();
		auto v_out=(v_gate * (*gate_depth) + (1.0f-*gate_depth))*v_gen;
		*L=v_out.x;
		*R=v_out.y;
		++L;
		++R;
		gate_ctrl();
		--n_frames;
		}
	}

void Happychords::Plugin::DspEngine::parametersUpdate()
	{
	auto generator=generators.begin();
	while(generator!=generators.end())
		{
		generator->attackSet(*choir_attack);
		generator->decaySet(*choir_decay);
		generator->sustainSet(*choir_sustain);
		generator->releaseSet(*choir_release);
		generator->detune(*choir_detune);
		generator->suboctSet(*choir_suboct > 0.5f);
		generator->filterResonanceSet(*filter_resonance);
		generator->filterAttackSet(*filter_attack);
		generator->filterDecaySet(*filter_decay);
		generator->filterSustainSet(*filter_sustain);
		generator->filterReleaseSet(*filter_release);
		generator->filterEnvSet(*filter_env);
		generator->filterKeysenseSet(*filter_keysense);
		++generator;
		}
	tempoUpdate();
	gate.attackSet(*gate_attack,f_s);
	gate.decaySet(*gate_decay,f_s);
	gate.sustainSet(*gate_sustain);
	gate.releaseSet(*gate_release,f_s);
	}

void Happychords::Plugin::DspEngine::noteStart(int key,int velocity)
	{
	auto generator=generators.begin();

	while(generator!=generators.end())
		{
		if(generator->released())
			{break;}
		++generator;
		}
	if(generator==generators.end())
		{return;}

	auto amp_min=generator->amplitude();
	auto generator_sel=generator;

	while(generator!=generators.end())
		{
		auto amp=generator->amplitude();
		if(generator->released() && amp<amp_min)
			{
			generator_sel=generator;
			amp_min=amp;
			}
		++generator;
		}
	generator_sel->play(key,velocity/127.0f);
	}

void Happychords::Plugin::DspEngine::noteStop(int key)
	{
	auto generator=generators.begin();
	while(generator!=generators.end())
		{
		generator->keyRelease(key);
		++generator;
		}
	}

Vector::Vector2d<float> Happychords::Plugin::DspEngine::generatorsMix()
	{
	Vector::Vector2d<float> sum={0.0f,0.0f};
	auto generator=generators.begin();
	while(generator!=generators.end())
		{
		auto key_c=LFO()*(*filter_lfodepth) + (*filter_cutoff);
		generator->filterCutoffKeySet(key_c);
		sum+=(*generator)();
		++generator;
		}
	return sum;
	}

void Happychords::Plugin::DspEngine::tempoUpdate()
	{
	auto f=tempo/(10.0f * (*lfo_period) );
	LFO.frequencySet(f/f_s);
	gate_ctrl.tempoSet(tempo,f_s);
	}

void Happychords::Plugin::DspEngine::positionUpdate(const LV2_Atom_Object& obj)
	{
// Received new transport position/speed
	LV2_Atom* beat =nullptr;
	LV2_Atom* bpm = nullptr;
	LV2_Atom* speed = nullptr;
	LV2_Atom* fps = nullptr;
	LV2_Atom* frame = nullptr;

	lv2_atom_object_get(&obj
		,features.Beat(), &beat
		,features.beatsPerMinute(), &bpm
		,features.speed(), &speed
		,features.frame(), &frame
		,features.fps(), &fps
		,NULL);

	if (bpm && bpm->type == features.Float())
		{
		auto temp=(LV2_Atom_Float*)bpm;
		tempo=temp->body;
		tempoUpdate();
		}

	if(frame && frame->type == features.Long())
		{
		auto temp=(LV2_Atom_Long*)frame;
		gate_ctrl.positionSet(temp->body);
		LFO.phaseSet(temp->body,*lfo_phase);
		}
	}