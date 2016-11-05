//@	{"targets":[{"name":"adsr.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_ADSR_HPP
#define HAPPYCHORDS_ADSR_HPP

#include "vectortype.hpp"
#include <cstdio>
#include <cmath>
#include <cstddef>

namespace Happychords
	{      
	class Adsr
		{
		public:
			class Params
				{
				public:
					explicit Params(double fs,float a,float d,float s,float r) noexcept
						{
						attackSet(fs,a).decaySet(fs,d).sustainSet(s).releaseSet(fs,r);
						}
		
					Params& attackSet(double fs,float a) noexcept
						{
						m_content.values.A=1.0f/(fs*a);
						return *this;
						}

					float attackGet() const noexcept
						{return m_content.values.A;}

					Params& decaySet(double fs,float d) noexcept
						{
						m_content.values.D=1.0f/(fs*d);
						return *this;
						}

					float decayGet() const noexcept
						{return m_content.values.D;}

					Params& sustainSet(float s) noexcept
						{
						m_content.values.S=s;
						return *this;
						}

					float sustainGet() const noexcept
						{return m_content.values.S;}

					Params& releaseSet(double fs,float r) noexcept
						{
						m_content.values.R=1.0f/(fs*r);
						return *this;
						}

					float releaseGet() const noexcept
						{return m_content.values.R;}

				private:
                  	union
                    	{
						struct
							{
							float A;
							float D;
							float S;
							float R;
							} values;
                        vec4<float> vec;
                        } m_content;
				};

			Adsr():state(release_handler){}
				
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
			
			typedef float (*State)(Adsr& self,const Params params,float value);
          
			static float attack_handler(Adsr& self,const Params params,float value)
             	{
                value+=(1.0f - value)*params.attackGet();
                if(std::abs(1.0f - value) < threshold)
                	{self.state=decay_handler;}
                return value;
              	}

			static float decay_handler(Adsr& self,const Params params,float value)
				{
				value+=(params.sustainGet()-value)*params.decayGet(); 
				if(std::abs(params.sustainGet() - value) < threshold)
					{self.state=sustain_handler;}
				return value;
				}

			static float sustain_handler(Adsr& self,const Params params,float value)
				{return params.sustainGet();}

			static float release_handler(Adsr& self,const Params params,float value)
				{
				value+=(-value)*params.releaseGet();
				return value;
				}
			State state;
		};
	}
#endif
