#@  {
#@  "targets":
#@      [
#@           {"name":"switch-down-background.png","dependencies":[]}
#@          ,{"name":"switch-down-light.png","dependencies":[]}
#@          ,{"name":"switch-up-background.png","dependencies":[]}
#@          ,{"name":"switch-up-light.png","dependencies":[]}
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
	target_dir=sys.argv[1]
	in_dir=sys.argv[2]

	if ( newer(target_dir+'/'+in_dir+'/switch-down-background.png',in_dir+'/switch.blend')
		and newer(target_dir+'/'+in_dir+'/switch-down-light.png',in_dir+'/switch.blend')
		and newer(target_dir+'/'+in_dir+'/switch-up-background.png',in_dir+'/switch.blend') 
		and newer(target_dir+'/'+in_dir+'/switch-up-light.png',in_dir+'/switch.blend')):
		exit(0)
	print('Baking switch sprites')

	subprocess.run(['blender','-b',in_dir+'/switch.blend' \
		,'-s','2','-e','5','-o',target_dir+'/'+in_dir+'/switch_#.png','-a'] \
		,stdout=subprocess.DEVNULL)

	subprocess.run(['composite','-compose','subtract',target_dir+'/'+in_dir+'/switch_2.png' \
		,target_dir+'/'+in_dir+'/switch_3.png',target_dir+'/'+in_dir+'/switch-down-background.png'])
	subprocess.run(['convert',target_dir+'/'+in_dir+'/switch-down-background.png'
		,'-channel','R','-separate',target_dir+'/'+in_dir+'/switch-down-background.png'])
	os.rename(target_dir+'/'+in_dir+'/switch_3.png',target_dir+'/'+in_dir+'/switch-down-light.png')

	subprocess.run(['composite','-compose','subtract',target_dir+'/'+in_dir+'/switch_4.png' \
		,target_dir+'/'+in_dir+'/switch_5.png',target_dir+'/'+in_dir+'/switch-up-background.png'])
	subprocess.run(['convert',target_dir+'/'+in_dir+'/switch-up-background.png'
		,'-channel','R','-separate',target_dir+'/'+in_dir+'/switch-up-background.png'])
	os.rename(target_dir+'/'+in_dir+'/switch_5.png',target_dir+'/'+in_dir+'/switch-up-light.png')
	os.remove(target_dir+'/'+in_dir+'/switch_2.png')
	os.remove(target_dir+'/'+in_dir+'/switch_4.png')

except Exception:
	write_error('%s:%d: error: %s\n'%(sys.argv[0],sys.exc_info()[2].tb_lineno,sys.exc_info()[1]))
	sys.exit(-1)
