#!/bin/bash

rm -r ~/.lv2/happychords2.ttl
mkdir -p ~/.lv2/happychords2.ttl
cp __targets/*.so ~/.lv2/happychords2.ttl
cp __targets/manifest.ttl ~/.lv2/happychords2.ttl
