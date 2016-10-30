//@	{"targets":[{"name":"sawtooth.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_SAWTOOTH_HPP
#define HAPPYCHORDS_SAWtOOTH_HPP

#include "arraystatic.hpp"
#include <cmath>

namespace Happychords
	{
	static constexpr auto sawtooth() noexcept
		{
		ArrayStatic<float,1024> ret{};
		auto dx=1.0f/1024.0f;
		auto steepness=60.0f;
		auto x0=-0.5f;
		for(size_t k=0;k<ret.size();++k)
			{
			auto x=x0 + dx*k;
			ret[k]=2.0f*x*(std::tanh(steepness*(x + 0.5f)) 
				+ std::tanh(steepness*(0.5f - x)) - 1.0f);
			}
		return ret;
		}
	}

#endif
