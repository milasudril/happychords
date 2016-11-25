#@  {
#@  "targets":
#@      [
#@           {"name":"switch-down-background.png","dependencies":[{"ref":"switch.blend","rel":"file"}]}
#@          ,{"name":"switch-down-light.png","dependencies":[{"ref":"switch.blend","rel":"file"}]}
#@          ,{"name":"switch-up-background.png","dependencies":[{"ref":"switch.blend","rel":"file"}]}
#@          ,{"name":"switch-up-light.png","dependencies":[{"ref":"switch.blend","rel":"file"}]}
#@      ]
#@  }

import subprocess
import sys
import os


def write_error(*args, **kwargs):
    print(*args,file=sys.stderr,**kwargs)
	
try:
	target_dir=sys.argv[1]
	in_dir=sys.argv[2]
	print('# Baking switch sprite')
	blender=subprocess.Popen(['blender','-b',in_dir+'/switch.blend' \
		,'-s','2','-e','5','-o',target_dir+'/'+in_dir+'/switch_#.png','-a'] \
		,stdout=subprocess.PIPE)
	for lines in blender.stdout:
		progress=lines.decode('utf8').rstrip().split('|')
		print('# Blender:%s'%(progress[-1]))
		sys.stdout.flush()

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
