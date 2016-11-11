//@	{"targets":[{"name":"sine.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_SINE_HPP
#define HAPPYCHORDS_SINE_HPP

#include "../common/arraystatic.hpp"
#include <cmath>

namespace Happychords
	{
	static constexpr auto sine() noexcept
		{
		ArrayStatic<float,1024> ret{};
		auto dx=1.0f/1024.0f;
		auto pi=std::acos(-1.0f);
		for(size_t k=0;k<ret.size();++k)
			{
			ret[k]=-std::cos(2.0f*pi*dx*k);
			}
		return ret;
		}
	}

#endif
