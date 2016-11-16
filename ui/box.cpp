//@	{
//@	 "targets":[{"name":"box.o","type":"object","pkgconfig_libs":["gtk+-2.0"]}]
//@	}

#include "box.hpp"
#include <gtk/gtk.h>

using namespace Happychords;

Box::Box(Container& container,bool horizontal):
m_handle(horizontal?gtk_hbox_new(false,0):gtk_vbox_new(false,0))
,m_mode(InsertMode::NORMAL),m_padding(4)
	{container.widgetAdd(m_handle);}

Box::~Box()
	{gtk_widget_destroy(reinterpret_cast<GtkWidget*>(m_handle));}

Box& Box::widgetAdd(void* widget)
	{
	bool expand=m_mode==InsertMode::EXPAND||m_mode==InsertMode::FILL;
	bool fill=m_mode==InsertMode::FILL;
	gtk_box_pack_start(reinterpret_cast<GtkBox*>(m_handle),reinterpret_cast<GtkWidget*>(widget)
		,expand,fill,m_padding);
	return *this;
	}
