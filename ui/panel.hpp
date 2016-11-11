//@	{
//@	 "targets":[{"name":"panel.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"panel.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_PANEL_HPP
#define HAPPYCHORDS_PANEL_HPP

#include "container.hpp"
#include <glm/glm.hpp>

namespace Happychords
	{
	class PRIVATE Panel:public Container
		{
		public:
			Panel(Container& parent,const char* caption);
			~Panel();

			virtual Panel& widgetAdd(void* widget);

			Panel& paddingSet(unsigned int padding) noexcept
				{
				m_padding=padding;
				return *this;
				}

			void captionColorSet(const glm::vec3& color) noexcept;

			void borderColorSet(const glm::vec3& color) noexcept;

			const glm::vec3& borderColorGet() const noexcept
				{return m_border_color;}

		private:
			void* m_handle;
			unsigned int m_padding;
			glm::vec3 m_border_color;
		};
	}

#endif