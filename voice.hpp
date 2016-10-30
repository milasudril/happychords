//@	{"targets":[{"name":"voice.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_VOICE_HPP
#define HAPPYCHORDS_VOICE_HPP

#include "functiongenerator.hpp"
#include "stereomixer.hpp"
#include <cmath>
#include <random>

namespace Happychords
	{
	template<size_t N>
	class PRIVATE Voice
		{
		public:
			Voice():m_amplitude(0),m_f(0)
				{
				std::random_device rd;
				std::uniform_real_distribution<double> U(0,N);
				for(size_t k=0;k<m_generators.size();++k)
					{m_generators[k].phaseSet(U(rd));}
				}

			void generate(const ArrayStatic<float,N>& waveform
				,double detune,bool suboct
				,float* buffer_temp,float* buffer_left,float* buffer_right,size_t n);

			float amplitude() const noexcept
				{return m_amplitude;}

			void start(float f,float a) noexcept
				{
				m_f=f;
				m_amplitude=a;
				}

			void stop() noexcept
				{m_amplitude=0.0f;}

		private:
			float m_amplitude;
			float m_f;
			ArrayStatic<FunctionGenerator<float,N>,11> m_generators;
		};

	template<size_t N>
	void Voice<N>::generate(const ArrayStatic<float,N>& waveform
		,double detune,bool suboct
		,float* buffer_temp,float* buffer_left,float* buffer_right,size_t n)
		{
		static_assert(m_generators.size()!=0,"No generators?");

		auto d_xi=1.0/(m_generators.size() - 1);
		auto df=std::exp2(detune*d_xi/12.0);
		auto f_0=exp2(-0.5*detune/12.0);
		auto f_base=m_f;
		auto a=m_amplitude;
		auto gain=1.0f/m_generators.size();
		f_base*=f_0;

		if(suboct)
			{
			for(size_t k=0;k<m_generators.size();++k)
				{
				m_generators[k].generate(k%2?0.5f*f_base:f_base,a,waveform,buffer_temp,n);
				f_base*=df;
				addToMix(buffer_temp,gain,k*d_xi,buffer_left,buffer_right,n);
				}
			}
		else
			{
			for(size_t k=0;k<m_generators.size();++k)
				{
				m_generators[k].generate(f_base,a,waveform,buffer_temp,n);
				f_base*=df;
				addToMix(buffer_temp,gain,k*d_xi,buffer_left,buffer_right,n);
				}
			}
		}
	}

#endif