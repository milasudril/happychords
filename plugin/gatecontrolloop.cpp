#ifdef __WAND__
target[name[gatecontrolloop.o] type[object]]
#endif

#include "gatecontrolloop.h"
#include "gate.h"
#include <midiseq/sequence.h>
#include <midiseq/event.h>

Happychords::Plugin::GateControlLoop::GateControlLoop(Gate& gate):
	m_gate(gate)
	,seq{nullptr,nullptr,0,0}
	{
	positionReset();
	}

void Happychords::Plugin::GateControlLoop::operator()()
	{
	double time_scale=m_fs*60/(m_bpm*seq.time_division);
	while(sample_pos>=time_scale*seq_pos->time && seq_pos!=seq.end)
		{
		if(seq_pos->type==(uint64_t)(-1))
			{
			switch(seq_pos->data.bytes[0]&0xf0)
				{
				case 0x80:
					m_gate.close();
					break;
				case 0x90:
					m_gate.open();
					break;
				}
			}
		++seq_pos;
		}

	++sample_pos;
	if(seq_pos==seq.end)
		{
		positionReset();
		}
	}

void Happychords::Plugin::GateControlLoop::seek()
	{
	double time_scale=m_fs*60/(m_bpm*seq.time_division);

//	Look for event at or after current sample_pos
	auto pos_min=seq.begin;
	while(pos_min!=seq.end)
		{
		if(pos_min->time*time_scale >= sample_pos)
			{
			seq_pos=pos_min;
			break;
			}
		++pos_min;
		}
	}
