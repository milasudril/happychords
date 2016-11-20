//@	{
//@	"targets":
//@		[{
//@		 "name":"../happychords-gtk.so","type":"lib_dynamic"
//@		,"dependencies":
//@			[
//@				 {"ref":"lv2plug_ui","rel":"external"}
//@				,{"ref":"background.png","rel":"generated"}
//@			]
//@		,"pkgconfig_libs":["gtk+-2.0"]
//@		}]
//@	}

#include "container.hpp"
#include <maike/targetinclude.hpp>
#include MAIKE_TARGET(../plugindescriptor.hpp)
#include "../common/blob.hpp"
#include "knob.hpp"
#include "switch.hpp"
#include "box.hpp"
#include "panel.hpp"
#include "stringchoice.hpp"
#include "imageresource.hpp"
#include "cairocontext.hpp"

#include <lv2plug/lv2plug_ui.hpp>
#include <gtk/gtk.h>
#include <cmath>
#include <algorithm>

using namespace Happychords;

static const glm::vec3 COLOR_KNOB={77.3e-2, 35.7e-2, 95.3e-2};
static const glm::vec3 COLOR_BG={97.6e-2, 33.3e-2, 65.9e-2};
static const glm::vec3 COLOR_TEXT={0,0,0};
static const glm::vec3 COLOR_ENTRY{84.7e-2, 99.2e-2, 60e-2};

BLOB(background,MAIKE_TARGET(background.png));

auto bg=imageResourceLoad(background_begin,background_end);

static gboolean draw_stuff(GtkWidget *widget, GdkEventExpose *event, gpointer data)
	{
	auto context=CairoContext(gdk_cairo_create(gtk_widget_get_window (widget)));
	cairo_set_source_rgb(context,COLOR_BG.r,COLOR_BG.g,COLOR_BG.b);
	cairo_paint(context);
	cairo_set_source_surface(context,bg,0,0);
	cairo_set_operator(context,CAIRO_OPERATOR_ADD);
	cairo_paint(context);
	return FALSE;
	}

class PRIVATE UIBase:public Container
	{
	public:
		UIBase()
			{
			auto plugincontainer=reinterpret_cast<GtkContainer*>(gtk_event_box_new());
			gtk_widget_set_app_paintable(reinterpret_cast<GtkWidget*>(plugincontainer),TRUE);
			g_signal_connect(plugincontainer,"expose_event",G_CALLBACK(draw_stuff),NULL);
			m_container=plugincontainer;
			}

		~UIBase()
			{
			gtk_widget_destroy(reinterpret_cast<GtkWidget*>(m_container));
			}

		void* widgetGet() noexcept
			{return m_container;}

		UIBase& widgetAdd(void* widget)
			{
			gtk_container_add(m_container,reinterpret_cast<GtkWidget*>(widget));
			gtk_container_set_border_width(reinterpret_cast<GtkContainer*>(widget),8);
			return *this;
			}

	private:
		GtkContainer* m_container;
	};

static void styleSet(Happychords::Panel& panel)
	{
	panel.borderColorSet(COLOR_KNOB);
	panel.captionColorSet(COLOR_TEXT);
	}

static void styleSet(Happychords::KnobBase& knob)
	{
	knob.colorSet(COLOR_KNOB);
	knob.captionColorSet(COLOR_TEXT);
	knob.entryBackgroundSet(COLOR_ENTRY);
	knob.entryForegroundSet(COLOR_TEXT);
	}

static void styleSet(Happychords::SwitchBase& sw)
	{
	sw.backgroundSet(COLOR_BG);
	sw.captionColorSet(COLOR_TEXT);
	}

class PRIVATE UIGtk:public LV2Plug::PluginUI<PluginDescriptor>,private UIBase
	{
	public:
		using UIBase::widgetGet;

		UIGtk(const char* path_bundle,LV2Plug::UIController&& controller
			,LV2Plug::FeatureDescriptor&& descriptor):Base(controller)
			,m_controls(*this,1)
				,m_osc(m_controls.paddingSet(8),0)
					,m_voice(m_osc.paddingSet(8),"Voice")
						,m_voice_box(m_voice.paddingSet(4))
							,m_detune(m_voice_box,*this)
							,m_suboct(m_voice_box,*this)
					,m_lfo(m_osc,"LFO")
						,m_lfo_box(m_lfo.paddingSet(4))
							,m_lfo_period(m_lfo_box,*this)
							,m_lfo_phase(m_lfo_box,*this)
				,m_filter(m_controls.paddingSet(16),0)
					,m_fc_env(m_filter.paddingSet(8),"Cutoff envelope")
						,m_fc_env_box(m_fc_env.paddingSet(4),1)
							,m_filter_attack(m_fc_env_box,*this)
							,m_filter_decay(m_fc_env_box,*this)
							,m_filter_sustain(m_fc_env_box,*this)
							,m_filter_release(m_fc_env_box,*this)
					,m_fc_mix(m_filter,"Cutoff mixer")
						,m_fc_mix_box(m_fc_mix.paddingSet(4),1)
							,m_filter_base(m_fc_mix_box,*this)
							,m_filter_lfo(m_fc_mix_box,*this)
							,m_filter_env(m_fc_mix_box,*this)
							,m_filter_keyb(m_fc_mix_box,*this)
					,m_res_box(m_filter,1)
						,m_filter_res(m_res_box.paddingSet(4),*this)
					//	,m_foo(m_res_box.insertModeSet(Box::InsertMode::FILL),"Decoration/Graph")
						,m_foo(m_res_box.insertModeSet(Box::InsertMode::FILL),1)
				,m_main(m_controls.paddingSet(8),0)
					,m_main_box(m_main.paddingSet(8),1)
						,m_main_env(m_main_box.paddingSet(4),"Envelope")
							,m_main_env_box(m_main_env.paddingSet(4),1)
								,m_main_attack(m_main_env_box.insertModeSet(Box::InsertMode::EXPAND),*this)
								,m_main_decay(m_main_env_box,*this)
								,m_main_sustain(m_main_env_box,*this)
								,m_main_release(m_main_env_box,*this)
						,m_main_gain_box(m_main_box,0)
							,m_main_gain(m_main_gain_box.paddingSet(4),*this)
					,m_gate(m_main,"Gate")
						,m_gate_box(m_gate.paddingSet(4))
							,m_gate_row(m_gate_box.paddingSet(4),1)
								,m_gate_attack(m_gate_row.paddingSet(4).insertModeSet(Box::InsertMode::EXPAND),*this)
								,m_gate_decay(m_gate_row,*this)
								,m_gate_sustain(m_gate_row,*this)
								,m_gate_release(m_gate_row,*this)
								,m_gate_depth(m_gate_row,*this)
						//	,m_gate_pattern(m_gate_box,*this)

			{
			styleSet(m_voice);
			styleSet(m_lfo);
			styleSet(m_fc_env);
			styleSet(m_fc_mix);
			styleSet(m_main_env);
			styleSet(m_gate);
	
			styleSet(m_detune);
			styleSet(m_lfo_period);
			styleSet(m_lfo_phase);
			styleSet(m_filter_attack);
			styleSet(m_filter_decay);
			styleSet(m_filter_sustain);
			styleSet(m_filter_release);
			styleSet(m_filter_base);
			styleSet(m_filter_lfo);
			styleSet(m_filter_env);
			styleSet(m_filter_keyb);
			styleSet(m_filter_res);
			styleSet(m_main_attack);
			styleSet(m_main_decay);
			styleSet(m_main_sustain);
			styleSet(m_main_release);
			styleSet(m_main_gain);
			styleSet(m_gate_attack);
			styleSet(m_gate_decay);
			styleSet(m_gate_sustain);
			styleSet(m_gate_release);
			styleSet(m_gate_depth);
	
			styleSet(m_suboct);
			char buffer[4096];
			printf("%s\n",getcwd(buffer,4096));
			fflush(stdout);
			}

		~UIGtk()
			{}



		void detuneUpdate(float value)
			{m_detune.valueSet(value);}

		template<unsigned int port_id>
		void eventProcess(KnobBase& knob)
			{portWrite<port_id>(knob.valueGet());}

		void suboctUpdate(SwitchBase::State state)
			{m_suboct.stateSet(state);}

		template<unsigned int port_id>
		void eventProcess(SwitchBase& sw)
			{portWrite<port_id>(sw.stateGet()==SwitchBase::State::UP?0.0f:1.0f);}

		template<unsigned int port_id>
		void eventProcess(StringchoiceBase& choice)
			{}

		void lfoPeriodUpdate(float value)
			{m_lfo_period.valueSet(value);}

		void lfoPhaseUpdate(float value)
			{m_lfo_phase.valueSet(value);}

		
		void filterAttackUpdate(float value)
			{m_filter_attack.valueSet(value);}

		void filterDecayUpdate(float value)
			{m_filter_decay.valueSet(value);}

		void filterSustainUpdate(float value)
			{m_filter_sustain.valueSet(value);}

		void filterReleaseUpdate(float value)
			{m_filter_release.valueSet(value);}


		void filterBaseUpdate(float value)
			{m_filter_base.valueSet(value);}

		void filterLFOUpdate(float value)
			{m_filter_lfo.valueSet(value);}

		void filterEnvUpdate(float value)
			{m_filter_env.valueSet(value);}

		void filterKeybUpdate(float value)
			{m_filter_keyb.valueSet(value);}

		void filterResUpdate(float value)
			{m_filter_res.valueSet(value);}


		void mainAttackUpdate(float value)
			{m_main_attack.valueSet(value);}

		void mainDecayUpdate(float value)
			{m_main_decay.valueSet(value);}

		void mainSustainUpdate(float value)
			{m_main_sustain.valueSet(value);}

		void mainReleaseUpdate(float value)
			{m_main_release.valueSet(value);}


		void gateAttackUpdate(float value)
			{m_gate_attack.valueSet(value);}

		void gateDecayUpdate(float value)
			{m_gate_decay.valueSet(value);}

		void gateSustainUpdate(float value)
			{m_gate_sustain.valueSet(value);}

		void gateReleaseUpdate(float value)
			{m_gate_release.valueSet(value);}

		void gateDepthUpdate(float value)
			{m_gate_depth.valueSet(value);}


		void mainGainUpdate(float value)
			{m_main_gain.valueSet(value);}


	private:
		Box m_controls;
			Box m_osc;
				Panel m_voice;
					Box m_voice_box;
						Knob< Port<Ports::VOICE_DETUNE>,UIGtk > m_detune;
						Switch< Port<Ports::VOICE_SUBOCT>,UIGtk> m_suboct;
				Panel m_lfo;
					Box m_lfo_box;
						Knob< Port<Ports::LFO_PERIOD>,UIGtk > m_lfo_period;
						Knob< Port<Ports::LFO_PHASE>,UIGtk > m_lfo_phase;
			Box m_filter;
				Panel m_fc_env;
					Box m_fc_env_box;
						Knob< Port<Ports::FILTER_ATTACK>,UIGtk> m_filter_attack;
						Knob< Port<Ports::FILTER_DECAY>,UIGtk> m_filter_decay;
						Knob< Port<Ports::FILTER_SUSTAIN>,UIGtk> m_filter_sustain;
						Knob< Port<Ports::FILTER_RELEASE>,UIGtk> m_filter_release;
				Panel m_fc_mix;
					Box m_fc_mix_box;
						Knob< Port<Ports::FILTER_BASE>,UIGtk> m_filter_base;
						Knob< Port<Ports::FILTER_LFO>,UIGtk> m_filter_lfo;
						Knob< Port<Ports::FILTER_ENVELOPE>,UIGtk> m_filter_env;
						Knob< Port<Ports::FILTER_KEYB>,UIGtk> m_filter_keyb;
				Box m_res_box;
					Knob< Port<Ports::FILTER_RES>,UIGtk> m_filter_res;
					Box m_foo;
			Box m_main;
				Box m_main_box;
					Panel m_main_env;
						Box m_main_env_box;
							Knob< Port<Ports::MAIN_ATTACK>,UIGtk> m_main_attack;
							Knob< Port<Ports::MAIN_DECAY>,UIGtk> m_main_decay;
							Knob< Port<Ports::MAIN_SUSTAIN>,UIGtk> m_main_sustain;
							Knob< Port<Ports::MAIN_RELEASE>,UIGtk> m_main_release;
					Box m_main_gain_box;
						Knob< Port<Ports::MAIN_GAIN>,UIGtk > m_main_gain;
				Panel m_gate;
					Box m_gate_box;
						Box m_gate_row;
							Knob< Port<Ports::GATE_ATTACK>,UIGtk> m_gate_attack;
							Knob< Port<Ports::GATE_DECAY>,UIGtk> m_gate_decay;
							Knob< Port<Ports::GATE_SUSTAIN>,UIGtk> m_gate_sustain;
							Knob< Port<Ports::GATE_RELEASE>,UIGtk> m_gate_release;
							Knob< Port<Ports::GATE_DEPTH>,UIGtk> m_gate_depth;
					//	Stringchoice< Port<Ports::GATE_PATTERN>,UIGtk> m_gate_pattern;
	};

template<>
void update<UIGtk::Ports::VOICE_DETUNE>(UIGtk& ui,float value)
	{ui.detuneUpdate(value);}

template<>
void update<UIGtk::Ports::VOICE_SUBOCT>(UIGtk& ui,float value)
	{ui.suboctUpdate(value>0.0f?SwitchBase::State::DOWN:SwitchBase::State::UP);}

template<>
void update<UIGtk::Ports::LFO_PERIOD>(UIGtk& ui,float value)
	{ui.lfoPeriodUpdate(value);}

template<>
void update<UIGtk::Ports::LFO_PHASE>(UIGtk& ui,float value)
	{ui.lfoPhaseUpdate(value);}



template<>
void update<UIGtk::Ports::FILTER_ATTACK>(UIGtk& ui,float value)
	{ui.filterAttackUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_DECAY>(UIGtk& ui,float value)
	{ui.filterDecayUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_SUSTAIN>(UIGtk& ui,float value)
	{ui.filterSustainUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_RELEASE>(UIGtk& ui,float value)
	{ui.filterReleaseUpdate(value);}



template<>
void update<UIGtk::Ports::FILTER_BASE>(UIGtk& ui,float value)
	{ui.filterBaseUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_LFO>(UIGtk& ui,float value)
	{ui.filterLFOUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_ENVELOPE>(UIGtk& ui,float value)
	{ui.filterEnvUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_KEYB>(UIGtk& ui,float value)
	{ui.filterKeybUpdate(value);}

template<>
void update<UIGtk::Ports::FILTER_RES>(UIGtk& ui,float value)
	{ui.filterResUpdate(value);}



template<>
void update<UIGtk::Ports::MAIN_ATTACK>(UIGtk& ui,float value)
	{ui.mainAttackUpdate(value);}

template<>
void update<UIGtk::Ports::MAIN_DECAY>(UIGtk& ui,float value)
	{ui.mainDecayUpdate(value);}

template<>
void update<UIGtk::Ports::MAIN_SUSTAIN>(UIGtk& ui,float value)
	{ui.mainSustainUpdate(value);}

template<>
void update<UIGtk::Ports::MAIN_RELEASE>(UIGtk& ui,float value)
	{ui.mainReleaseUpdate(value);}



template<>
void update<UIGtk::Ports::GATE_ATTACK>(UIGtk& ui,float value)
	{ui.gateAttackUpdate(value);}

template<>
void update<UIGtk::Ports::GATE_DECAY>(UIGtk& ui,float value)
	{ui.gateDecayUpdate(value);}

template<>
void update<UIGtk::Ports::GATE_SUSTAIN>(UIGtk& ui,float value)
	{ui.gateSustainUpdate(value);}

template<>
void update<UIGtk::Ports::GATE_RELEASE>(UIGtk& ui,float value)
	{ui.gateReleaseUpdate(value);}

template<>
void update<UIGtk::Ports::GATE_DEPTH>(UIGtk& ui,float value)
	{ui.gateDepthUpdate(value);}


template<>
void update<UIGtk::Ports::MAIN_GAIN>(UIGtk& ui,float value)
	{ui.mainGainUpdate(value);}



const LV2UI_Descriptor& LV2Plug::mainUI()
	{return LV2Plug::descriptorUiGet<UIGtk>();}
 