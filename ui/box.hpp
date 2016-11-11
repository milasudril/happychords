//@	{
//@	 "targets":[{"name":"box.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"box.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_BOX_HPP
#define HAPPYCHORDS_BOX_HPP

#include "container.hpp"

namespace Happychords
	{
	class PRIVATE Box:public Container
		{
		public:
			enum class InsertMode:unsigned int{NORMAL,EXPAND,FILL};

			Box(Container& parent,bool horizontal=0);
			~Box();

			virtual Box& widgetAdd(void* widget);

			Box& insertModeSet(InsertMode mode) noexcept
				{
				m_mode=mode;
				return *this;
				}

			Box& paddingSet(unsigned int padding) noexcept
				{
				m_padding=padding;
				return *this;
				}


		private:
			void* m_handle;
			InsertMode m_mode;
			unsigned int m_padding;
		};
	}

#endif