//@	{"targets":[{"name":"cairocontext.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_CAIROCONTEXT_HPP
#define HAPPYCHORDS_CAIROCONTEXT_HPP

#include <lv2plug/visibility.hpp>
#include <cairo.h>
#include <memory>

namespace Happychords
	{
	class PRIVATE CairoContext
		{
		public:
			explicit CairoContext(cairo_t* obj):m_ptr(obj,Deleter{})
				{}

			operator cairo_t*() noexcept
				{return m_ptr.get();}

			operator const cairo_t*() const noexcept
				{return m_ptr.get();}

		private:
			struct PRIVATE Deleter
				{
				void operator()(cairo_t* surface)
					{cairo_destroy(surface);}
				};
			std::unique_ptr<cairo_t,Deleter> m_ptr;
		};
	}

#endif