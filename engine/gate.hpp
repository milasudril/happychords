//@	{
//@	 "targets":[{"name":"gate.hpp","type":"include"}]
//@	,"dependencies_extra":[{"ref":"gate.o","rel":"implementation"}]
//@	}

#ifndef HAPPYCHORDS_GATE_HPP
#define HAPPYCHORDS_GATE_HPP

#include "gatesequence.hpp"
#include "adsr.hpp"
#include "framepair.hpp"
#include <cmath>
#include <random>

namespace Happychords
	{
	class PRIVATE Gate
		{
		public:
			Gate(GateSequence&&)=delete;
			explicit Gate(const GateSequence& seq,float tempo,double fs):
				 m_amplitude(0.0f,0.0f,0.0f,0.0f)
				,m_seq_pos(0)
				,m_seq_current(seq.begin())
				,m_seq_begin(seq.begin()),m_seq_end(seq.end())
				,m_tpqn(seq.tpqnGet())
				{
				timescaleSet(tempo,fs);
				}

			void modulate(const Framepair* buffer_in,Adsr::Params adsr,Framepair* buffer_out
				,size_t n) noexcept;

			void positionSet(int64_t frame) noexcept
				{
				if(m_seq_begin==m_seq_end)
					{return;}
				auto seq_length=static_cast<size_t>(m_timescale * (m_seq_end - 1)->time + 0.5);
				m_seq_pos=frame%seq_length;
				seek();
				}

			void timescaleSet(float tempo,double fs) noexcept
				{m_timescale=fs*60.0/(tempo*m_tpqn);}

		private:
			void seek() noexcept;
			Adsr m_modulator;
			Framepair m_amplitude;
			size_t m_seq_pos;
			const GateSequence::Event* m_seq_current;
			const GateSequence::Event* m_seq_begin;
			const GateSequence::Event* m_seq_end;
			double m_timescale;
			size_t m_tpqn;
		};
	}

#endif