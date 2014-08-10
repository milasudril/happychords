#ifdef __WAND__
target[name[mainwin.h] type[include]]
dependency[mainwin.o]
#endif

#ifndef HAPPYCHORDS_UI_MAINWIN_H
#define HAPPYCHORDS_UI_MAINWIN_H
#include "../bridge/connection.h"
#include "../bridge/message.h"
#include <gui/glviewport.h>

#include <gl/glew.h>

namespace Happychords
	{
	namespace Ui
		{
		class Mainwin:public Gui::GlViewport
			{
			public:
				static Mainwin* create(Gui::Gui& gui_obj,uint32_t style_0
					,uint32_t style_1,Window* parent
					,Bridge::Connection& connection)
					{
					return new Mainwin(gui_obj,style_0,style_1,parent,connection);
					}

				void onResize(int width,int height);

				void onRender();

				size_t onEvent(uint32_t message_id,size_t param_0,size_t param_1);

				~Mainwin();

			private:
				Mainwin(Gui::Gui& gui_obj,uint32_t style_0
					,uint32_t style_1,Window* parent
					,Bridge::Connection& connection);
				Bridge::Connection& m_connection;
				GLuint v_array_id;
				GLuint v_buffer;
				GLuint program;
			};
		}
	}

#endif
