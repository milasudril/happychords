#@  {
#@  "targets":
#@      [
#@          {
#@			 "name":"background.png"
#@			,"dependencies":
#@				[
#@					 {"ref":"star.svg","rel":"file"}
#@					,{"ref":"genpattern.m","rel":"file"}
#@				]
#@			}
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
	print('# Baking background image');

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
