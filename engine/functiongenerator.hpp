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

			void phaseSet(double phi) noexcept
				{
				assert(phi < static_cast<size_t>(N));
				m_phi=phi;
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
	}

#endif
