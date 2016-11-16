//@	{
//@	"targets":
//@		[{
//@		 "name":"knob.o","type":"object"
//@		,"dependencies":
//@			[
//@				 {"ref":"knob-shadow.png","rel":"generated"}
//@				,{"ref":"knob-mask.png","rel":"generated"}
//@				,{"ref":"knob-specular.png","rel":"generated"}
//@			]
//@		,"pkgconfig_libs":["gtk+-2.0"]
//@		}]
//@	}

#include "knob.hpp"
#include "../common/blob.hpp"
#include "imageresource.hpp"
#include "cairocontext.hpp"
#include "container.hpp"
#include "color.hpp"
#include <maike/targetinclude.hpp>
#include <cairo.h>
#include <gtk/gtk.h>
#include <cmath>

BLOB(knob_shadow,MAIKE_TARGET(knob-shadow.png));
BLOB(knob_mask,MAIKE_TARGET(knob-mask.png));
BLOB(knob_specular,MAIKE_TARGET(knob-specular.png));

using namespace Happychords;

static auto image_mask=imageResourceLoad(knob_mask_begin,knob_mask_end);
static auto image_shadow=imageResourceLoad(knob_shadow_begin,knob_shadow_end);
static auto image_specular=imageResourceLoad(knob_specular_begin,knob_specular_end);

static bool dial_draw(GtkWidget* widget,GdkEventExpose* event,void* data) noexcept
	{
	auto knob=reinterpret_cast<KnobBase*>(data);
	GtkAllocation alloc;
	gtk_widget_get_allocation(widget,&alloc);

	auto width=alloc.width;	
	auto context=CairoContext( gdk_cairo_create(gtk_widget_get_window(widget)) );

	auto w_in=cairo_image_surface_get_width(image_mask);
	auto h_in=cairo_image_surface_get_height(image_mask);
	auto surf_temp=CairoSurface( cairo_image_surface_create(CAIRO_FORMAT_ARGB32,w_in,h_in) );
	auto context_temp=CairoContext( cairo_create(surf_temp) );

	cairo_translate(context_temp,0.5*w_in,0.5*h_in);
	cairo_rotate(context_temp,knob->angleGet());
	cairo_translate(context_temp,-0.5*w_in,-0.5*h_in);
	cairo_set_operator(context_temp,CAIRO_OPERATOR_OVER);
	cairo_set_source_surface(context_temp,image_mask,0,0);
	cairo_paint(context_temp);

	cairo_set_operator(context_temp,CAIRO_OPERATOR_MULTIPLY);
	cairo_identity_matrix(context_temp);
	cairo_set_source_surface(context_temp,image_shadow,0,0);
	cairo_mask_surface(context_temp,surf_temp,0,0);

	cairo_set_operator(context_temp,CAIRO_OPERATOR_MULTIPLY);
	auto color=knob->colorGet();
	cairo_set_source_rgb(context_temp, color.r, color.g, color.b);
	cairo_rectangle(context_temp, 0, 0, w_in, h_in);
	cairo_mask_surface(context_temp,surf_temp,0,0);

	cairo_set_operator(context_temp,CAIRO_OPERATOR_ADD);
	cairo_set_source_surface(context_temp,image_specular,0,0);
	cairo_mask_surface(context_temp,surf_temp,0,0);

	auto s=static_cast<double>(width)/static_cast<double>(w_in);
	cairo_translate(context,alloc.x,alloc.y);
	cairo_scale(context,s,s);
	cairo_set_source_surface(context,surf_temp,0,0);
	cairo_set_operator(context,CAIRO_OPERATOR_OVER);
	cairo_paint(context);
	return FALSE;
	}

static void dial_hover(GtkWidget* widget,GdkEventMotion* event,void* data)
	{
	if(event->state&GDK_BUTTON1_MASK)
		{
		GtkAllocation allocation;
		gtk_widget_get_allocation(widget,&allocation);
		auto w=allocation.width;
		auto h=allocation.height;
		auto mid_x=0.5*w;
		auto mid_y=0.5*h;

		auto x=event->x - mid_x;
		auto y=mid_y - event->y;
		auto theta=std::atan2(x,y) - std::acos(-1.0)/2.0;
		auto knob=reinterpret_cast<KnobBase*>(data);
		auto value=knob->valueGet(theta);
		knob->valueSet(value);
		knob->changeEmmit();
		}
	}

static void entry_changed(GtkSpinButton* spinbutton,void* arg1,void* data)
	{
	auto knob=reinterpret_cast<KnobBase*>(data);
	knob->valueSet(gtk_spin_button_get_value(spinbutton));
	knob->changeEmmit();
	}

static double step_from_range(double min,double max)
	{
	auto length=max - min;
	return std::pow(10,std::floor(log10(length))-3.0 );
	}

KnobBase::KnobBase(Container& parent,const char* caption,double min,double max,double value):
m_min(min),m_max(max),m_value(value),m_color(1.0f,1.0f,1.0f)
	{
	auto dial=gtk_drawing_area_new();
	m_dial=dial;
	gtk_widget_set_size_request(dial,64,64);
	gtk_signal_connect(reinterpret_cast<GtkObject*>(dial)
		,"expose_event",G_CALLBACK(dial_draw),this);
	gtk_widget_set_has_window(dial,FALSE);
	auto eb=gtk_event_box_new();
	gtk_widget_add_events(eb
		,static_cast<int>(GDK_POINTER_MOTION_MASK
			|GDK_BUTTON_PRESS_MASK
			|GDK_BUTTON_RELEASE_MASK
			|GDK_KEY_PRESS_MASK));
	g_signal_connect(eb,"motion-notify-event",G_CALLBACK(dial_hover),this);
	gtk_container_add(reinterpret_cast<GtkContainer*>(eb),dial);
	gtk_event_box_set_visible_window(reinterpret_cast<GtkEventBox*>(eb),FALSE);	
#ifdef FIXME
	g_signal_connect(reinterpret_cast<GtkObject*>(dial),"key-press-event",G_CALLBACK(onKeyDown),this);
	g_signal_connect(reinterpret_cast<GtkObject*>(dial),"key-release-event",G_CALLBACK(onKeyUp),this);
#endif

	auto dial_box=gtk_aspect_frame_new(caption,0.5f,0.5f,1.0,TRUE);
	m_dial_box=dial_box;
	gtk_frame_set_label_align(reinterpret_cast<GtkFrame*>(dial_box),0.5f,.0f);
	gtk_frame_set_shadow_type(reinterpret_cast<GtkFrame*>(dial_box),GTK_SHADOW_NONE);
	gtk_container_add(reinterpret_cast<GtkContainer*>(dial_box),eb);

	auto entry=gtk_spin_button_new_with_range(min,max,step_from_range(min,max));
	GtkBorder border{0,0,0,0};
	gtk_entry_set_inner_border(reinterpret_cast<GtkEntry*>(entry),&border);
	gtk_entry_set_width_chars(reinterpret_cast<GtkEntry*>(entry),0);
	m_entry=entry;
	gtk_spin_button_set_value(reinterpret_cast<GtkSpinButton*>(entry),m_value);
	gtk_signal_connect(reinterpret_cast<GtkObject*>(entry),"value_changed",G_CALLBACK(entry_changed),this);

	auto box=reinterpret_cast<GtkBox*>(gtk_vbox_new(FALSE,0));
	m_box=reinterpret_cast<GtkWidget*>(box);
	gtk_box_pack_start(box,reinterpret_cast<GtkWidget*>(dial_box),TRUE,TRUE,0);
	gtk_box_pack_start(box,reinterpret_cast<GtkWidget*>(m_entry),FALSE,FALSE,0);

	parent.widgetAdd(box);
	}

KnobBase::~KnobBase()
	{gtk_widget_destroy(reinterpret_cast<GtkWidget*>(m_box));}

void KnobBase::valueSet(double value) noexcept
	{
	m_value=std::min(m_max,std::max(value,m_min));
	gtk_widget_queue_draw(reinterpret_cast<GtkWidget*>(m_dial));
	gtk_spin_button_set_value(reinterpret_cast<GtkSpinButton*>(m_entry),m_value);
	}

void KnobBase::colorSet(const glm::vec3& color) noexcept
	{
	m_color=color;
	gtk_widget_queue_draw(reinterpret_cast<GtkWidget*>(m_dial));
	}

void KnobBase::captionColorSet(const glm::vec3& color) noexcept
	{
	auto c=make_color(color);
	gtk_widget_modify_fg(gtk_frame_get_label_widget(reinterpret_cast<GtkFrame*>(m_dial_box)),GTK_STATE_NORMAL,&c);
	}

void KnobBase::entryBackgroundSet(const glm::vec3& color) noexcept
	{
	auto c=make_color(color);
	gtk_widget_modify_base(reinterpret_cast<GtkWidget*>(m_entry),GTK_STATE_NORMAL,&c);
	}

void KnobBase::entryForegroundSet(const glm::vec3& color) noexcept
	{
	auto c=make_color(color);
	gtk_widget_modify_text(reinterpret_cast<GtkWidget*>(m_entry),GTK_STATE_NORMAL,&c);
	gtk_widget_modify_fg(reinterpret_cast<GtkWidget*>(m_entry),GTK_STATE_NORMAL,&c);
	}
