#ifdef __WAND__
target[name[happychords-ui.exe] type[application] platform[;Windows]]
target[name[happychords-ui] type[application] ]
#endif

#include "uirunner.h"
#include <herbs/maindefault/maindefault.h>
#include <utility>

Herbs::Application* Herbs::Application::instanceCreate(Herbs::LogWriter& log
	,Herbs::Directory&& config)
	{
	return new Happychords::Ui::UiRunner(log,std::move(config));
	}