####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, yaml, re, sys
from subprocess import Popen, PIPE
from truculence import analysis
import decortication
from decortication import eos
# /IMPORTS

# VARIABLES
username = "tote"
data_dir = "/store/user/" + username
tuple_dir = data_dir + "/data/fat"
signal_processes = ["sqtojjjj", "sqtojj"]
# /VARIABLES

# CLASSES:
class dataset:
	# Construction:
	def __init__(self, info=None, set_info=False):
		# Basic attributes:
		for key, value in info.iteritems():
			setattr(self, key, value)
		if "name" not in info:
			self.name = False
		
		# Simple calculated assignments:
		self.miniaod_full = "/{}/{}".format(self.name, self.miniaod)
		self.jets_full = "/{}/{}".format(self.name, self.jets)
		self.tuple_file = "{}_tuple.root".format(self.name)
		self.tuple_path = tuple_dir + "/" + self.tuple_file
		
		# Local info:
		if set_info:
			self.set_info()
	# /Construction
	
	# Properties:
	def __nonzero__(self):
		return self.name != False
	
	def __str__(self):
		return "<dataset object: name = {0}>".format(self.name)
	# /Properties
	
	# Methods:
	def Print(self):
		print self
	
	def get_files(self):
		ds_dir = data_dir + "/" + self.name
	#	print ds_path
		results = {}
		
		# Look in the dataset directory and find the MiniAOD and jets (flavors) directories:
		dirs_flavor = eos.listdir(ds_dir)
		## General:
		results["dir"] = ds_dir
		
		## MiniAOD:
		dirs_miniaod = [d for d in dirs_flavor if "_fatjets" not in d]
		results["miniaod"] = {}
		if dirs_miniaod:
			if len(dirs_miniaod) > 1:
				print "ERROR (dataset.get_info): There is more than one jets directory: {0}".format(dirs_fatjet)
				return False
			elif len(dirs_miniaod) == 1:
				dir_miniaod = ds_dir + "/" + dirs_miniaod[0]
				results["miniaod"]["dir"] = dir_miniaod
				dates = eos.listdir(dir_miniaod)
				path_miniaod = dir_miniaod + "/" + dates[-1] + "/0000"
				results["miniaod"]["files"] = [path_miniaod + "/" + f for f in eos.listdir(path_miniaod) if ".root" in f]
		else:
			results["miniaod"]["dir"] = None
			results["miniaod"]["files"] = None
		
		## Jets:
		dirs_fatjet = [d for d in dirs_flavor if "_fatjets" in d]
		if len(dirs_fatjet) > 1:
			print "ERROR (decortication.dataset.get_files): There is more than one fatjet directory: {0}".format(dirs_fatjet)
			return False
		elif len(dirs_fatjet) == 1:
			results["jets"] = {}
			dir_fatjet = ds_dir + "/" + dirs_fatjet[0]
			results["jets"]["dir"] = dir_fatjet
			dates = eos.listdir(dir_fatjet)
			path_fatjet = dir_fatjet + "/" + dates[-1] + "/0000"
			results["jets"]["files"] = [path_fatjet + "/" + f for f in eos.listdir(path_fatjet) if ".root" in f]
		
		# Return stuff:
		return results
	
	def set_info(self):
		info = self.get_files()
#		print info
		if info:
			self.dir = info["dir"]
			# MiniAOD info:
			if "miniaod" in info.keys():
				# Set file variables:
				self.miniaod_dir = info["miniaod"]["dir"]
				self.miniaod_path = info["miniaod"]["files"]
			# Jets info:
			if "jets" in info.keys():
				# Set file variables:
				self.jets_dir = info["jets"]["dir"]
				self.jets_path = info["jets"]["files"]
				
#			# Tuple info:
#			if "tuple" in info.keys():
#				self.dir_tuple = info["tuple"]["dir"]
#				self.files_tuple = info["tuple"]["files"]
			return True
		else:
			return False
	
	def set_nevents(self):
		n = 0
		for f in self.jets_path:
			n += analysis.get_nevents(f)
		self.n = n
		self.nevents = n
		
	# /Methods
# /CLASSES

# FUNCTIONS:
def get_datasets(path=os.path.join(decortication.__path__[0], "..", "resources/samples.yaml"), name=None, process=None, key=None, generation="spring15", set_info=False):
	# Get dataset info:
	with open(path, 'r') as f:
		info = yaml.load(f)
	
	# Arguments:
	if process and not isinstance(process, list):
		process = [process]
	else:
		process = info.keys()
	if key and not isinstance(key, list):
		key = [key]
	
	# Apply some search parameters before starting:
	info = {k: ds for p, dss in info.iteritems() for k, ds in dss.iteritems() if p in process}
#	print info
	if key:
		info = {k: ds for k, ds in info.iteritems() if k in key}
#	print info
	
	# Find the dataset(s):
	datasets = {}
	for key, list_of_ds in info.iteritems():		# e.g., sq150tojjjj, qcdmg
		datasets[key] = []
		for ds in list_of_ds:		# The info for each dataset
			if ds["generation"] == generation:
				if (name and ds["name"] == name) or (not name):
					datasets[key].append(dataset(ds, set_info=set_info))
	
	# Trim results:
	datasets = {key: value for key, value in datasets.iteritems() if value}		# Delete any keys if the associated value is null.
	
	return datasets

def get_nevents(files):		# This is very slow with many files!
	nevents = 0
	for f in files:
		print f
		raw_output = Popen(['echo "Events->GetEntries()" | root -l {0}'.format(f)], shell=True, stdout=PIPE, stderr=PIPE).communicate()
		match = re.search("\(Long64_t\) (\d+)\s", raw_output[0])
		if match:
			nevents += int(match.group(1))
	return nevents
# /FUNCTIONS

# VARIABLES:
# /VARIABLES
