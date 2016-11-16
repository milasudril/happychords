#@  {
#@  "targets":
#@      [
#@           {"name":"background.png","dependencies":[]}
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

	if (newer(target_dir+'/'+in_dir+'/background.png',in_dir+'/star.svg') 
		and newer(target_dir+'/'+in_dir+'/background.png',sys.argv[0])
		and newer(target_dir+'/'+in_dir+'/background.png',in_dir+'/genpattern.m')):
		exit(0)
	print('Baking background image');

	subprocess.run(['inkscape','--export-png='+target_dir+'/'+in_dir+'/background.png'
		,in_dir+'/star.svg']\
		,stdout=subprocess.DEVNULL)

	script="""addpath('"""+in_dir+"""');
filename='""" +target_dir+'/'+in_dir+'/background.png'+"""';
warning('off','Octave:GraphicsMagic-Quantum-Depth');
data=imread(filename);
mask=data(:,:,1);
pkg load image;
pattern=genpattern(mask,64,[1200 1920],225);
noise=rand(size(pattern)).*(pattern < 0.125);
noise=4*(noise - 5/8)/3;
imwrite(pattern + noise.*(noise>0),filename);
"""
	p=subprocess.Popen(['octave-cli'],stdin=subprocess.PIPE)
	p.communicate(script.encode('utf8'))
except Exception:
	write_error('%s:%d: error: %s\n'%(sys.argv[0],sys.exc_info()[2].tb_lineno,sys.exc_info()[1]))
	sys.exit(-1)
