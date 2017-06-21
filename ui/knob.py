#@  {
#@  "targets":
#@      [
#@           {"name":"knob-mask.png","dependencies":[{"ref":"knob.blend","rel":"misc"}]}
#@          ,{"name":"knob-shadow.png","dependencies":[{"ref":"knob.blend","rel":"misc"}]}
#@          ,{"name":"knob-specular.png","dependencies":[{"ref":"knob.blend","rel":"misc"}]}
#@      ]
#@  }

import subprocess
import sys
import os

def write_error(*args, **kwargs):
    print(*args,file=sys.stderr,**kwargs)

try:
	target_dir=sys.argv[1];
	in_dir=sys.argv[2];

	print('# Baking knob sprites')

	blender=subprocess.Popen(['blender','-b',in_dir+'/knob.blend' \
		,'-s','1','-e','3','-o',target_dir+'/'+in_dir+'/knob_#.png','-a']\
		,stdout=subprocess.PIPE);
	for lines in blender.stdout:
		progress=lines.decode('utf8').rstrip().split('|')
		print('# Blender:%s'%(progress[-1]))
		sys.stdout.flush()

	subprocess.run(['convert','-white-threshold','64',target_dir+'/'+in_dir+'/knob_1.png'\
		,target_dir+'/'+in_dir+'/knob-mask.png']);
	os.remove(target_dir+'/'+in_dir+'/knob_1.png')
	os.rename(target_dir+'/'+in_dir+'/knob_2.png',target_dir+'/'+in_dir+'/knob-shadow.png')
	os.rename(target_dir+'/'+in_dir+'/knob_3.png',target_dir+'/'+in_dir+'/knob-specular.png')
except Exception:
	write_error('%s:%d: error: %s\n'%(sys.argv[0],sys.exc_info()[2].tb_lineno,sys.exc_info()[1]))
	sys.exit(-1)
