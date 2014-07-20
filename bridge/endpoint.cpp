#ifdef __WAND__
target[name[endpoint.o] type[object]]
#endif

#include "endpoint.h"
#include <herbs/stringformat/stringformat.h>
#include <herbs/intformat/intformat.h>
#include <herbs/directory/directory.h>

Happychords::Bridge::Endpoint::Endpoint(const Herbs::Directory& dir)
	{
	auto ptr=dir.itemsBegin();
	size_t k=0;
	while(ptr!=dir.itemsEnd())
		{
		switch(k)
			{
			case 0:
				ipSet(*ptr);
				break;
			case 1:
				portSet(Herbs::toInt<uint64_t>(ptr->begin()));
				return;
			}
		++k;
		++ptr;
		}
	}
	
Happychords::Bridge::Endpoint&
Happychords::Bridge::Endpoint::ipSet(const Herbs::String& ip)
	{
	m_ip.clear();
	auto ptr=ip.begin();
	while(ptr!=ip.end())
		{
		m_ip.append(*ptr);
		++ptr;
		}
	return *this;
	}

Herbs::String Happychords::Bridge::Endpoint::ipGet() const
	{
	Herbs::String ret(m_ip.length());
	auto ptr=m_ip.begin();
	while(ptr!=m_ip.end())
		{
		ret.append(*ptr);
		++ptr;
		}
	return ret;
	}

Herbs::String Happychords::Bridge::Endpoint::spellstringGet() const
	{
	return Herbs::format(STR("%0;%1"),
		{
		ipGet().begin()
		,Herbs::IntFormat<uint64_t>(m_port)
		});
	}


