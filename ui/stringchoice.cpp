//@	{
//@	 "targets":
//@		[
//@			{
//@			 "name":"stringchoice.o","type":"object"
//@			,"pkgconfig_libs":["gtk+-2.0"]
//@			}
//@		]
//@	}

#include "stringchoice.hpp"
#include "container.hpp"
#include <gtk/gtk.h>

using namespace Happychords;

StringchoiceBase::StringchoiceBase(Container& parent,const char* caption)
	{
	auto label=gtk_label_new(caption);
	m_label=label;
	auto combo=gtk_combo_box_text_new();
	m_combo=combo;
	auto box=reinterpret_cast<GtkBox*>(gtk_hbox_new(FALSE,0));
	m_box=box;
	gtk_box_pack_start(box,reinterpret_cast<GtkWidget*>(label),FALSE,FALSE,0);
	gtk_box_pack_start(box,reinterpret_cast<GtkWidget*>(combo),TRUE,TRUE,4);
	parent.widgetAdd(box);
	}

StringchoiceBase::~StringchoiceBase()
	{
	gtk_widget_destroy(reinterpret_cast<GtkWidget*>(m_box));
	}
