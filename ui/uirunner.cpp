#ifdef __WAND__
target[name[uirunner.o] type[object]]
#endif

#include "uirunner.h"
#include "mainwin.h"
#include "../bridge/message.h"
#include <herbs/directory/directory.h>
#include <herbs/exceptionmissing/exceptionmissing.h>
#include <herbs/thread/thread.h>

Happychords::Ui::UiRunner::UiRunner(Herbs::LogWriter& log,Herbs::Directory&& config)
	:Gui::Gui(my_sysout),connection(config),msg_receiver(my_sysout)
	{
	::Gui::WindowCustom::init();
	mainwin=Mainwin::create(*this,0,0,nullptr,connection);
	msg_receiver.sourceSet(connection);
	msg_receiver.destSet(*mainwin);
	msg_thread=new Herbs::Thread(msg_receiver);
	
	my_sysout.ownerSet(mainwin);
	
//	fonts={&font_header,&font_label,&font_content,&font_content_large};
//	mainwin->fontsSet(fonts);
	mainwin->popup();
	mainwin->sizeRelative(0.5,0.5);
	mainwin->moveRelative({0,0},{0.5,0.5});
	mainwin->show(::Gui::Window::DisplayNormal);
	connection.messageSend({Bridge::Message::Type::ACKNOLEDGEMENT,{{0}}});
	}

Happychords::Ui::UiRunner::~UiRunner()
	{
	delete msg_thread;
	}

void Happychords::Ui::UiRunner::destroy()
	{
	delete this;
	}
