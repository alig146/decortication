####################################################################
# Type: SCRIPT                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, sys, sqlite3
from time import time
import decortication
from decortication import dataset, variables
from truculence import crab
# /IMPORTS

# CLASSES:
# /CLASSES

# VARIABLES:
# /VARIABLES

# FUNCTIONS:

def main():
	# Arguments
	a = variables.arguments()
	if not a.kinds:
		a.kinds = variables.all_kinds
	
	# Fetch datasets:
	results = {}
	for kind in a.kinds:
		entries = dataset.fetch_entries(kind, a.query)
		for entry in entries:
			if entry.subprocess not in results:
				results[entry.subprocess] = {}
			if entry.kind not in results[entry.subprocess]:
				results[entry.subprocess][entry.kind] = []
			results[entry.subprocess][entry.kind].append(entry)
	
	# Print stuff:
	for subprocess, kinds in results.items():
		for kind, entries in kinds.items():
			for entry in entries:
				entry.Print()
		print "=========================================================="
	return True
# /FUNCTIONS

# MAIN:
if __name__ == "__main__":
	main()
# /MAIN

