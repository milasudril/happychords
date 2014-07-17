#ifdef __WAND__
target[name[ui_client.h] type[include]]
#endif

#ifndef HAPPYCHORDS_UICLIENT_H
#define HAPPYCHORDS_UICLIENT_H

#include <lv2plug/feature_descriptor.h>
#include <lv2plug/ui.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

#include <cstdio>

namespace Happychords
	{
	class UiClient:public LV2Plug::UiWrapper<UiClient>
		{
		public:
			static constexpr const char* URI="http://example.org/happychords#UI";
			
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
			
		private:
			UiClient(const char* path_bundle
				,LV2UI_Write_Function write_callback
				,LV2UI_Controller controller
				,const LV2_External_UI_Host& ext_host)
				{
				printf("Hello %s\n",ext_host.plugin_human_id);
				}
		};
	}

#endif
