//@	{
//@	 "targets":[{"name":"switch.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"switch.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_SWITCH_HPP
#define HAPPYCHORDS_SWITCH_HPP

#include <lv2plug/visibility.hpp>
#include <cmath>
#include <glm/glm.hpp>

namespace Happychords
	{
	class Container;
	class PRIVATE SwitchBase
		{
		public:
			enum class State:unsigned int{UP,DOWN};

			SwitchBase(Container& container,const char* caption,State state_init);
			~SwitchBase();

			void stateSet(State state_new) noexcept;

			State stateGet() const noexcept
				{return m_state;}

			void backgroundSet(const glm::vec3& color) noexcept;

			void captionColorSet(const glm::vec3& color) noexcept;

			const glm::vec3& backgroundGet() const noexcept
				{return m_background;}

			virtual void changeEmmit() noexcept=0;

		private:
			void* m_box;
			void* m_switch;
			State m_state;
			glm::vec3 m_background;
		};

	template<class Paraminfo,class EventHandler
		,std::enable_if_t< std::is_same<bool,typename Paraminfo::type_logical>::value ,int> n=0>
	class PRIVATE Switch:private SwitchBase
		{
		public:
			Switch(Container& parent,EventHandler& handler):
				SwitchBase(parent,Paraminfo::name(),SwitchBase::State::UP)
				,m_handler(handler)
				{}

			using SwitchBase::stateGet;
			using SwitchBase::stateSet;
			using SwitchBase::backgroundSet;
			using SwitchBase::captionColorSet;

		private:
			void changeEmmit() noexcept
				{m_handler.template eventProcess< Paraminfo::id() >(*this);}
			EventHandler& m_handler;
		};
	
	};

#endif