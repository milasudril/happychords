#ifdef __WAND__
target[name[ui_client.h] type[include]]
dependency[ui_client.o]
#endif

#ifndef HAPPYCHORDS_PLUGIN_UICLIENT_H
#define HAPPYCHORDS_PLUGIN_UICLIENT_H

#include "../bridge/connection.h"
#include <lv2plug/feature_descriptor.h>
#include <lv2plug/ui.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

namespace Herbs
	{
	class Process;
	}

namespace Happychords
	{
	namespace Plugin
		{
		class UiClient:public LV2Plug::UiWrapper<UiClient>
			{
			public:
				static constexpr const char* URI="http://github.com/milasudril/happychords#UI";
				
				static LV2UI_Handle doCreate(const char* path_bundle
					,LV2UI_Write_Function write_callback
					,LV2UI_Controller controller
					,const LV2_External_UI_Host& ext_host)
					{
					return new UiClient(path_bundle,write_callback,controller
						,ext_host);
					}
				
				void doPortEvent(uint32_t port,uint32_t buffer_size
					,uint32_t format,const void* buffer)
					{
					}
				
				void doRun()
					{}
				
				void doShow()
					{}
				
				void doHide()
					{}
				
				void doDestroy()
					{delete this;}
				
				~UiClient();
				
			private:
				UiClient(const char* path_bundle
					,LV2UI_Write_Function write_callback
					,LV2UI_Controller controller
					,const LV2_External_UI_Host& ext_host);
				
				Bridge::Connection ui_bridge;
				
				Herbs::Process* remote;
				
			};
		}
	}

#endif
