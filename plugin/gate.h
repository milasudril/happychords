#ifdef __WAND__
target[name[gate.h] type[include]]
#endif

#ifndef HAPPYCHRODS_PLUGIN_GATE_H
#define HAPPYCHRODS_PLUGIN_GATE_H

#include <synthmod/filter_adsr.h>

namespace Happychords
	{
	namespace Plugin
		{
		class Gate
			{
			public:
				void open()
					{
					G=0.0f;
					envelope.attack();
					}
					
				void close()
					{envelope.release();}
				
				void attackSet(float time,float f_s)
					{envelope.A=time*f_s;}
				
				void decaySet(float time,float f_s)
					{envelope.D=time*f_s;}
				
				void sustainSet(float value)
					{envelope.S=value;}
				
				void releaseSet(float time,float f_s)
					{envelope.R=time*f_s;}
				
				float operator()()
					{
					auto ret=G;
					G=envelope(G);
					return ret;
					}
				
			private:
				Synthmod::FilterAdsr envelope;
				float G;
			};
		}
	}

#endif
