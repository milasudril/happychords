#ifdef __WAND__
target[name[connection.h] type[include]]
dependency[connection.o]
#endif

#ifndef HAPPYCHORDS_BRIDGE_CONNECTION_H
#define HAPPYCHORDS_BRIDGE_CONNECTION_H

#include "endpoint.h"
#include <herbs/network/socket_datagram.h>

namespace Happychords
	{
	namespace Bridge
		{
		struct Message;
			
		class Connection
			{
			public:
				Connection( Endpoint&& in, Endpoint&& out);
					
				Connection(const Herbs::Directory& dir);
			
				Herbs::String spellstringGet(bool inout_swap) const;
				
				bool messageGet(Message& msg);
				bool messageSend(const Message& msg);
			
			private:
				Endpoint end_in;
				Endpoint end_out;
				
				Herbs::Network::SocketDatagram socket_in;
				Herbs::Network::SocketDatagram socket_out;
			};
		}
	}

#endif

