#ifdef __WAND__
target[name[gatecontrolloop.h] type [include]]
dependency[gatecontrolloop.o]
#endif

#ifndef HAPPYCHORDS_PLUGIN_GATECONTROLLOOP_H
#define HAPPYCHORDS_PLUGIN_GATECONTROLLOOP_H

#include "sequence_info.h"

#include <midiseq/event.h>
#include <cstdio>

namespace Happychords
	{
	namespace Plugin
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

					printf("dt=%lu l=%lu\n",seq.time_division,seq.length);

					auto pos_min=seq.begin;
					while(pos_min!=seq.end)
						{
						printf("%llu, %llx, %x\n",pos_min->time,pos_min->type,pos_min->data.bytes[0]&0xf0);
						++pos_min;
						}


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
				const MIDISeq::Event* seq_pos;
				double m_fs;
				double m_bpm;
				size_t sample_pos;

				void seek();

			};
		}
	}

#endif
