//@	{"targets":[{"name":"ringbuffer.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_RINGBUFFER_HPP
#define HAPPYCHORDS_RINGBUFFER_HPP

#include "../common/arraystatic.hpp"

namespace Happychords
	{
	template<class T,size_t N>
	class RingBuffer
		{
		public:
			static constexpr size_t npos=N;
			typedef T value_type;

			constexpr RingBuffer() noexcept:
				m_offset_read(0),m_offset_write(0),m_data{}
				{}

			constexpr void push(const T& element) noexcept
				{
				m_data[m_offset_write%N]=element;
				++m_offset_write;
				}

			constexpr T pop() noexcept
				{
				auto ret=m_data[m_offset_read%N];
				++m_offset_read;
				return ret;
				}

			constexpr bool full() const noexcept
				{return size()==npos;}

			constexpr bool empty() const noexcept
				{return size()==0;}

			constexpr size_t size() const noexcept
				{return m_offset_write - m_offset_read;}
				

		private:
			size_t m_offset_read;
			size_t m_offset_write;
			ArrayStatic<T,N> m_data;
		};
	};

#endif
