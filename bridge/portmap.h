#ifdef __WAND__
target[name[portmap.h] type[include]]
dependency[portmap.o]
#endif

#ifndef HAPPYCHORDS_BRIDGE_PORTMAP_H
#define HAPPYCHORDS_BRIDGE_PORTMAP_H

#include <cstddef>
#include <herbs/chartype/chartype.h>

namespace Herbs
	{
	class Directory;
	template<class T>
 	class Stringbase;
	
	typedef Stringbase<char_t> String;
	}

namespace Happychords
	{
	namespace Bridge
		{
		struct Portmap
			{
			void valuesSet(const Herbs::Directory& dir);
			operator Herbs::String() const;
			size_t ports[2];
			};
		}
	}

#endif