//@	{"targets":[{"name":"stereomixer.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_STEREOMIXER_HPP
#define HAPPYCHORDS_STEREOMIXER_HPP

namespace Happychords
	{
	static void addToMix(const float* src,float gain,float xi
		,float* buffer_left,float* buffer_right,size_t n)
		{
		auto xi_comp=1.0f - xi;
		while(n!=0)
			{
			auto v=*src;
			*buffer_left+=gain*xi_comp*v;
			*buffer_right+=gain*xi*v;
			++buffer_left;
			++buffer_right;
			++src;
			--n;
			}
		}
	}

#endif
