#ifdef __WAND__
target[name[clientdescriptor.o] type[object]]
#endif

#include "clientdescriptor.h"
#include <herbs/directory/directory.h>
#include <herbs/exceptionmissing/exceptionmissing.h>
#include <herbs/stringformat/stringformat.h>

void Happychords::Bridge::ClientDescriptor::valuesSet(const Herbs::Directory& dir)
	{
	auto dir_me=dir.directoryLastGet(STR("client"));
	if(dir_me==nullptr)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
		
	auto items=dir_me->itemsBegin();
	size_t k=0;
	while(items!=dir_me->itemsEnd())
		{
		switch(k)
			{
			case 0:
				ipSet(*items);
				break;
			case 1:
				pid=Herbs::toInt<size_t>(items->begin());
				break;
			case 2:
				object=Herbs::toInt<size_t>(items->begin());
				break;
			default:
				return;
			}
		++k;
		++items;
		}
	}

Happychords::Bridge::ClientDescriptor::operator Herbs::String() const
	{

	return Herbs::format(STR("client[%0;%1;%2]")
		,{
		ipGet().begin()
		,Herbs::IntFormat<size_t>(pid)
		,Herbs::IntFormat<size_t>(object)
		});
	}

void Happychords::Bridge::ClientDescriptor::ipSet(const Herbs::String& string)
	{
	auto ptr=string.begin();
	ip.clear();
	while(ptr!=string.end())
		{
		ip.append(*ptr);
		++ptr;
		}
	}

Herbs::String Happychords::Bridge::ClientDescriptor::ipGet() const
	{
	Herbs::String ret;
	auto ptr=ip.begin();
	while(ptr!=ip.end())
		{
		ret.append(*ptr);
		++ptr;
		}
	return ret;
	}