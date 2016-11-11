//@	{"targets":[{"name":"voice.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_VOICE_HPP
#define HAPPYCHORDS_VOICE_HPP

#include "functiongenerator.hpp"
#include "stereomixer.hpp"
#include "adsr.hpp"
#include "filter.hpp"
#include <cmath>
#include <random>

namespace Happychords
	{
	template<size_t N>
	class PRIVATE Voice
		{
		public:
			Voice():m_amplitude(0.0f,0.0f,0.0f,0.0f),m_f(0),m_gain(0),m_f_0(1.0f)
				,m_keytrack(1.0f),m_key(-1)
				{
				std::random_device rd;
				std::uniform_real_distribution<double> U(0,N);
				for(size_t k=0;k<m_generators.size();++k)
					{m_generators[k].phaseSet(U(rd));}
				}

			void generate(const ArrayStatic<float,N>& waveform
				,double detune,bool suboct
				,float* buffer_temp,Framepair* stereo_out,size_t n) noexcept;

			void filterApply(const Framepair* buffer_in
				,Filter::Params filter,float* buffer_lfo,Framepair* buffer_out,size_t n) noexcept;

			void modulate(const Framepair* buffer_in
				,Adsr::Params adsr,Framepair* buffer_out,size_t n) noexcept;

			float amplitude() const noexcept
				{return m_amplitude.left<0>();}

			void start(float f,float a,Adsr::Params adsr,float keytrack
				,int8_t key) noexcept
				{
				m_f=f;
				m_gain=a;
				m_modulator.attack();
				auto a_1=m_modulator.stateUpdate(adsr,0.0f);
				m_filter.stateReset();
				m_amplitude=Framepair{0.0f,0.0f,a_1,a_1};
				m_key=key;
				m_keytrack=std::exp2((key-69)*keytrack/12.0f);
				}

			void stop(int8_t key) noexcept
				{
				if(key==m_key)
					{m_modulator.release();}
				}

			bool started() const noexcept
				{return m_modulator.started();}

		private:
			ArrayStatic<FunctionGenerator<float,N>,11> m_generators;
			Framepair m_amplitude;
			float m_f;
			float m_gain;
			Adsr m_modulator;
			Filter m_filter;
			float m_f_0;
			float m_keytrack;
			int8_t m_key;
		};

	template<size_t N>
	void Voice<N>::generate(const ArrayStatic<float,N>& waveform
		,double detune,bool suboct
		,float* buffer_temp,Framepair* stereo_out,size_t n) noexcept
		{
		static_assert(m_generators.size()!=0,"No generators?");

		auto d_xi=1.0/(m_generators.size() - 1);
		auto df=std::exp2(detune*d_xi/12.0);
		auto f_0=std::exp2(-0.5*detune/12.0);
		auto f_base=m_f;
		auto a=m_gain;
		auto gain=2.0f/m_generators.size();
		f_base*=f_0;

		if(suboct)
			{
			for(size_t k=0;k<m_generators.size();++k)
				{
				m_generators[k].generate(k%2?0.5f*f_base:f_base,a,waveform,buffer_temp,n);
				f_base*=df;
				addToMix(buffer_temp,gain,k*d_xi,stereo_out,n);
				}
			}
		else
			{
			for(size_t k=0;k<m_generators.size();++k)
				{
				m_generators[k].generate(f_base,a,waveform,buffer_temp,n);
				f_base*=df;
				addToMix(buffer_temp,gain,k*d_xi,stereo_out,n);
				}
			}
		}

	template<size_t N>
	void Voice<N>::modulate(const Framepair* buffer_in,Adsr::Params adsr,Framepair* buffer_out,size_t n) noexcept
		{
		auto mod=m_modulator;
		auto amplitude=m_amplitude;
		while(n!=0)
			{
			*buffer_out=amplitude*(*buffer_in);

			++buffer_out;
			++buffer_in;

			auto a_1=mod.stateUpdate(adsr,amplitude.left<1>());
			auto a_2=mod.stateUpdate(adsr,a_1);
			amplitude=Framepair{a_1,a_1,a_2,a_2};
			n-=2;
			}
		m_amplitude=amplitude;
		m_modulator=mod;
		}

	template<size_t N>
	void Voice<N>::filterApply(const Framepair* buffer_in
		,Filter::Params filter_params,float* buffer_lfo,Framepair* buffer_out,size_t n) noexcept
		{
        auto filter=m_filter;
        auto f0=m_f_0;
		auto keytrack=m_keytrack;
		auto omega_0=filter_params.omega_0();
        while(n!=0)
        	{
            filter_params.omega_0()=omega_0 * f0 * keytrack * (*buffer_lfo);
            auto a=filter.stateUpdate(filter_params,{buffer_in->left<0>(),buffer_in->right<0>()});
			filter_params.omega_0()=omega_0 * f0 * keytrack * (*(buffer_lfo + 1));
            auto b=filter.stateUpdate(filter_params,{buffer_in->left<1>(),buffer_in->right<1>()});
            *buffer_out=Framepair{a.first,a.second,b.first,b.second};
            ++buffer_in;
            ++buffer_out;
			buffer_lfo+=2;
            n-=2;
            }
        m_filter=filter;
		}
	}

#endif