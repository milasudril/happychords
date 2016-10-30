//@	{"targets":[{"name":"cairosurface.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_CAIROSURFACE_HPP
#define HAPPYCHORDS_CAIROSURFACE_HPP

#include <lv2plug/visibility.hpp>
#include <cairo.h>
#include <memory>

namespace Happychords
	{
	class PRIVATE CairoSurface
		{
		public:
			explicit CairoSurface(cairo_surface_t* obj):m_ptr(obj,Deleter{})
				{}

			operator cairo_surface_t*() noexcept
				{return m_ptr.get();}

			operator const cairo_surface_t*() const noexcept
				{return m_ptr.get();}

		private:
			struct PRIVATE Deleter
				{
				void operator()(cairo_surface_t* surface)
					{cairo_surface_destroy(surface);}
				};
			std::unique_ptr<cairo_surface_t,Deleter> m_ptr;
		};

	inline auto cairo_image_surface_get_width(const CairoSurface& surface)
		{return ::cairo_image_surface_get_width(const_cast<CairoSurface&>(surface));}

	inline auto cairo_image_surface_get_height(const CairoSurface& surface)
		{return ::cairo_image_surface_get_height(const_cast<CairoSurface&>(surface));}

	inline auto cairo_set_source_surface(cairo_t* context,const CairoSurface& surface,double x,double y)
		{return ::cairo_set_source_surface(context,const_cast<CairoSurface&>(surface),x,y);}

	}

#endif