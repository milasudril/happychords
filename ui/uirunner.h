#ifdef __WAND__
target[name[uirunner.h] type[include]]
dependency[uirunner.o]
#endif

#ifndef HAPPYCHORDS_UI_UIRUNNER_H
#define HAPPYCHORDS_UI_UIRUNNER_H

#include "message_receiver.h"
#include "../bridge/connection.h"
#include <gui/gui.h>
#include <gui/logwriter_msgbox.h>

namespace Herbs
	{
	class Thread;
	}

namespace Happychords
	{
	namespace Ui
		{
		class Mainwin;
		
		class UiRunner:public Gui::Gui
			{
			public:
				UiRunner(Herbs::LogWriter& log,Herbs::Directory&& config);
				void destroy();
				~UiRunner();
				
			private:
				::Gui::LogwriterMsgbox my_sysout;
				Bridge::Connection connection;
				Mainwin* mainwin;
				MessageReceiver msg_receiver;
				Herbs::Thread* msg_thread;
			};
		}
	}

#endif