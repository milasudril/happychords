//@	{"targets":[{"name":"stereomixer.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_STEREOMIXER_HPP
#define HAPPYCHORDS_STEREOMIXER_HPP

#include "framepair.hpp"

namespace Happychords
	{
	static void addToMix(const float* buffer_in,float gain,float xi
		,Framepair* buffer_out,size_t n)
		{
		auto xi_vec=gain*Framepair{xi,1.0f - xi,xi,1.0f - xi};
		while(n!=0)
			{
			auto v1=*buffer_in;
			auto v2=*(buffer_in+1);
			(*buffer_out)+=xi_vec*Framepair{v1,v2,v1,v2};
			++buffer_out;
			buffer_in+=2;
			n-=2;
			}
		}

	static void addToMix(const Framepair* buffer_in,Framepair* buffer_out,size_t n)
		{
		while(n!=0)
			{
			(*buffer_out)+=*buffer_in;
			++buffer_in;
			++buffer_out;
			n-=2;
			}
		}

	static void mix(const Framepair* buffer_a,const Framepair* buffer_b
		,float xi
		,Framepair* buffer_out,size_t n)
		{
		auto xi_comp=1.0f - xi;
		while(n!=0)
			{
			auto v1=*buffer_a;
			auto v2=*buffer_b;
			*buffer_out=xi_comp*v1 + xi*v2;
			++buffer_a;
			++buffer_b;
			++buffer_out;
			n-=2;
			}
		}

	static void demux(const Framepair* buffer_in,float* buffer_l,float* buffer_r,size_t n)
		{
		while(n!=0)
			{
			buffer_l[0]=buffer_in->left<0>();
			buffer_r[0]=buffer_in->right<0>();
			buffer_l[1]=buffer_in->left<1>();
			buffer_r[1]=buffer_in->right<1>();
			buffer_l+=2;
			buffer_r+=2;
			++buffer_in;
			n-=2;
			}
		}
	}

#endif
