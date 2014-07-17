#ifdef __WAND__
target[name[ui.o] type[object]]
#endif

#include "ui.h"
#include "ui_mainwin.h"

Happychords::Ui::Ui(Herbs::LogWriter& log,Herbs::Directory&& config)
	:Gui::Gui(my_sysout)
	{
	::Gui::WindowCustom::init();
	mainwin=UiMainwin::create(*this,0,0,nullptr);
	my_sysout.ownerSet(mainwin);
//	fonts={&font_header,&font_label,&font_content,&font_content_large};
//	mainwin->fontsSet(fonts);
	mainwin->popup();
	mainwin->sizeRelative(0.5,0.5);
	mainwin->moveRelative({0,0},{0.5,0.5});
	mainwin->show(::Gui::Window::DisplayNormal);
	}

void Happychords::Ui::destroy()
	{
	delete this;
	}
