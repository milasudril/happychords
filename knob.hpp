//@	{
//@	 "targets":[{"name":"knob.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"knob.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_KNOB_HPP
#define HAPPYCHORDS_KNOB_HPP

#include <lv2plug/visibility.hpp>
#include <cmath>
#include <glm/glm.hpp>

namespace Happychords
	{
	class Container;
	class KnobBase
		{
		public:
			KnobBase(Container& parent,const char* caption,double min,double max,double value);
			~KnobBase();

			void valueSet(double value) noexcept;

			double valueGet() const noexcept
				{return m_value;}

			double angleGet() const noexcept
				{return angleGetImpl(m_value,m_min,m_max);}

			double valueGet(double angle) const noexcept
				{return valueGetImpl(angle,m_min,m_max);}

			void colorSet(const glm::vec3& color) noexcept;

			const glm::vec3& colorGet() const noexcept
				{return m_color;}

			void captionColorSet(const glm::vec3& color) noexcept;

			void entryBackgroundSet(const glm::vec3& color) noexcept;

			void entryForegroundSet(const glm::vec3& color) noexcept;

			virtual void changeEmmit() noexcept=0;

		private:
			void* m_box;
			void* m_dial;
			void* m_dial_box;
			void* m_entry;
			double m_min;
			double m_max;
			double m_value;
			glm::vec3 m_color;

			static constexpr double pi=std::acos(-1.0);

			static constexpr double angleGetImpl(double value,double min,double max) noexcept
				{
				auto xi=(value - min)/(max - min);
				return (1.0 - xi)*(-7.0*pi/6.0) + xi*pi/6;
				}

			static constexpr double valueGetImpl(double angle,double min,double max) noexcept
				{
				auto xi=(angle + 7.0*pi/6.0)/(pi/6.0 + 7.0*pi/6.0);
				return (1.0 - xi)*min + xi*max;
				}
		};

	template<class Paraminfo,class EventHandler
		,std::enable_if_t<
			std::is_same< float,std::remove_const_t<typename Paraminfo::type_logical> >::value
		,int> n=0>
	class PRIVATE Knob:private KnobBase
		{
		public:
			Knob(Container& parent,EventHandler& handler):KnobBase(parent
				,Paraminfo::name(),Paraminfo::minimum(),Paraminfo::maximum(),Paraminfo::valueDefault())
				,m_handler(handler)
				{}

			using KnobBase::valueSet;
			using KnobBase::angleGet;
			using KnobBase::valueGet;
			using KnobBase::colorSet;
			using KnobBase::colorGet;
			using KnobBase::captionColorSet;
			using KnobBase::entryBackgroundSet;
			using KnobBase::entryForegroundSet;

		private:
			void changeEmmit() noexcept
				{m_handler.template eventProcess< Paraminfo::id() >(*this);}
			EventHandler& m_handler;
		};
	
	};

#endif