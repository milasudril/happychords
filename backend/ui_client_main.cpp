#ifdef __WAND__
target[name[happychords-ui.so] type [lib_dynamic] platform[;GNU/Linux]]
#endif

#include "ui_client.h"
#include <lv2plug/ui.h>
#include <lv2plug/ui_main.h>

const LV2UI_Descriptor& LV2Plug::ui_main()
	{
	return LV2Plug::descriptorGet<Happychords::UiClient>();
	}
