//@	{
//@	"targets":
//@		[{
//@		 "name":"../happychords2-gtk.so","type":"lib_dynamic"
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
					,m_main_env(m_main.paddingSet(8),"Envelope")
						,m_main_env_box(m_main_env.paddingSet(4),1)
							,m_main_attack(m_main_env_box.insertModeSet(Box::InsertMode::EXPAND),*this)
							,m_main_decay(m_main_env_box,*this)
							,m_main_sustain(m_main_env_box,*this)
							,m_main_release(m_main_env_box,*this)
					,m_gate(m_main,"Gate")
						,m_gate_box(m_gate.paddingSet(4))
							,m_gate_row(m_gate_box.paddingSet(0),1)
								,m_gate_attack(m_gate_row.paddingSet(0).insertModeSet(Box::InsertMode::EXPAND),*this)
								,m_gate_decay(m_gate_row,*this)
								,m_gate_sustain(m_gate_row,*this)
								,m_gate_release(m_gate_row,*this)
								,m_gate_depth(m_gate_row,*this)

			{
			m_voice.borderColorSet(COLOR_KNOB);
			m_voice.captionColorSet(COLOR_TEXT);
			m_lfo.borderColorSet(COLOR_KNOB);
			m_lfo.captionColorSet(COLOR_TEXT);
			m_fc_env.borderColorSet(COLOR_KNOB);
			m_fc_env.captionColorSet(COLOR_TEXT);
			m_fc_mix.borderColorSet(COLOR_KNOB);
			m_fc_mix.captionColorSet(COLOR_TEXT);
		//	m_foo.borderColorSet(COLOR_KNOB);
		//	m_foo.captionColorSet(COLOR_TEXT);
			m_main_env.borderColorSet(COLOR_KNOB);
			m_main_env.captionColorSet(COLOR_TEXT);
			m_gate.borderColorSet(COLOR_KNOB);
			m_gate.captionColorSet(COLOR_TEXT);



			m_detune.colorSet(COLOR_KNOB);
			m_detune.captionColorSet(COLOR_TEXT);
			m_detune.entryBackgroundSet(COLOR_ENTRY);
			m_detune.entryForegroundSet(COLOR_TEXT);
			m_lfo_period.colorSet(COLOR_KNOB);
			m_lfo_period.captionColorSet(COLOR_TEXT);
			m_lfo_period.entryBackgroundSet(COLOR_ENTRY);
			m_lfo_period.entryForegroundSet(COLOR_TEXT);
			m_lfo_phase.colorSet(COLOR_KNOB);
			m_lfo_phase.captionColorSet(COLOR_TEXT);
			m_lfo_phase.entryBackgroundSet(COLOR_ENTRY);
			m_lfo_phase.entryForegroundSet(COLOR_TEXT);
			m_filter_attack.colorSet(COLOR_KNOB);
			m_filter_attack.captionColorSet(COLOR_TEXT);
			m_filter_attack.entryBackgroundSet(COLOR_ENTRY);
			m_filter_attack.entryForegroundSet(COLOR_TEXT);
			m_filter_decay.colorSet(COLOR_KNOB);
			m_filter_decay.captionColorSet(COLOR_TEXT);
			m_filter_decay.entryBackgroundSet(COLOR_ENTRY);
			m_filter_decay.entryForegroundSet(COLOR_TEXT);
			m_filter_sustain.colorSet(COLOR_KNOB);
			m_filter_sustain.captionColorSet(COLOR_TEXT);
			m_filter_sustain.entryBackgroundSet(COLOR_ENTRY);
			m_filter_sustain.entryForegroundSet(COLOR_TEXT);
			m_filter_release.colorSet(COLOR_KNOB);
			m_filter_release.captionColorSet(COLOR_TEXT);
			m_filter_release.entryBackgroundSet(COLOR_ENTRY);
			m_filter_release.entryForegroundSet(COLOR_TEXT);
			m_filter_base.colorSet(COLOR_KNOB);
			m_filter_base.captionColorSet(COLOR_TEXT);
			m_filter_base.entryBackgroundSet(COLOR_ENTRY);
			m_filter_base.entryForegroundSet(COLOR_TEXT);
			m_filter_lfo.colorSet(COLOR_KNOB);
			m_filter_lfo.captionColorSet(COLOR_TEXT);
			m_filter_lfo.entryBackgroundSet(COLOR_ENTRY);
			m_filter_lfo.entryForegroundSet(COLOR_TEXT);
			m_filter_env.colorSet(COLOR_KNOB);
			m_filter_env.captionColorSet(COLOR_TEXT);
			m_filter_env.entryBackgroundSet(COLOR_ENTRY);
			m_filter_env.entryForegroundSet(COLOR_TEXT);
			m_filter_keyb.colorSet(COLOR_KNOB);
			m_filter_keyb.captionColorSet(COLOR_TEXT);
			m_filter_keyb.entryBackgroundSet(COLOR_ENTRY);
			m_filter_keyb.entryForegroundSet(COLOR_TEXT);
			m_filter_res.colorSet(COLOR_KNOB);
			m_filter_res.captionColorSet(COLOR_TEXT);
			m_filter_res.entryBackgroundSet(COLOR_ENTRY);
			m_filter_res.entryForegroundSet(COLOR_TEXT);
			m_main_attack.colorSet(COLOR_KNOB);
			m_main_attack.captionColorSet(COLOR_TEXT);
			m_main_attack.entryBackgroundSet(COLOR_ENTRY);
			m_main_attack.entryForegroundSet(COLOR_TEXT);
			m_main_decay.colorSet(COLOR_KNOB);
			m_main_decay.captionColorSet(COLOR_TEXT);
			m_main_decay.entryBackgroundSet(COLOR_ENTRY);
			m_main_decay.entryForegroundSet(COLOR_TEXT);
			m_main_sustain.colorSet(COLOR_KNOB);
			m_main_sustain.captionColorSet(COLOR_TEXT);
			m_main_sustain.entryBackgroundSet(COLOR_ENTRY);
			m_main_sustain.entryForegroundSet(COLOR_TEXT);
			m_main_release.colorSet(COLOR_KNOB);
			m_main_release.captionColorSet(COLOR_TEXT);
			m_main_release.entryBackgroundSet(COLOR_ENTRY);
			m_main_release.entryForegroundSet(COLOR_TEXT);
			m_gate_attack.colorSet(COLOR_KNOB);
			m_gate_attack.captionColorSet(COLOR_TEXT);
			m_gate_attack.entryBackgroundSet(COLOR_ENTRY);
			m_gate_attack.entryForegroundSet(COLOR_TEXT);
			m_gate_decay.colorSet(COLOR_KNOB);
			m_gate_decay.captionColorSet(COLOR_TEXT);
			m_gate_decay.entryBackgroundSet(COLOR_ENTRY);
			m_gate_decay.entryForegroundSet(COLOR_TEXT);
			m_gate_sustain.colorSet(COLOR_KNOB);
			m_gate_sustain.captionColorSet(COLOR_TEXT);
			m_gate_sustain.entryBackgroundSet(COLOR_ENTRY);
			m_gate_sustain.entryForegroundSet(COLOR_TEXT);
			m_gate_release.colorSet(COLOR_KNOB);
			m_gate_release.captionColorSet(COLOR_TEXT);
			m_gate_release.entryBackgroundSet(COLOR_ENTRY);
			m_gate_release.entryForegroundSet(COLOR_TEXT);
			m_gate_depth.colorSet(COLOR_KNOB);
			m_gate_depth.captionColorSet(COLOR_TEXT);
			m_gate_depth.entryBackgroundSet(COLOR_ENTRY);
			m_gate_depth.entryForegroundSet(COLOR_TEXT);

			m_suboct.backgroundSet(COLOR_BG);
			m_suboct.captionColorSet(COLOR_TEXT);
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


		void lfoPeriodUpdate(float value)
			{m_lfo_period.valueSet(value);}

		void lfoPhaseUpdate(float value)
			{m_lfo_phase.valueSet(value);}

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
				Panel m_main_env;
					Box m_main_env_box;
						Knob< Port<Ports::MAIN_ATTACK>,UIGtk> m_main_attack;
						Knob< Port<Ports::MAIN_DECAY>,UIGtk> m_main_decay;
						Knob< Port<Ports::MAIN_SUSTAIN>,UIGtk> m_main_sustain;
						Knob< Port<Ports::MAIN_RELEASE>,UIGtk> m_main_release;
				Panel m_gate;
					Box m_gate_box;
						Box m_gate_row;
							Knob< Port<Ports::GATE_ATTACK>,UIGtk> m_gate_attack;
							Knob< Port<Ports::GATE_DECAY>,UIGtk> m_gate_decay;
							Knob< Port<Ports::GATE_SUSTAIN>,UIGtk> m_gate_sustain;
							Knob< Port<Ports::GATE_RELEASE>,UIGtk> m_gate_release;
							Knob< Port<Ports::GATE_DEPTH>,UIGtk> m_gate_depth;
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

const LV2UI_Descriptor& LV2Plug::mainUI()
	{
	return LV2Plug::descriptorUiGet<UIGtk>();
	}
