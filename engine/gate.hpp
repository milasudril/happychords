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

			void positionSet(double beat) noexcept
				{
				if(m_seq_begin==m_seq_end)
					{return;}
				auto seq_length=(m_seq_end - 1)->time;
				m_seq_pos=std::fmod(beat*m_tpqn,seq_length);
				seek();
				printf("Gate position: %.15g (at event %zd with position %zu)\n",
					m_seq_pos,m_seq_current - m_seq_begin,m_seq_current->time);
				fflush(stdout);
				}

			void timescaleSet(float tempo,double fs) noexcept
				{
				m_timescale=(tempo*m_tpqn)/(60.0*fs);
				printf("Timescale: %.15g\n",m_timescale);
				fflush(stdout);
				}

		private:
			void seek() noexcept;
			Adsr m_modulator;
			Framepair m_amplitude;
			double m_seq_pos;
			const GateSequence::Event* m_seq_current;
			const GateSequence::Event* m_seq_begin;
			const GateSequence::Event* m_seq_end;
			double m_timescale;
			size_t m_tpqn;
		};
	}

#endif