#ifdef __WAND__
target[name[message_receiver.o] type [object]]
#endif

#include "message_receiver.h"
#include "mainwin.h"
#include "../bridge/connection.h"
#include "../bridge/message.h"

Happychords::Ui::MessageReceiver::MessageReceiver(Herbs::LogWriter& log):
	Herbs::Runnable(log)
	{}

int Happychords::Ui::MessageReceiver::run()
	{
	Bridge::Message msg;
	while(m_source->messageGet(msg))
		{
		switch(msg.type)
			{
			case Bridge::Message::Type::TERMINATE:
				m_dest->close();
				return STATUS_OK;
			case Bridge::Message::Type::WINDOWTITLE_SET:
				{
				Herbs::String str=stringGet(msg);
				m_dest->titleSet(str.begin());
				}
				break;
			}
		}
	return STATUS_FAILED;
	}