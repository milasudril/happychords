//@	{
//@	 "targets":[{"name":"panel.o","type":"object","pkgconfig_libs":["gtk+-2.0"]}]
//@	}

#include "panel.hpp"
#include "color.hpp"
#include "cairocontext.hpp"
#include <gtk/gtk.h>
#include <cmath>
#include <cstdio>

using namespace Happychords;

static constexpr auto pi=std::acos(-1.0);

static void cairo_rounded_rect(cairo_t* context,double x,double y,double w,double h,double r)
	{
	cairo_new_sub_path(context);
	cairo_arc(context,x + w - r, y + r,r,-pi/2.0,0.0);
	cairo_arc(context,x + w - r, y + h - r,r,0.0,pi/2.0);
	cairo_arc(context,x + r, y + h - r,r,pi/2.0,pi);
	cairo_arc(context,x + r, y + r,r,pi,3.0*pi/2.0);
	cairo_close_path(context);
	}
	
static gboolean draw_stuff(GtkWidget *widget, GdkEventExpose *event,void* data)
	{
	auto panel=reinterpret_cast<Panel*>(data);
	auto context=CairoContext( gdk_cairo_create(gtk_widget_get_window(widget)) );
	GtkAllocation alloc;
	gtk_widget_get_allocation(widget,&alloc);

	auto color=panel->borderColorGet();
	cairo_set_source_rgba(context,color.r,color.g,color.b,1);
	cairo_set_operator(context,CAIRO_OPERATOR_MULTIPLY);
	cairo_rounded_rect(context,alloc.x,alloc.y,alloc.width,alloc.height,4);
	cairo_stroke(context);
	return FALSE;
	}

Panel::Panel(Container& container,const char* caption):m_handle(gtk_frame_new(caption))
	,m_padding(0)
	{
	container.widgetAdd(m_handle);
	gtk_frame_set_shadow_type(reinterpret_cast<GtkFrame*>(m_handle),GTK_SHADOW_NONE);
	gtk_widget_set_app_paintable(reinterpret_cast<GtkWidget*>(m_handle),TRUE);
	gtk_frame_set_label_align(reinterpret_cast<GtkFrame*>(m_handle),0.5,0.0);
	g_signal_connect(m_handle,"expose_event",G_CALLBACK(draw_stuff),this);

	auto markup=g_markup_printf_escaped ("<span weight=\"bold\">%s</span>", caption);
	gtk_label_set_markup(
		reinterpret_cast<GtkLabel*>(gtk_frame_get_label_widget(reinterpret_cast<GtkFrame*>(m_handle))),markup);
	g_free(markup);
	}

Panel::~Panel()
	{gtk_widget_destroy(reinterpret_cast<GtkWidget*>(m_handle));}

Panel& Panel::widgetAdd(void* widget)
	{
	gtk_container_add(reinterpret_cast<GtkContainer*>(m_handle),reinterpret_cast<GtkWidget*>(widget));
//	FIXME: This is WRONG, since it does only work on containers, but it is GTK that has a bad API :-(.
//	It is likely that panels always contain a container so this should work.
	gtk_container_set_border_width(reinterpret_cast<GtkContainer*>(widget),m_padding);

	return *this;
	}

void Panel::captionColorSet(const glm::vec3& color) noexcept
	{
	auto c=make_color(color);
	gtk_widget_modify_fg(gtk_frame_get_label_widget(reinterpret_cast<GtkFrame*>(m_handle)),GTK_STATE_NORMAL,&c);
	}

void Panel::borderColorSet(const glm::vec3& color) noexcept
	{
	m_border_color=color;
	gtk_widget_queue_draw(reinterpret_cast<GtkWidget*>(m_handle));
	}

	