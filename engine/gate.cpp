//@	{
//@	 "targets":[{"name":"gate.o","type":"object"}]
//@	,"dependencies_extra":[{"ref":"gate.o","rel":"implementation"}]
//@	}

#include "gate.hpp"
#include <algorithm>

using namespace Happychords;

void Gate::seek() noexcept
	{
	m_seq_current=std::lower_bound(m_seq_begin,m_seq_end,m_seq_pos
		,[](const GateSequence::Event& a,double b)
			{return a.time < b;}
		);
	}

static inline const GateSequence::Event* eventsProcess(const GateSequence::Event* begin
	,const GateSequence::Event* end,double seq_pos,Adsr& mod)
	{
	while(begin!=end)
		{
		auto e=*begin;
		if(e.time > seq_pos)
			{return begin;}
		switch(e.type)
			{
			case GateSequence::Event::Type::NOTE_OFF:
				mod.release();
				break;
			case GateSequence::Event::Type::NOTE_ON:
				mod.attack();
				break;
			default:
				break;
			}
		++begin;
		}
	return begin;
	}


void Gate::modulate(const Framepair* buffer_in,Adsr::Params adsr,Framepair* buffer_out,size_t n) noexcept
	{
	auto mod=m_modulator;
	auto amplitude=m_amplitude;
	auto seq_current=m_seq_current;
	auto seq_begin=m_seq_begin;
	auto seq_end=m_seq_end;
	auto seq_pos=m_seq_pos;
	auto time_scale=m_timescale;
	
	while(n!=0)
		{
		seq_current=eventsProcess(seq_current,seq_end,seq_pos,mod);
		seq_pos+=time_scale;
		if(seq_current==seq_end)
			{
			seq_current=seq_begin;
			seq_pos=0;
			}
		auto a_0=mod.stateUpdate(adsr,amplitude.left<1>());

		seq_current=eventsProcess(seq_current,seq_end,seq_pos,mod);
		seq_pos+=time_scale;
		if(seq_current==seq_end)
			{
			seq_current=seq_begin;
			seq_pos=0;
			}
		auto a_1=mod.stateUpdate(adsr,a_0);

		amplitude=Framepair{a_0,a_0,a_1,a_0};
		*buffer_out=amplitude*(*buffer_in);
		++buffer_out;
		++buffer_in;
		n-=2;
		}
	m_seq_pos=seq_pos;
	m_seq_current=seq_current;
	m_amplitude=amplitude;
	m_modulator=mod;
	}
