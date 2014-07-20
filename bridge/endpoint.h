#ifdef __WAND__
target[name[endpoint.h] type[include]]
dependency[endpoint.o]
#endif

#ifndef HAPPYCHORDS_BRIDGE_ENDPOINT_H
#define HAPPYCHORDS_BRIDGE_ENDPOINT_H

#include <herbs/string/string.h>

namespace Herbs
	{
	class Directory;
	}

namespace Happychords
	{
	namespace Bridge
		{
		class Endpoint
			{
			public:
				Endpoint(const Herbs::Directory& dir);
				Endpoint(const char* ip,uint64_t port):
					m_ip(ip),m_port(port)
					{}
				
				Herbs::String spellstringGet() const;
				
				const Herbs::Stringbase<char>& ipGetRaw() const
					{return m_ip;}
				Herbs::String ipGet() const;
				Endpoint& ipSet(const Herbs::String& string);
				
				uint64_t portGet() const
					{return m_port;}
				Endpoint& portSet(uint64_t port_new)
					{
					m_port=port_new;
					return *this;
					}

			private:
				Herbs::Stringbase<char> m_ip;
				uint64_t m_port;
			};
		}
	};

#endif
