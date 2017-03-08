####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
from subprocess import Popen, PIPE
# /IMPORTS

# VARIABLES:
access_domains = {
	"cmslpc": ("cmseos.fnal.gov", "cmsxrootd.fnal.gov"),
}
# /VARIABLES

# CLASSES:
# /CLASSES

# FUNCTIONS:
def cp(original, copy, to=True):
	if to:
		raw_output = Popen(['xrdcp {} root://cmseos.fnal.gov/{}'.format(original, copy)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	else:
		raw_output = Popen(['xrdcp root://cmseos.fnal.gov/{} {}'.format(original, copy)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	return True

def listdir(d, root=False, interactive=False, location="cmslpc"):
	cmd = 'eos root://cmseos.fnal.gov ls {}'.format(d)
	raw_output = Popen([cmd], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	files = [thing for thing in raw_output[0].split("\n") if thing]
	if not root: return files
	else: return ["root://{}/{}/{}".format(access_domains[location][interactive], d, f) for f in files]

def mkdir(d):
	raw_output = Popen(['eos root://cmseos.fnal.gov mkdir -p {}'.format(d)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	return True

def getsize(f):
	raw_output = Popen(['eos root://cmseos.fnal.gov ls -l {}'.format(f)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	if raw_output[0]:
		return float(raw_output[0].split()[4])
	else:
		if raw_output[1]:
			print raw_output[1]
		return False

def rm(f):
	raw_output = Popen(['eos root://cmseos.fnal.gov rm {}'.format(f)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
#	print raw_output
	return True

def rmr(d):
	raw_output = Popen(['eos root://cmseos.fnal.gov rm -r {}'.format(d)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
#	print raw_output
	return True
# /FUNCTIONS
