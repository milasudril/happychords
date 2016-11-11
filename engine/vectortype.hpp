//@	{"targets":[{"name":"vectortype.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_VECTORTYPE_HPP
#define HAPPYCHORDS_VECTORTYPE_HPP

#include "vectortype.hpp"

namespace Happychords
	{
	template<class T>
	using vec4 __attribute__ ((vector_size (4*sizeof(T))))=T;

    template<class T>
    inline T dot(vec4<T> a,vec4<T> b)
    	{
        T ret=0;
        for(int k=0;k<4;++k)
        	{ret+=a[k]*b[k];}
        return ret;
        }
	}

#endif
