//@	{"targets":[{"name":"gate.hpp","type":"include"}]}

#ifndef HAPPYCHORDS_GATE_HPP
#define HAPPYCHORDS_GATE_HPP

#include "gatesequence.hpp"
#include "adsr.hpp"
#include <cmath>
#include <random>

namespace Happychords
	{
	class PRIVATE Gate
		{
		public:
			Gate(GateSequence&&)=delete;
			explicit Gate(const GateSequence& seq):m_seq_current(m_seq.begin())
				,m_seq_begin(m_seq.begin()),m_seq_end(m_seq.end())
				,m_amplitude(0.0f,0.0f,0.0f,0.0f)
				{}

			void modulate(const Framepair* buffer_in,Adsr::Params adsr,Framepair* buffer_out
				,size_t n) noexcept;

		private:
			Adsr m_modulator;
			Framepair m_amplitude;
			const GateSequence::Event* m_seq_current;
			const GateSequence::Event* m_seq_begin;
			const GateSequence::Event* m_seq_end;
		};


	Gate::modulate(const Framepair* buffer_in,Adsr::Params adsr,Framepair* buffer_out,size_t n) noexcept
		{
		auto mod=m_modulator;
		auto amplitude=m_amplitude;
		auto seq_current=m_seq_current;
		auto seq_begin=m_seq_begin;
		auto seq_end=m_seq_end;
		
		while(n!=0)
			{
			auto a_0=mod.stateUpdate(adsr,amplitude.left<1>());
			auto a_1=mod.stateUpdate(adsr,a_0);
			amplitude=Framepair{a_0,a_0,a_1,a_0};

			*buffer_out=amplitude*(*buffer_in);

			++buffer_out;
			++buffer_in;

			n-=2;
			}
		m_seq_current=seq_current;
		m_amplitude=amplitude;
		m_modulator=mod;
		}
	}

#endif