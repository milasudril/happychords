#@  {
#@  "targets":
#@      [
#@           {"name":"knob-mask.png","dependencies":[]}
#@          ,{"name":"knob-shadow.png","dependencies":[]}
#@          ,{"name":"knob-specular.png","dependencies":[]}
#@      ]
#@  }

import subprocess
import sys
import os

def write_error(*args, **kwargs):
    print(*args,file=sys.stderr,**kwargs)

def newer(file_a,file_b):
	if not os.path.exists(file_a):
		return 0
	if not os.path.exists(file_b):
		return 1
	stata=os.stat(file_a)
	statb=os.stat(file_b)
	if stata.st_mtime > statb.st_mtime:
		return 1
	return 0

try:
	target_dir=sys.argv[1];

	if ( newer(target_dir+'/knob-mask.png','knob.blend')
		and newer(target_dir+'/knob-shadow.png','knob.blend')
		and newer(target_dir+'/knob-specular.png','knob.blend') ):
		exit(0)

	subprocess.run(['blender','-b','knob.blend' \
		,'-s','1','-e','3','-o','//'+target_dir+'/knob_#.png','-a'] \
		,stdout=subprocess.DEVNULL);

	subprocess.run(['convert','-white-threshold','64',target_dir+'/knob_1.png'\
		,target_dir+'/knob-mask.png']);
	os.remove(target_dir+'/knob_1.png')
	os.rename(target_dir+'/knob_2.png',target_dir+'/knob-shadow.png')
	os.rename(target_dir+'/knob_3.png',target_dir+'/knob-specular.png')
except Exception:
    write_error('%s: error: %s\n'%(sys.argv[0],sys.exc_info()[1]))
    sys.exit(-1)
