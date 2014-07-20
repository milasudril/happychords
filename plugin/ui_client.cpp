#ifdef __WAND__
target[name[ui_client.o] type[object]]
#endif

#include "ui_client.h"
#include "../bridge/message.h"

#include <herbs/stringsys/stringsys.h>
#include <herbs/path/path.h>
#include <herbs/process/process.h>
#include <herbs/stringformat/stringformat.h>
#include <herbs/intformat/intformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

Happychords::Plugin::UiClient::~UiClient()
	{delete remote;}

	
Happychords::Plugin::UiClient::UiClient(const char* path_bundle
	,LV2UI_Write_Function write_callback,LV2UI_Controller controller
	,const LV2_External_UI_Host& ext_host):
	ui_bridge(
		 {"127.0.0.1",65535}
		,{"127.0.0.1",65534}
		)
	{
	Herbs::Path path_exe(Herbs::stringloc(path_bundle));
	path_exe>>=STR("happychords-ui.exe");

	Herbs::String command=Herbs::format(STR("wine \"%0\" \"%1\"")
		,{
		 Herbs::String(path_exe).begin()
		,ui_bridge.spellstringGet(1).begin()
		});

	remote=new Herbs::Process(command);
	
	Bridge::Message msg;
	if(!ui_bridge.messageGet(msg))
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
		{
		Bridge::Message msg;
		msg.type=Bridge::Message::Type::WINDOWTITLE_SET;
		strncpy((char*)msg.data.bytes,ext_host.plugin_human_id,56);
		ui_bridge.messageSend(msg);
		}
	}
