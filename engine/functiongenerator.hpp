//@	{
//@	 "targets":[{"name":"functiongenerator.hpp","type":"include"}]
//@	}

#ifndef HAPPYCHORDS_FUNCTIONGENERATOR_HPP
#define HAPPYCHORDS_FUNCTIONGENERATOR_HPP

#include "../common/arraystatic.hpp"
#include <cassert>

namespace Happychords
	{
	template<class T,size_t N>
	class PRIVATE FunctionGenerator
		{
		public:
			FunctionGenerator() noexcept:m_phi(0){}

			void generate(double f,float a,const ArrayStatic<T,N>& source
				,float* dest,size_t n_frames) noexcept;
				
			void generate(double f,float a,const ArrayStatic<T,N>& source,float& dest) noexcept;

			void generate(double f,float a,double phi_0
				,const ArrayStatic<T,N>& source
				,float* dest,size_t n_frames) noexcept;
				
			void generate(double f,float a,double phi_0
				,const ArrayStatic<T,N>& source
				,float& dest) noexcept;

			void phaseSet(double phi) noexcept
				{
				assert(phi < N);
				m_phi=phi;
				}

			void phaseSet(int64_t position,double f) noexcept
				{
				auto temp=position*f;
				m_phi=(temp - int(temp))*N;
				}

		private:
			double m_phi;
		};

	template<class T,size_t N>
	void FunctionGenerator<T,N>::generate(double f,float a,const ArrayStatic<T,N>& source
		,float* dest,size_t n_frames) noexcept
		{
		auto ptr_end=dest+n_frames;
		auto phi=m_phi;
		while(dest!=ptr_end)
			{
			auto i=static_cast<size_t>(phi);
			*dest=a*source[i];
			
			phi+=source.size()*f;
			if(phi>=source.size())
				{phi-=source.size();}
			++dest;
			}
		m_phi=phi;
		}
		
	template<class T,size_t N>
	void FunctionGenerator<T,N>::generate(double f,float a,const ArrayStatic<T,N>& source,float& dest) noexcept
		{
		auto phi=m_phi;
		auto i=static_cast<size_t>(phi);
		dest=a*source[i];
		phi+=source.size()*f;
		if(phi>=source.size())
			{phi-=source.size();}
		m_phi=phi;
		}

	template<class T,size_t N>
	void FunctionGenerator<T,N>::generate(double f,float a,double phi_0
		,const ArrayStatic<T,N>& source
		,float* dest,size_t n_frames) noexcept
		{
		auto ptr_end=dest+n_frames;
		auto phi=m_phi + phi_0;
		if(phi>=source.size())
			{phi-=source.size();}
		while(dest!=ptr_end)
			{
			auto i=static_cast<size_t>(phi);
			*dest=a*source[i];
			
			phi+=source.size()*f;
			if(phi>=source.size())
				{phi-=source.size();}
			++dest;
			}
		m_phi=phi - phi_0;
		if(m_phi<0)
			{m_phi+=source.size();}
		}
		
	template<class T,size_t N>
	void FunctionGenerator<T,N>::generate(double f,float a,double phi_0
		,const ArrayStatic<T,N>& source	,float& dest) noexcept
		{
		auto phi=m_phi + phi_0;
		if(phi>=source.size())
			{phi-=source.size();}
		
		auto i=static_cast<size_t>(phi);
		dest=a*source[i];
			
		phi+=source.size()*f;
		if(phi>=source.size())
			{phi-=source.size();}
		
		m_phi=phi - phi_0;
		if(m_phi<0)
			{m_phi+=source.size();}
		}
	}

#endif
