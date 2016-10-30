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
	target_dir=sys.argv[1];

	if (newer(target_dir+'/background.png','star.svg') 
		and newer(target_dir+'/background.png',sys.argv[0])
		and newer(target_dir+'/background.png','genpattern.m')):
		exit(0)
	subprocess.run(['inkscape','--export-png='+target_dir+'/background.png','star.svg']\
		,stdout=subprocess.DEVNULL)

	script="""data=imread('""" +target_dir+'/background.png'+"""');
mask=data(:,:,1);
pkg load image;
pattern=genpattern(mask,64,[1200 1920],225);
noise=rand(size(pattern)).*(pattern < 0.125);
noise=4*(noise - 5/8)/3;
imwrite(pattern + noise.*(noise>0),'""" +target_dir+'/background.png'+ """');
"""
	p=subprocess.Popen(['octave-cli'],stdin=subprocess.PIPE)
	p.communicate(script.encode('utf8'))

#	subprocess.run(['convert','-size','1020x1020','pattern:checkerboard' \
#		,target_dir + '/background.png']);
except Exception:
    write_error('%s: error: %s\n'%(sys.argv[0],sys.exc_info()[1]))
    sys.exit(-1)
