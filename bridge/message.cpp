#ifdef __WAND__
target[name[message.o] type[object]]
#endif

#include "message.h"

#include <herbs/textconverter/textconverter.h>
#include <herbs/string/string.h>

Herbs::String Happychords::Bridge::stringGet(Message& msg)
	{
	msg.data.bytes[39]=0; //Make sure string is terminated!

	Herbs::TextConverter converter(Herbs::TextConverter::Encoding::UTF_8
		,ENCODING_LOCAL);
	size_t length_in=39;
	Herbs::String ret(converter.lengthFactorGet()*length_in);
	size_t n_bytes=converter.convert(msg.data.bytes,ret.begin(),length_in*sizeof(charsys_t));
	ret.lengthValidSet(n_bytes/sizeof(char_t));
	return ret;
	}
