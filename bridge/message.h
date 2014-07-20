#ifdef __WAND__
target[name[message.h] type[include]]
dependency[message.o]
#endif

#ifndef HAPPYCHORDS_BRIDGE_MESSAGE_H
#define HAPPYCHORDS_BRIDGE_MESSAGE_H

#include <herbs/chartype/chartype.h>

namespace Herbs
	{
	template<class T>
	class Stringbase;
	typedef Stringbase<char_t> String;
	}

namespace Happychords
	{
	namespace Bridge
		{
		struct Message
			{
			uint64_t type;
			union
				{
				uint8_t bytes[56];
				uint16_t words[28];
				uint32_t dwords[14];
				uint64_t qwords[7];
				} data;
			
			struct Type
				{
				static const uint64_t TERMINATE=-1;
				static const uint64_t NOP=0;
				static const uint64_t ACKNOLEDGEMENT=1;
				static const uint64_t WINDOWTITLE_SET=2;
				};
			
			};
		Herbs::String stringGet(Message& msg);
		
		
		}
	}

#endif
