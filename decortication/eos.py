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
def listdir(d):
	raw_output = Popen(['eos root://cmseos.fnal.gov ls {}'.format(d)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
	return [thing for thing in raw_output[0].split("\n") if thing]
# /FUNCTIONS
