#ifdef __WAND__
target[name[message_receiver.h] type[include]]
dependency[message_receiver.o]
#endif

#ifndef HAPPYCHORDS_UI_MESSAGERECEIVER_H
#define HAPPYCHORDS_UI_MESSAGERECEIVER_H

#include <herbs/runnable/runnable.h>

namespace Happychords
	{
	namespace Bridge
		{
		class Connection;
		}
	
	namespace Ui
		{
		class Mainwin;
		class MessageReceiver:public Herbs::Runnable
			{
			public:
				MessageReceiver(Herbs::LogWriter& log);
				
				void destSet(Mainwin& dest_new)
					{m_dest=&dest_new;}
					
				void sourceSet(Bridge::Connection& src_new)
					{m_source=&src_new;}
				
				int run();
				
			private:
				Bridge::Connection* m_source;
				Mainwin* m_dest;
			};
		}
	}

#endif
