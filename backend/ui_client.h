#ifdef __WAND__
target[name[ui_client.h] type[include]]
#endif

#ifndef HAPPYCHORDS_UICLIENT_H
#define HAPPYCHORDS_UICLIENT_H

#include <lv2plug/feature_descriptor.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>

#include <cstdio>

namespace Happychords
	{
	class UiClient
		{
		public:
			static constexpr const char* URI="http://example.org/happychords/ui";
			
			static LV2UI_Handle create(const char* path_bundle
				,LV2UI_Write_Function write_callback
				,LV2UI_Controller controller
				,LV2UI_Widget* widget
				,const LV2Plug::FeatureDescriptor& features)
				{
				return new UiClient(path_bundle,write_callback,controller,widget
					,features);
				}
			
			void portEvent(uint32_t port,uint32_t buffer_size
				,uint32_t format,const void* buffer)
				{
				}
			
			void destroy()
				{delete this;}
			
		private:
			UiClient(const char* path_bundle
				,LV2UI_Write_Function write_callback
				,LV2UI_Controller controller
				,LV2UI_Widget* widget
				,const LV2Plug::FeatureDescriptor& features)
				{
				printf("Hello %p\n",widget);
				}
		};
	}

#endif
