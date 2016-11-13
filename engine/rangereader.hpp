//@	{"targets":[{"name":"rangereader.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_RANGEREADER_HPP
#define HAPPYCHORDS_RANGEREADER_HPP

#include <lv2plug/visibility.hpp>
#include <cstdio> //We want EOF constant to mimic the FILE behaviour

namespace Happychords
	{
	template<class Iterator>
	class PRIVATE RangeReader
		{
		public:
			constexpr RangeReader(Iterator begin,Iterator end) noexcept:
				m_pos(begin),m_end(end)
				{}

			constexpr int getc() noexcept
				{
				static_assert(std::is_same<int8_t
					,typename std::iterator_traits<Iterator>::value_type>::value
					,"Wrong iterator type");
				auto ret=m_pos==m_end?EOF:*m_pos;
				++m_pos;
				return ret;
				}

		private:
			Iterator m_pos;
			Iterator m_end;
		};

	template<class Iterator>
	constexpr inline int getc(RangeReader<Iterator>& reader) noexcept
		{return reader.getc();}
	}

#endif
