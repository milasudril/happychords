//@	{"targets":[{"name":"color.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_COLOR_HPP
#define HAPPYCHORDS_COLOR_HPP

#include <gtk/gtk.h>
#include <glm/glm.hpp>
#include <cstdint>

namespace Happychords
	{
	constexpr GdkColor make_color(const glm::vec3& color)
		{
		GdkColor ret
			{
			 0
			,static_cast<uint16_t>(color.r*0xffff)
			,static_cast<uint16_t>(color.g*0xffff)
			,static_cast<uint16_t>(color.b*0xffff)
			};
		return ret;
		};
	}

#endif
