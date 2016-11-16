//@	{
//@	 "targets":[{"name":"container.hpp","type":"include"}]
//@	}

#ifndef HAPPYCHORDS_CONTAINER_HPP
#define HAPPYCHORDS_CONTAINER_HPP

#include <lv2plug/visibility.hpp>

namespace Happychords
	{
	class PRIVATE Container
		{
		public:
			virtual Container& widgetAdd(void* widget)=0;

		protected:
			~Container(){}
		};
	}

#endif