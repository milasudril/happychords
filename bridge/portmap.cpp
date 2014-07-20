#ifdef __WAND__
target[name[portmap.o] type[object]]
#endif

#include "portmap.h"
#include <herbs/directory/directory.h>
#include <herbs/stringformat/stringformat.h>
#include <herbs/exceptionmissing/exceptionmissing.h>

void Happychords::Bridge::Portmap::valuesSet(const Herbs::Directory& dir)
	{
	auto dir_me=dir.directoryLastGet(STR("ports"));
	if(dir_me==nullptr)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	auto items=dir_me->itemsBegin();
	size_t k=0;
	while(items!=dir_me->itemsEnd() && k!=2)
		{
		ports[k]=Herbs::toInt<size_t>(items->begin());
		++k;
		++items;
		}
	}

Happychords::Bridge::Portmap::operator Herbs::String() const
	{
	return Herbs::format(STR("ports[%0;%1]")
		,{
		Herbs::IntFormat<size_t>(ports[0])
		,Herbs::IntFormat<size_t>(ports[1])
		});
	}