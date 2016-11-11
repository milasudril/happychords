//@	{"targets":[{"name":"mat4.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_MAT4_HPP
#define HAPPYCHORDS_MAT4_HPP

#include "vectortype.hpp"
#include <lv2plug/visibility.hpp>

namespace Happychords
	{
	template<class T>
	class PRIVATE mat4
		{
		public:
			constexpr T& operator()(int row,int col) noexcept
				{return cols[col][row];}
		  
			constexpr T operator()(int row,int col) const noexcept
				{return cols[col][row];}
		  
			constexpr vec4<T>& column(int col) noexcept
				{return cols[col];}
		  
			constexpr mat4& operator+=(const mat4& m) noexcept
				{
				for(int k=0;k<4;++k)
					{cols[k]+=m.cols[k];}
				return *this;
				}
		  
			constexpr mat4& operator-=(const mat4& m) noexcept
				{
				for(int k=0;k<4;++k)
					{cols[k]-=m.cols[k];}
				return *this;
				}
		  
			constexpr mat4& operator*=(T c) noexcept
				{
				for(int k=0;k<4;++k)
					{cols[k]*=c;}
				return *this;
				}
		  
			constexpr mat4& operator*=(const mat4& c) noexcept
				{
				for(int k=0;k<4;++k)
					{
					vec4<T> row{cols[0][k],cols[1][k],cols[2][k],cols[3][k]};
					for(int l=0;l<4;++l)
						{cols[l][k]=dot<T>(row,c.cols[l]);}
					}
				return *this;
				}
		  
			static constexpr mat4<T> identity() noexcept
				{
				mat4<T> ret{};
				ret.cols[0]=vec4<T>{1,0,0,0};
				ret.cols[1]=vec4<T>{0,1,0,0};
				ret.cols[2]=vec4<T>{0,0,1,0};
				ret.cols[3]=vec4<T>{0,0,0,1};
				return ret;
				}
		  
		private:
			vec4<T> cols[4];
		};
	  
	inline vec4<double> operator*(const mat4<double>& A,vec4<double> v)
		{
		vec4<double> ret;
		for(int k=0;k<4;++k)
			{
			auto row=vec4<double>{A(k,0),A(k,1),A(k,2),A(k,3)};
			ret[k]=dot<double>(row,v);
			}
		return ret;
		}
	  
	template<class T>
	mat4<T> operator*(T c,mat4<T> A)
		{return A*=c;}
	  
	template<class T>
	mat4<T> operator-(mat4<T> A,const mat4<T>& B)
		{return A-=B;}
	  

	inline vec4<double> block_div_twice(vec4<double> v,const mat4<double>& A)
		{
		vec4<double> ret;
		auto a=A(0,0);
		auto b=A(0,1);
		auto c=A(1,0);
		auto d=A(1,1);
		auto det_inv=1/(a*d - b*c);
		ret[0]=v[0]*d - v[1]*b;
		ret[1]=-(v[0]*c - v[1]*a);
		ret[2]=v[2]*d - v[3]*b;
		ret[3]=-(v[2]*c - v[3]*a);
		return ret*det_inv;
		}
	}

#endif
