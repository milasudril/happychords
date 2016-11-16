//@ {
//@	 "targets":[{"name":"gatesequence.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"gatesequence.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_GATESEQUENCE_HPP
#define HAPPYCHORDS_GATESEQUENCE_HPP

#include <lv2plug/visibility.hpp>
#include <vector>
#include <string>
#include <cstdio>

namespace Happychords
	{
	class PRIVATE GateSequence
		{
		public:
			struct Event
				{
				size_t time;
				enum class Type:decltype(time){NOTE_OFF,NOTE_ON,LOOP,NO_OPERATION};
				Type type;

				void valueSet(const std::string& key,const std::string& value);
				bool empty() const noexcept
					{return time==size_t(-1) || type==Type::NO_OPERATION;}
				};

			explicit GateSequence(FILE* src)
				{load(src);}

			explicit GateSequence(const int8_t* input_begin,const int8_t* input_end)
				{load(input_begin,input_end);}

			void load(FILE* src);

			void load(const int8_t* input_begin,const int8_t* input_end);

			void valueSet(const std::string& key,const std::string& value);

			const Event* begin() const noexcept
				{return m_events.data();}

			const Event* end() const noexcept
				{return m_events.data() + m_events.size();}

			size_t tpqnGet() const noexcept
				{return m_tpqn;}

		private:
			static inline void from_string(const std::string& value,GateSequence::Event::Type& type);

			size_t m_tpqn;
			std::string m_name;
			std::vector<Event> m_events;
		};
	}

#endif
