all: __wand_targets_rel_lnx/plugin/happychords.so \
__wand_targets_rel_lnx/plugin/happychords-ui.so \
__wand_targets_rel_win/ui/happychords-ui.exe

__wand_targets_rel_lnx/plugin/happychords.so __wand_targets_rel_lnx/plugin/happychords-ui.so: plugin bridge
	wand profile[release]

__wand_targets_rel_win/ui/happychords-ui.exe: ui bridge
	wine wand profile[release]

__wand_targets_dbg_lnx/plugin/happychords.so __wand_targets_dbg_lnx/plugin/happychords-ui.so: plugin bridge
	wand

__wand_targets_dbg_win/ui/happychords-ui.exe: ui bridge
	wine wand

install: all
	mkdir -p ~/.lv2
	mkdir -p ~/.lv2/happychords.lv2
	cp __wand_targets_rel_lnx/plugin/happychords.so ~/.lv2/happychords.lv2
	cp __wand_targets_rel_lnx/plugin/happychords-ui.so ~/.lv2/happychords.lv2
	cp __wand_targets_rel_win/ui/happychords-ui.exe ~/.lv2/happychords.lv2
	cp manifest.ttl ~/.lv2/happychords.lv2/manifest.ttl

install_herbarium: all
	wand profile[install]
	wine profile[install]

clean:
	rm -rf __wand_targets*

