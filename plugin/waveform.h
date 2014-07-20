#ifdef __WAND__
target[name[waveform.h] type[include]]
#endif

#ifndef HAPPYCHORDS_PLUGIN_WAVEFORM_H
#define HAPPYCHORDS_PLUGIN_WAVEFORM_H

namespace Happychords
	{
	namespace Plugin
		{
		struct Waveform
			{
			const float* data;
			size_t n_frames;
			};
		}
	}

#endif
