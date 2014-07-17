#ifdef __WAND__
target[name[gatecontrolloop.h] type [include]]
dependency[gatecontrolloop.o]
#endif

#ifndef HAPPYCHORDS_GATECONTROLLOOP_H
#define HAPPYCHORDS_GATECONTROLLOOP_H

#include "sequence_info.h"

namespace Happychords
	{
	class Gate;
	class GateControlLoop
		{
		public:
			GateControlLoop(Gate& gate);
			
			void operator()();
			
			void sequenceSet(const SequenceInfo& seq_info)
				{
				seq=seq_info;
				positionReset();
				}
			
			void positionReset()
				{
				seq_pos=seq.begin;
				sample_pos=0;
				}
				
			void tempoSet(double bpm,double f_s)
				{
				m_fs=f_s;
				m_bpm=bpm;
				}
			
			void positionSet(size_t frame)
				{
				double time_scale=m_fs*60/(m_bpm*seq.time_division);
				size_t length_frames=size_t(seq.length*time_scale + 0.5);
				sample_pos=frame%length_frames;
				seek();
				}

		private:
			Gate& m_gate;
			SequenceInfo seq;
			const MuStudio::MIDI::Event* seq_pos;
			double m_fs;
			double m_bpm;
			size_t sample_pos;
			
			void seek();
			
		};
	}

#endif
