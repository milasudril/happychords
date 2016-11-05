//@	{"targets":[{"name":"framepair.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_FRAMEPAIR_HPP
#define HAPPYCHORDS_FRAMEPAIR_HPP

#include "vectortype.hpp"

namespace Happychords
	{
	class Framepair
		{
		public:
			explicit constexpr Framepair() noexcept:m_vec{0.0f,0.0f,0.0f,0.0f}{}
			constexpr Framepair(vec4<float> val) noexcept:m_vec{val}{}
			explicit constexpr Framepair(float a,float b,float c,float d) noexcept:
				m_vec{a,b,c,d}
				{}
		  
			template<int n>
			constexpr float left() const noexcept
				{
				static_assert(n>=0 && n<2,"A Framepair only has two frames");
				return m_vec[2*n];
				}
		  
			template<int n>
			constexpr float& left() noexcept
				{
				static_assert(n>=0 && n<2,"A Framepair only has two frames");
				return m_vec[2*n];
				}
		  
			template<int n>
			constexpr float& right() noexcept
				{
				static_assert(n>=0 && n<2,"A Framepair only has two frames");
				return m_vec[2*n + 1];
				}
		  
			template<int n>
			constexpr float right() const noexcept
				{
				static_assert(n>=0 && n<2,"A Framepair only has two frames");
				return m_vec[2*n + 1];
				}
		  
			constexpr Framepair& operator+=(Framepair p) noexcept
				{
				m_vec+=p.m_vec;
				return *this;
				}
		  
			constexpr Framepair& operator-=(Framepair p) noexcept
				{
				m_vec+=p.m_vec;
				return *this;
				}
		  
			constexpr Framepair& operator*=(Framepair p) noexcept
				{
				m_vec*=p.m_vec;
				return *this;
				}
		  
			constexpr Framepair& operator/=(Framepair p) noexcept
				{
				m_vec/=p.m_vec;
				return *this;
				}
		  
			constexpr Framepair& operator*=(float c) noexcept
				{
				m_vec*=c;
				return *this;
				}
		  
			constexpr Framepair& operator/=(float c) noexcept
				{
				m_vec/=c;
				return *this;
				}
		
		private:
			vec4<float> m_vec;
		};

	constexpr inline Framepair operator+(Framepair a,Framepair b) noexcept
		{return a+=b;}

	constexpr inline Framepair operator-(Framepair a,Framepair b) noexcept
		{return a-=b;}

	constexpr inline Framepair operator*(Framepair a,Framepair b) noexcept 
		{return a*=b;}

	constexpr inline Framepair operator/(Framepair a,Framepair b) noexcept
		{return a/=b;}

	constexpr inline Framepair operator*(float c,Framepair b) noexcept
		{return b*=c;}

	constexpr inline Framepair operator/(Framepair b,float c) noexcept
		{return b/=c;}

	};

#endif
