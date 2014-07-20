#ifdef __WAND__
target[name[message_receiver.o] type [object]]
#endif

#include "message_receiver.h"
#include "ui_client.h"
#include "../bridge/connection.h"
#include "../bridge/message.h"

Happychords::Plugin::MessageReceiver::MessageReceiver(Herbs::LogWriter& log
	,UiClient& client,Bridge::Connection& connection
	,void (*closeCallback)(LV2UI_Controller)
	,LV2UI_Controller controller):
	Herbs::Runnable(log),m_client(client),m_connection(connection)
	,m_closeCallback(closeCallback),m_controller(controller)
	,terminating(0)
	{}

int Happychords::Plugin::MessageReceiver::run()
	{
	Bridge::Message msg;
	while(m_connection.messageGet(msg))
		{
		switch(msg.type)
			{
			case Bridge::Message::Type::TERMINATE:
				if(!terminating)
					{m_closeCallback(m_controller);}
				return STATUS_OK;
			}
		}
	return STATUS_FAILED;
	}