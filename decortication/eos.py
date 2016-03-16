####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
from subprocess import Popen, PIPE
# /IMPORTS

# VARIABLES:
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

def listdir(d):
	raw_output = Popen(['eos root://cmseos.fnal.gov ls {}'.format(d)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	return [thing for thing in raw_output[0].split("\n") if thing]

def mkdir(d):
	raw_output = Popen(['eos root://cmseos.fnal.gov mkdir -p {}'.format(d)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	return True
# /FUNCTIONS
