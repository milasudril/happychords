#!/bin/bash
cd backend
wand
wand profile[release]
cd ..
cd ui
wine wand
wine wand "profile[release]"
cd ..
mkdir ~/.lv2
mkdir ~/.lv2/happychords.lv2
cp backend/__wand_targets_rel/happychords.so ~/.lv2/happychords.lv2
cp backend/__wand_targets_rel/happychords-ui.so ~/.lv2/happychords.lv2
cp manifest.ttl ~/.lv2/happychords.lv2/manifest.ttl