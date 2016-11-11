#!/bin/bash

rm -r ~/.lv2/happychords2.ttl
mkdir -p ~/.lv2/happychords2.ttl
cp __targets_rel/*.so ~/.lv2/happychords2.ttl
cp __targets_rel/manifest.ttl ~/.lv2/happychords2.ttl
