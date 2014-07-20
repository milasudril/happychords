#ifdef __WAND__
target[name[happychords.so] type [lib_dynamic] platform[;GNU/Linux]]
#endif

#include "dspengine.h"
#include <lv2plug/client.h>
#include <lv2plug/main.h>

const LV2_Descriptor& LV2Plug::main()
	{
	return LV2Plug::descriptorGet<Happychords::Plugin::DspEngine>();
	}
