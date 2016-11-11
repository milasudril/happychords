//@	{"targets":[{"name":"filter.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_FILTER_HPP
#define HAPPYCHORDS_FILTER_HPP

#include "mat4.hpp"
#include <utility>

namespace Happychords
	{
	class PRIVATE Filter
		{
		public:
			struct PRIVATE Params
				{
                public:
                    constexpr double& dt() noexcept
                    	{return m_data.content.dt;}

                  	constexpr double dt() const noexcept
                    	{return m_data.content.dt;}

                  	constexpr float& omega_0() noexcept
                    	{return m_data.content.omega_0;}

                  	constexpr float omega_0() const noexcept
                    	{return m_data.content.omega_0;}

                  	constexpr float& Q() noexcept
                    	{return m_data.content.Q;}

                  	constexpr float Q() const noexcept
                    	{return m_data.content.Q;}
                  
                private:
                    union
                        {
                        struct
                            {
                            double dt;
                            float omega_0;
                            float Q;
                            } content;
                        vec4<float> vec;
                        } m_data;
				};

			constexpr Filter() noexcept:m_out_old{0.0,0.0,0.0,0.0}
          		,m_in_old{0.0,0.0,0.0,0.0}
				{}

			std::pair<float,float> stateUpdate(Params params,const std::pair<float,float>& value_in) noexcept
            	{
                mat4<double> I=mat4<double>::identity();
                auto omega_0=params.omega_0();
                auto omega_0_2=omega_0*omega_0;
                auto Q_inv=1.0f/params.Q();
                auto dt_half=0.5*params.dt();
                vec4<double> f{0.0,omega_0_2*value_in.first,0.0,omega_0_2*value_in.second};
                mat4<double> A;
                A.column(0)=vec4<double>{0.0,-omega_0_2,0.0,0.0};
                A.column(1)=vec4<double>{1.0,-omega_0*Q_inv,0.0,0.0};
                A.column(2)=vec4<double>{0.0,0.0,0.0,-omega_0_2};
                A.column(3)=vec4<double>{0.0,0.0,1.0,-omega_0*Q_inv};
				auto r=m_out_old;
				r=block_div_twice( r + dt_half*(f + m_in_old + A*r),I-dt_half*A );
				m_in_old=f;
                m_out_old=r;
                return {r[0],r[2]};
            	}

		private:
			vec4<double> m_out_old;
          	vec4<double> m_in_old;
		};
	}

#endif
