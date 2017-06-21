//@	{
//@	"targets":
//@		[{
//@		 "name":"switch.o","type":"object"
//@		,"dependencies":
//@			[
//@           {"ref":"switch-down-background.png","rel":"misc"}
//@          ,{"ref":"switch-down-light.png","rel":"misc"}
//@          ,{"ref":"switch-up-background.png","rel":"misc"}
//@          ,{"ref":"switch-up-light.png","rel":"misc"}
//@			]
//@		,"pkgconfig_libs":["gtk+-2.0"]
//@		}]
//@	}

#include "switch.hpp"
#include "../common/blob.hpp"
#include "imageresource.hpp"
#include "cairocontext.hpp"
#include "color.hpp"
#include "container.hpp"
#include <maike/targetinclude.hpp>
#include <cairo.h>
#include <gtk/gtk.h>
#include <cmath>

BLOB(switch_down_background,MAIKE_TARGET(switch-down-background.png));
BLOB(switch_down_light,MAIKE_TARGET(switch-down-light.png));
BLOB(switch_up_background,MAIKE_TARGET(switch-up-background.png));
BLOB(switch_up_light,MAIKE_TARGET(switch-up-light.png));

using namespace Happychords;

static auto image_switch_down_background=imageResourceLoad(switch_down_background_begin,switch_down_background_end);
static auto image_switch_down_light=imageResourceLoad(switch_down_light_begin,switch_down_light_end);
static auto image_switch_up_background=imageResourceLoad(switch_up_background_begin,switch_up_background_end);
static auto image_switch_up_light=imageResourceLoad(switch_up_light_begin,switch_up_light_end);

static void switch_draw_impl(GtkWidget* widget
	,const CairoSurface& light,const CairoSurface& background
	,const glm::vec3& color_bg)
	{
	GtkAllocation alloc;
	gtk_widget_get_allocation(widget,&alloc);

	auto width=alloc.width;
	auto context=CairoContext( gdk_cairo_create(gtk_widget_get_window(widget)) );

	auto w_in=cairo_image_surface_get_width(light);
	auto h_in=cairo_image_surface_get_height(light);
	auto surf_temp=CairoSurface( cairo_image_surface_create(CAIRO_FORMAT_ARGB32,w_in,h_in) );
	auto context_temp=CairoContext( cairo_create(surf_temp) );

	cairo_set_source_surface(context_temp,light,0,0);
	cairo_set_operator(context_temp,CAIRO_OPERATOR_OVER);
	cairo_paint(context_temp);

	auto surf_temp_2=CairoSurface( cairo_image_surface_create(CAIRO_FORMAT_ARGB32,w_in,h_in) );
	auto context_temp_2=CairoContext( cairo_create(surf_temp_2) );
	cairo_set_source_surface(context_temp_2,background,0,0);
	cairo_set_operator(context_temp_2,CAIRO_OPERATOR_OVER);
	cairo_paint(context_temp_2);

	cairo_set_operator(context_temp_2,CAIRO_OPERATOR_MULTIPLY);
	cairo_set_source_rgb(context_temp_2, color_bg.r, color_bg.g, color_bg.b);
	cairo_rectangle(context_temp_2, 0, 0, w_in, h_in);
	cairo_mask_surface(context_temp_2,surf_temp,0,0);

	cairo_set_source_surface(context_temp,surf_temp_2,0,0);
	cairo_set_operator(context_temp,CAIRO_OPERATOR_ADD);
	cairo_mask_surface(context_temp,surf_temp,0,0);

	auto s=static_cast<double>(width)/static_cast<double>(w_in);
	cairo_translate(context,alloc.x,alloc.y);
	cairo_scale(context,s,s);
	cairo_set_source_surface(context,surf_temp,0,0);
	cairo_set_operator(context,CAIRO_OPERATOR_OVER);
	cairo_paint(context);
	}

static bool switch_draw(GtkWidget* widget,GdkEventExpose* event,void* data) noexcept
	{
	auto sw=reinterpret_cast<SwitchBase*>(data);
	if(sw->stateGet()==SwitchBase::State::UP)
		{switch_draw_impl(widget,image_switch_up_light,image_switch_up_background,sw->backgroundGet());}
	else
		{switch_draw_impl(widget,image_switch_down_light,image_switch_down_background,sw->backgroundGet());}
	return FALSE;
	}

static bool toggle(GtkWidget* widget,GdkEvent* event,void* data) noexcept
	{
	auto sw=reinterpret_cast<SwitchBase*>(data);
	auto state=sw->stateGet();
	sw->stateSet(state==SwitchBase::State::UP?
		SwitchBase::State::DOWN:SwitchBase::State::UP);
	sw->changeEmmit();
	return TRUE;
	}

SwitchBase::SwitchBase(Container& parent,const char* caption,State state_init):
	m_state(state_init),m_background(1.0f,1.0f,1.0f)
	{
	auto sw=gtk_drawing_area_new();
	m_switch=sw;
	gtk_widget_set_size_request(sw,64,64);
	gtk_widget_set_has_window(sw,FALSE);
	gtk_signal_connect(reinterpret_cast<GtkObject*>(sw)
		,"expose_event",G_CALLBACK(switch_draw),this);

	auto eb=gtk_event_box_new();
	gtk_widget_add_events(eb
		,static_cast<int>(GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK));
	g_signal_connect(eb,"button-press-event",G_CALLBACK(toggle),this);
	gtk_event_box_set_above_child(reinterpret_cast<GtkEventBox*>(eb),FALSE);
	gtk_event_box_set_visible_window(reinterpret_cast<GtkEventBox*>(eb),FALSE);	
	gtk_container_set_border_width(reinterpret_cast<GtkContainer*>(eb),0);
	gtk_container_add(reinterpret_cast<GtkContainer*>(eb),sw);

	auto switch_box=gtk_aspect_frame_new(caption,0.5f,0.5f,1.0f,TRUE);
	gtk_frame_set_label_align(reinterpret_cast<GtkFrame*>(switch_box),0.5f,0.0f);
	gtk_frame_set_shadow_type(reinterpret_cast<GtkFrame*>(switch_box),GTK_SHADOW_NONE);
	gtk_container_set_border_width(reinterpret_cast<GtkContainer*>(switch_box),0);
	gtk_container_add(reinterpret_cast<GtkContainer*>(switch_box),eb);

	m_box=switch_box;
	parent.widgetAdd(m_box);
	}

SwitchBase::~SwitchBase()
	{gtk_widget_destroy(reinterpret_cast<GtkWidget*>(m_box));}

void SwitchBase::stateSet(State state) noexcept
	{
	m_state=state;
	gtk_widget_queue_draw(reinterpret_cast<GtkWidget*>(m_switch));
	}

void SwitchBase::backgroundSet(const glm::vec3& color) noexcept
	{
	m_background=color;
	gtk_widget_queue_draw(reinterpret_cast<GtkWidget*>(m_switch));
	}

void SwitchBase::captionColorSet(const glm::vec3& color) noexcept
	{
	auto c=make_color(color);
	gtk_widget_modify_fg(gtk_frame_get_label_widget(reinterpret_cast<GtkFrame*>(m_box)),GTK_STATE_NORMAL,&c);
	}

