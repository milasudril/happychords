//@	{
//@	 "targets":[{"name":"imageresource.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"imageresource.o","rel":"implementation"}]
//@	}


#ifndef HAPPYCHORDS_IMAGERESOURCE_HPP
#define HAPPYCHORDS_IMAGERESOURCE_HPP

#include "cairosurface.hpp"

namespace Happychords
	{
	CairoSurface imageResourceLoad(const uint8_t* begin,const uint8_t* end);
	}

#endif