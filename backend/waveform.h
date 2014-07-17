#ifdef __WAND__
target[name[waveform.h] type[include]]
#endif

#ifndef HAPPYCHORDS_WAVEFORM_H
#define HAPPYCHORDS_WAVEFORM_H

namespace Happychords
	{
	struct Waveform
		{
		const float* data;
		size_t n_frames;
		};
	}

#endif
