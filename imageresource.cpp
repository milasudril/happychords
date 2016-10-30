//@	{
//@	"targets":
//@		[{
//@		 "name":"imageresource.o","type":"object"
//@		,"pkgconfig_libs":["cairo"]
//@		}]
//@	}

#include "imageresource.hpp"
#include <cstring>

using namespace Happychords;

namespace
	{
	struct PRIVATE ReadState
		{
		const uint8_t* pos_read;
		size_t n_left;
		};
	}

static cairo_status_t memReader(void* read_state,unsigned char* output,unsigned int length)
	{
	auto pointers=reinterpret_cast<ReadState*>(read_state);
	auto n=std::min(static_cast<size_t>(length),pointers->n_left);
	if(n!=0 && pointers->n_left==0)
		{return CAIRO_STATUS_READ_ERROR;}
	memcpy(output,pointers->pos_read,n);
	pointers->n_left-=n;
	pointers->pos_read+=n;
	return CAIRO_STATUS_SUCCESS;
	}

CairoSurface Happychords::imageResourceLoad(const uint8_t* begin,const uint8_t* end)
	{
	ReadState rs{begin,static_cast<size_t>(end - begin)};
	return CairoSurface(cairo_image_surface_create_from_png_stream(memReader,&rs));
	}
