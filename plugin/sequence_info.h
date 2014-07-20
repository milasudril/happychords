#ifdef __WAND__
target[name[sequence_info.h] type[include]]
#endif

#ifndef HAPPYCHORDS_PLUGIN_SEQUENCEINFO_H
#define HAPPYCHORDS_PLUGIN_SEQUENCEINFO_H

#include <cstddef>

namespace MuStudio
	{
	namespace MIDI
		{
		struct Event;
		};
	}

namespace Happychords
	{
	namespace Plugin
		{
		struct SequenceInfo
			{
			const MuStudio::MIDI::Event* begin;
			const MuStudio::MIDI::Event* end;
			size_t time_division;
			size_t length;
			};
		}
	};

#endif
