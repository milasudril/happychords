#ifdef __WAND__
target[name[ui.h] type[include]]
dependency[ui.o]
#endif

#ifndef HAPPYCHORDS_UI_H
#define HAPPYCHORDS_UI_H

#include <gui/gui.h>
#include <gui/logwriter_msgbox.h>

namespace Happychords
	{
	class UiMainwin;
	
	class Ui:public Gui::Gui
		{
		public:
			Ui(Herbs::LogWriter& log,Herbs::Directory&& config);
			void destroy();
			
		private:
			UiMainwin* mainwin;
			::Gui::LogwriterMsgbox my_sysout;
		};
	}

#endif