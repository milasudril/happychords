//@	{"targets":[{"name":"vectortype.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_VECTORTYPE_HPP
#define HAPPYCHORDS_VECTORTYPE_HPP

#include "vectortype.hpp"

namespace Happychords
	{
	template<class T>
	using vec4 __attribute__ ((vector_size (4*sizeof(T))))=T;
	}

#endif
