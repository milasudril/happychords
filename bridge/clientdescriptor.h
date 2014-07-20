#ifdef __WAND__
target[name[clientdescriptor.h] type[include]]
dependency[clientdescriptor.o]
#endif

#ifndef HAPPYCHORDS_BRIDGE_CLIENTDESCRIPTOR_H
#define HAPPYCHORDS_BRIDGE_CLIENTDESCRIPTOR_H

#include <herbs/string/string.h>

namespace Herbs
	{
	class Directory;
	}

namespace Happychords
	{
	namespace Bridge
		{
		struct ClientDescriptor
			{
			public:
				ClientDescriptor(){}
				
				ClientDescriptor(const Herbs::String& _ip,uint64_t _pid
					,uint64_t _obj)
					{
					ipSet(_ip);
					pidSet(_pid);
					objectSet(_obj);
					}
				
				void valuesSet(const Herbs::Directory& dir);
				operator Herbs::String() const;
				
				Herbs::String ipGet() const;
				const Herbs::Stringbase<char>& ipGetRaw() const
					{return ip;}
				void ipSet(const Herbs::String& ip);
				
				uint64_t pidGet() const
					{return pid;}
				void pidSet(uint64_t pid_new)
					{pid=pid_new;}
				
				uint64_t objectGet() const
					{return object;}
				void objectSet(uint64_t obj_new)
					{object=obj_new;}
				
				
				
			
			private:							
				Herbs::Stringbase<char> ip;
				uint64_t pid;
				uint64_t object;
			};
		}
	}
	

#endif

