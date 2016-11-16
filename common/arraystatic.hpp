//@	{
//@	 "targets":[{"name":"arraystatic.hpp","type":"include"}]
//@	}

#ifndef HAPPYCHORDS_ARRAYSTATIC_HPP
#define HAPPYCHORDS_ARRAYSTATIC_HPP

#include <lv2plug/visibility.hpp>

namespace Happychords
	{
	template<class T,size_t N>
	class ArrayStatic
		{
		public:
			constexpr ArrayStatic() noexcept:m_data{}
            	{}

			static constexpr size_t size() noexcept
				{return N;}

			constexpr T& operator[](size_t k) noexcept
				{return m_data[k];}

			constexpr const T& operator[](size_t k) const noexcept
				{return m_data[k];}

			constexpr const T* begin() const noexcept
				{return m_data;}

			constexpr const T* end() const noexcept
				{return m_data + size();}

			constexpr T* begin() noexcept
				{return m_data;}

			constexpr T* end() noexcept
				{return m_data + size();}

		private:
			T m_data[N];
		};
	}

#endif
