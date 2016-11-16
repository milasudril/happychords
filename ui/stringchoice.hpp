//@	{
//@	 "targets":[{"name":"stringchoice.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"stringchoice.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_STRINGCHOICE_HPP
#define HAPPYCHORDS_STRINGCHOICE_HPP

#include <lv2plug/visibility.hpp>
#include <glm/glm.hpp>
#include <utility>

namespace Happychords
	{
	class Container;
	class PRIVATE StringchoiceBase
		{
		public:
			StringchoiceBase(Container& parent,const char* caption);
			~StringchoiceBase();

			void choiceAddAndSet(const char* str) noexcept;

			std::pair<int,const char*> valueGet(double angle) const noexcept;

			void captionColorSet(const glm::vec3& color) noexcept;

			void entryBackgroundSet(const glm::vec3& color) noexcept;

			void entryForegroundSet(const glm::vec3& color) noexcept;

			virtual void changeEmmit() noexcept=0;

		private:
			void* m_box;
			void* m_label;
			void* m_combo;
		};

	template<class Paraminfo,class EventHandler
		,std::enable_if_t<
			std::is_same< float,std::remove_const_t<typename Paraminfo::type_logical> >::value
		,int> n=0>
	class PRIVATE Stringchoice:public StringchoiceBase
		{
		public:
			Stringchoice(Container& parent,EventHandler& handler):
				StringchoiceBase(parent,Paraminfo::name())
				,m_handler(handler)
				{}
		private:
			void changeEmmit() noexcept
				{m_handler.template eventProcess< Paraminfo::id() >(*this);}
			EventHandler& m_handler;
		};
	
	};

#endif