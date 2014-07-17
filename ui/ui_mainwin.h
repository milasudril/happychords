#ifdef __WAND__
target[name[ui_mainwin.h] type[include]]
#endif

#ifndef HAPPYCHORDS_UIMAINWIN_H
#define HAPPYCHORDS_UIMAINWIN_H

#include <gui/window-custom.h>

namespace Happychords
	{
	class UiMainwin:public Gui::WindowCustom
		{
		public:
			static UiMainwin* create(Gui::Gui& gui_obj,uint32_t style_0
				,uint32_t style_1,Window* parent)
				{
				return new UiMainwin(gui_obj,style_0,style_1,parent);
				}
		private:
			UiMainwin(Gui::Gui& gui_obj,uint32_t style_0
				,uint32_t style_1,Window* parent):
				Gui::WindowCustom(gui_obj,style_0,style_1,parent)
				{}
		};
	}

#endif
