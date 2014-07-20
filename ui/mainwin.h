#ifdef __WAND__
target[name[mainwin.h] type[include]]
#endif

#ifndef HAPPYCHORDS_UI_MAINWIN_H
#define HAPPYCHORDS_UI_MAINWIN_H
#include "../bridge/connection.h"
#include "../bridge/message.h"
#include <gui/window-custom.h>

#include <cstdio>

namespace Happychords
	{
	namespace Ui
		{
		class Mainwin:public Gui::WindowCustom
			{
			public:
				static Mainwin* create(Gui::Gui& gui_obj,uint32_t style_0
					,uint32_t style_1,Window* parent
					,Bridge::Connection& connection)
					{
					return new Mainwin(gui_obj,style_0,style_1,parent,connection);
					}
				
				size_t onEvent(uint32_t message_id,size_t param_0,size_t param_1)
					{
					switch(message_id)
						{
						case MessageLbuttondown:
							printf("You clicked in the window...\n");
							break;
							
						case MessageClose:
							m_connection.messageSend({Bridge::Message::Type::TERMINATE
								,{{0}}});
							break;
						}
					return WindowCustom::onEvent(message_id,param_0,param_1);
					}

			private:
				Mainwin(Gui::Gui& gui_obj,uint32_t style_0
					,uint32_t style_1,Window* parent
					,Bridge::Connection& connection):
					Gui::WindowCustom(gui_obj,style_0,style_1,parent)
					,m_connection(connection)
					{}
				Bridge::Connection& m_connection;
			};
		}
	}

#endif
