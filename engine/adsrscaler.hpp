//@	{"targets":[{"name":"adsrscaler.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_ADSRSCALER_HPP
#define HAPPYCHORDS_ADSRSCALER_HPP

#include "vectortype.hpp"

#include <cmath>
#include <cstddef>

namespace Happychords
	{      
	class AdsrScaler
		{
		public:
			class Params
				{
				public:
					explicit Params(double fs,float base,float a,float d,float s,float r) noexcept
						{
						baseSet(base).attackSet(fs,base,a).decaySet(fs,base,d).sustainSet(base,s)	
							.releaseSet(fs,base,r);
						}
		
					Params& attackSet(double fs,float base,float a) noexcept
						{
						m_content.values.A=std::pow(m_content.values.base,1.0f/(fs*a));
						return *this;
						}

					float attackGet() const noexcept
						{return m_content.values.A;}

					Params& baseSet(float base) noexcept
						{
						m_content.values.base=base;
						return *this;
						}

					Params& decaySet(double fs,float base,float d) noexcept
						{
						m_content.values.D=std::pow(m_content.values.base,-1.0f/(fs*d));
						return *this;
						}

					float decayGet() const noexcept
						{return m_content.values.D;}

					Params& sustainSet(float base,float s) noexcept
						{
						m_content.values.S=std::pow(m_content.values.base,s);
						return *this;
						}

					float sustainGet() const noexcept
						{return m_content.values.S;}

					Params& releaseSet(double fs,float base,float r) noexcept
						{
						m_content.values.R=std::pow(m_content.values.base,-1.0f/(fs*r));
						return *this;
						}

					float releaseGet() const noexcept
						{return m_content.values.R;}
                  
                  	float baseGet() const noexcept
                    	{return m_content.values.base;}

				private:
                  	union
                    	{
						struct
							{
							float A;
							float D;
							float S;
							float R;
							float base;
							} values;
                        vec8<float> vec;
                        } m_content;
				};

			AdsrScaler():state(done_handler){}
				
			void attack() noexcept
				{state=attack_handler;}

			void release() noexcept
				{state=release_handler;}
			
			float stateUpdate(const Params& params,float value) noexcept
				{return state(*this,params,value);}

			bool started() const noexcept
				{return state==attack_handler;}
		
		private:
			static constexpr const float threshold=1.0e-2f;
			
			typedef float (*State)(AdsrScaler& self,const Params params,float value);
          
			static float attack_handler(AdsrScaler& self,const Params params,float value)
             	{
                value*=params.attackGet();
                if(value > params.baseGet())
                	{self.state=decay_handler;}
                return value;
              	}

			static float decay_handler(AdsrScaler& self,const Params params,float value)
				{
				value*=params.decayGet(); 
				if(value < params.sustainGet())
					{
					self.state=sustain_handler;
					return params.sustainGet();
					}
				return value;
				}

			static float sustain_handler(AdsrScaler& self,const Params params,float value)
				{return params.sustainGet();}

			static float release_handler(AdsrScaler& self,const Params params,float value)
				{
				value*=params.releaseGet();
				if(value < 1.0f)
					{
					self.state=done_handler;
					return 1.0f;
					}
				return value;
				}

			static float done_handler(AdsrScaler& self,const Params params,float value)
				{return value;}
				

			State state;
		};
	}
#endif
