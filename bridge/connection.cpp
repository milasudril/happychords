#ifdef __WAND__
target[name[connection.o] type[object]]
#endif

#include "connection.h"
#include "message.h"
#include <herbs/directory/directory.h>
#include <herbs/exceptionmissing/exceptionmissing.h>
#include <herbs/stringformat/stringformat.h>
#include <herbs/process/process.h>

#include <cstring>

namespace
	{
	const Herbs::Directory& directoryGet(const Herbs::Directory& dir
		,const char_t* name)
		{
		auto dir_me=dir.directoryLastGet(name);
		if(dir_me==nullptr)
			{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
		return *dir_me;
		}
	}

Happychords::Bridge::Connection::Connection(const Herbs::Directory& dir):
	end_in(directoryGet(dir,STR("port_in"))),end_out(directoryGet(dir,STR("port_out")))
	{
	socket_in.bind(end_in.portGet(),end_in.ipGetRaw().begin());
	}
	
Happychords::Bridge::Connection::Connection(Endpoint&& in,Endpoint&& out):
	end_in(std::move(in)),end_out(std::move(out))
	{
	socket_in.bind(end_in.portGet(),end_in.ipGetRaw().begin());
	}
	
Herbs::String Happychords::Bridge::Connection::spellstringGet(bool inout_swap) const
	{
	if(inout_swap)
		{
		return Herbs::format(STR("port_in[%1]port_out[%0]")
			,{
			 end_in.spellstringGet().begin()
			,end_out.spellstringGet().begin()
			});
		}
	else
		{
		return Herbs::format(STR("port_in[%0]port_out[%1]")
			,{
			 end_in.spellstringGet().begin()
			,end_out.spellstringGet().begin()
			});
		}
	}

bool Happychords::Bridge::Connection::messageGet(Message& msg)
	{
	memset(&msg,0,sizeof(msg));
	if(socket_in.receive(&msg,sizeof(msg))!=sizeof(msg))
		{return 0;}
	return 1;
	}
	
bool Happychords::Bridge::Connection::messageSend(const Message& msg)
	{
	return socket_out.send(&msg,sizeof(msg),end_out.portGet()
		,end_out.ipGetRaw().begin())==sizeof(msg);
	}
