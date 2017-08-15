//@	{"targets":[{"name":"voice.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_VOICE_HPP
#define HAPPYCHORDS_VOICE_HPP

#include "functiongenerator.hpp"
#include "stereomixer.hpp"
#include "adsr.hpp"
#include "filter.hpp"
#include "adsrscaler.hpp"
#include <cmath>
#include <random>

namespace Happychords
	{
	template<size_t N>
	class PRIVATE Voice
		{
		public:
			Voice():m_amplitude(0.0f),m_f(0),m_gain(0),m_f_0(0)
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
				
			void generate(const ArrayStatic<float,N>& waveform
				,double detune,bool suboct
				,float& buffer_temp,std::pair<float,float>& stereo_out) noexcept;

			void filterApply(const Framepair* buffer_in
				,Filter::Params filter
				,AdsrScaler::Params filter_mod_params
				,const float* buffer_lfo,Framepair* buffer_out,size_t n) noexcept;
				
			void filterApply(const std::pair<float,float>& buffer_in
				,Filter::Params filter
				,AdsrScaler::Params filter_mod_params
				,float buffer_lfo,std::pair<float,float>& buffer_out) noexcept;

			void modulate(const Framepair* buffer_in
				,Adsr::Params adsr,Framepair* buffer_out,size_t n) noexcept;
				
			void modulate(const std::pair<float,float>& buffer_in
				,Adsr::Params adsr,std::pair<float,float>& buffer_out) noexcept;

			float amplitude() const noexcept
				{return m_amplitude;}

			void start(float f,float a,float keytrack,int8_t key) noexcept
				{
				m_f=f;
				m_gain=a;
				m_modulator.attack();
				m_filter.stateReset();
				m_amplitude=0.0f;
				m_key=key;
				m_keytrack=std::exp2((key-69)*keytrack/12.0f);
				m_f_0=1.0f;
				m_filter_mod.attack();
				}

			void stop(int8_t key) noexcept
				{
				if(key==m_key)
					{
					m_modulator.release();
					m_filter_mod.release();
					}
				}

			bool started() const noexcept
				{return m_modulator.started();}

		private:
			ArrayStatic<FunctionGenerator<float,N>,11> m_generators;
			float m_amplitude;
			float m_f;
			float m_gain;
			Adsr m_modulator;
			

			Filter m_filter;
			AdsrScaler m_filter_mod;
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
	void Voice<N>::generate(const ArrayStatic<float,N>& waveform
		,double detune,bool suboct
		,float& buffer_temp,std::pair<float,float>& stereo_out) noexcept
		{
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
				m_generators[k].generate(k%2?0.5f*f_base:f_base,a,waveform,buffer_temp);
				f_base*=df;
				addToMix(buffer_temp,gain,k*d_xi,stereo_out);
				}
			}
		else
			{
			for(size_t k=0;k<m_generators.size();++k)
				{
				m_generators[k].generate(f_base,a,waveform,buffer_temp);
				f_base*=df;
				addToMix(buffer_temp,gain,k*d_xi,stereo_out);
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
			auto a_0=mod.stateUpdate(adsr,amplitude);
			auto a_1=mod.stateUpdate(adsr,a_0);
			amplitude=a_1;
			auto a_vec=Framepair{a_0,a_0,a_1,a_1};

			*buffer_out=a_vec*(*buffer_in);

			++buffer_out;
			++buffer_in;

			n-=2;
			}
		m_amplitude=amplitude;
		m_modulator=mod;
		}
		
	template<size_t N>
	void Voice<N>::modulate(const std::pair<float,float>& buffer_in
		,Adsr::Params adsr,std::pair<float,float>& buffer_out) noexcept
		{
		auto mod=m_modulator;
		auto amplitude=m_amplitude;
		auto a_0=mod.stateUpdate(adsr,amplitude);
		buffer_out.first=a_0*buffer_in.first;
		buffer_out.second=a_0*buffer_in.second;
		m_amplitude=a_0;
		m_modulator=mod;		
		}

	template<size_t N>
	void Voice<N>::filterApply(const Framepair* buffer_in
		,Filter::Params filter_params
		,AdsrScaler::Params filter_mod_params
		,const float* buffer_lfo,Framepair* buffer_out,size_t n) noexcept
		{
        auto filter=m_filter;
        auto filter_mod=m_filter_mod;
		auto keytrack=m_keytrack;
		auto omega_0=filter_params.omega_0();
		auto f_0=m_f_0;
        while(n!=0)
        	{
			f_0=filter_mod.stateUpdate(filter_mod_params,f_0);
            filter_params.omega_0()=omega_0 * f_0 * keytrack * (*buffer_lfo);
            auto a=filter.stateUpdate(filter_params,{buffer_in->left<0>(),buffer_in->right<0>()});
		
			f_0=filter_mod.stateUpdate(filter_mod_params,f_0);
			filter_params.omega_0()=omega_0 * f_0 * keytrack * (*(buffer_lfo + 1));
            auto b=filter.stateUpdate(filter_params,{buffer_in->left<1>(),buffer_in->right<1>()});
		
            *buffer_out=Framepair{a.first,a.second,b.first,b.second};
            ++buffer_in;
            ++buffer_out;
			buffer_lfo+=2;
            n-=2;
            }
		m_f_0=f_0;
		m_filter_mod=filter_mod;
        m_filter=filter;
		}
	
	template<size_t N>
	void Voice<N>::filterApply(const std::pair<float,float>& buffer_in
		,Filter::Params filter_params,AdsrScaler::Params filter_mod_params
		,float lfo,std::pair<float,float>& buffer_out) noexcept
		{
        auto filter=m_filter;
        auto filter_mod=m_filter_mod;
		auto keytrack=m_keytrack;
		auto omega_0=filter_params.omega_0();
		
		auto f_0=filter_mod.stateUpdate(filter_mod_params,m_f_0);
        filter_params.omega_0()=omega_0 * f_0 * keytrack * lfo;
        auto a=filter.stateUpdate(filter_params,buffer_in);
		buffer_out=a;

		m_f_0=f_0;
		m_filter_mod=filter_mod;
        m_filter=filter;		
		}
	}

#endif