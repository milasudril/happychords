#ifdef __WAND__
target[name[message_receiver.h] type[include]]
dependency[message_receiver.o]
#endif

#ifndef HAPPYCHORDS_PLUGIN_MESSAGERECEIVER_H
#define HAPPYCHORDS_PLUGIN_MESSAGERECEIVER_H

#include <lv2plug/ui.h>
#include <herbs/runnable/runnable.h>

namespace Happychords
	{
	namespace Bridge
		{
		class Connection;
		}
	
	namespace Plugin
		{
		class UiClient;
		class MessageReceiver:public Herbs::Runnable
			{
			public:
				MessageReceiver(Herbs::LogWriter& log,UiClient& client
					,Bridge::Connection& connection
					,void (*closeCallback)(LV2UI_Controller)
					,LV2UI_Controller controller);
				
				int run();
				
				void terminateSet()
					{terminating=1;}
				
			private:
				UiClient& m_client;
				Bridge::Connection& m_connection;
				void (*m_closeCallback)(LV2UI_Controller);
				LV2UI_Controller m_controller;
				bool terminating;
			};
		}
	}

#endif
