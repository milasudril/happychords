#!/bin/bash

rm -r ~/.lv2/happychords.ttl
mkdir -p ~/.lv2/happychords.ttl
cp __targets_rel/*.so ~/.lv2/happychords.ttl
cp __targets_rel/manifest.ttl ~/.lv2/happychords.ttl
