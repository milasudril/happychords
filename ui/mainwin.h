#ifdef __WAND__
target[name[mainwin.h] type[include]]
#endif

#ifndef HAPPYCHORDS_UI_MAINWIN_H
#define HAPPYCHORDS_UI_MAINWIN_H

#include <gui/window-custom.h>

namespace Happychords
	{
	namespace Ui
		{
		class Mainwin:public Gui::WindowCustom
			{
			public:
				static Mainwin* create(Gui::Gui& gui_obj,uint32_t style_0
					,uint32_t style_1,Window* parent)
					{
					return new Mainwin(gui_obj,style_0,style_1,parent);
					}

			private:
				Mainwin(Gui::Gui& gui_obj,uint32_t style_0
					,uint32_t style_1,Window* parent):
					Gui::WindowCustom(gui_obj,style_0,style_1,parent)
					{}
			};
		}
	}

#endif
