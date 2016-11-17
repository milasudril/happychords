//@	{"targets":[{"name":"idgenerator.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_IDGENERATOR_HPP
#define HAPPYCHORDS_IDGENERATOR_HPP

namespace Happychords
	{
	template<class Freelist>
	class IdGenerator
		{
		public:
			IdGenerator() noexcept:m_id_next(-1){}

			static constexpr typename Freelist::value_type id_null=Freelist::npos;

			auto idGet() noexcept
				{
				if(m_freelist.empty())
					{
					if(m_id_next==id_null-1)
						{return id_null;}
					++m_id_next;
					return m_id_next;
					}
				return m_freelist.pop();
				}

			IdGenerator& idRelease(const typename Freelist::value_type& id)
				{
				m_freelist.push(id);
				return *this;
				}

			IdGenerator& reset() noexcept
				{
				m_freelist.clear();
				m_id_next=-1;
				return *this;
				}

		private:
			Freelist m_freelist;
			typename Freelist::value_type m_id_next;
		};
	}
#endif
