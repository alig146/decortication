####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, yaml, re, sys
from subprocess import Popen, PIPE
from truculence import analysis, das
import decortication
from decortication import eos
# /IMPORTS

# VARIABLES
username = "tote"
data_dir = "/store/user/" + username
tuple_dir = data_dir + "/data/fat"
signal_processes = ["sqto4j", "sqto2j"]
info_path_default = os.path.join(decortication.__path__[0], "..", "resources/samples.yaml")
# /VARIABLES

# CLASSES:
class dataset:
	# Construction:
	def __init__(self, info=None, set_info=False, suffix=""):
		# Basic attributes:
		self.luminosity = 10000		# In inverse pb
		self.suffix = suffix
		for key, value in info.iteritems():
			setattr(self, key, value)
		self.weight = self.sigma*self.luminosity/self.miniaod_n
		self.w = self.weight
		if not hasattr(self, "analyze"):
			self.analyze = True
		## I do the following to make sure that dataset booleans work (see __nonzero__ below):
		if "name" not in info:
			self.name = False
		
		# Simple calculated assignments:
		self.miniaod_name = "/{}/{}".format(self.name, self.miniaod)
		if hasattr(self, "jets"):
			self.jets_name = "/{}/{}".format(self.name, self.jets)
		else:
			self.jets = None
			self.jets_name = None
#		self.tuple_file = "{}_tuple.root".format(self.name)
#		self.tuple_path = "{}/{}/{}_tuples/{}".format(data_dir, self.name, self.subprocess, self.tuple_file)
#		self.tuple_path = tuple_dir + "/" + self.tuple_file
		self.tuple_dir = None
		self.tuple_path = None
		
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
		dirs_miniaod = [d for d in dirs_flavor if d == self.name]
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
		dirs_fatjet = [d for d in dirs_flavor if d == "{}_jets".format(self.subprocess)]
		results["jets"] = {}
		if len(dirs_fatjet) > 1:
			print "ERROR (decortication.dataset.get_files): There is more than one jets directory: {0}".format(dirs_fatjet)
			return False
		elif len(dirs_fatjet) == 1:
			dir_fatjet = ds_dir + "/" + dirs_fatjet[0]
			dates = eos.listdir(dir_fatjet)
			dir_fatjet += "/" + dates[-1]
			results["jets"]["dir"] = dir_fatjet
			
			results["jets"]["files"] = []
			subdirs = eos.listdir(dir_fatjet)		# "0000", "0001", etc.
			for subdir in subdirs:
				path_dir = dir_fatjet + "/" + subdir
				results["jets"]["files"].extend([path_dir + "/" + f for f in eos.listdir(path_dir) if ".root" in f])
		else:
			results["jets"]["dir"] = None
			results["jets"]["files"] = None
		
		## Tuple:
		if self.suffix:
			dirs_fatjet = [d for d in dirs_flavor if d == "{}_tuple_{}".format(self.subprocess, self.suffix)]
		else:
			dirs_fatjet = [d for d in dirs_flavor if d == "{}_tuple".format(self.subprocess)]
		results["tuple"] = {}
		if len(dirs_fatjet) > 1:
			print "ERROR (decortication.dataset.get_files): There is more than one tuple directory: {0}".format(dirs_fatjet)
			return False
		elif len(dirs_fatjet) == 1:
			dir_fatjet = ds_dir + "/" + dirs_fatjet[0]
			dates = eos.listdir(dir_fatjet)
			dir_fatjet += "/" + dates[-1]
			results["tuple"]["dir"] = dir_fatjet
			
			results["tuple"]["files"] = []
			subdirs = eos.listdir(dir_fatjet)		# "0000", "0001", etc.
			for subdir in subdirs:
				path_dir = dir_fatjet + "/" + subdir
				results["tuple"]["files"].extend([path_dir + "/" + f for f in eos.listdir(path_dir) if ".root" in f])
		else:
			results["tuple"]["dir"] = None
			results["tuple"]["files"] = None
		
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
				
			# Tuple info:
			if "tuple" in info.keys():
				self.tuple_dir = info["tuple"]["dir"]
				self.tuple_path = info["tuple"]["files"]
			return True
		else:
			return False
	
	
	def set_nevents(self):
		n = 0
		for f in self.jets_path:
			n += analysis.get_nevents(f)
		self.jets_n = n
		self.n_jets = n
		self.nevents = n
		return n
		
	# /Methods
# /CLASSES

# FUNCTIONS:
def explore_dataset_dir(d):
	result = {}
	dates = eos.listdir(d)
	d += "/" + dates[-1]
	result["dir"] = d
	result["files"] = []
	subdirs = eos.listdir(d)		# "0000", "0001", etc.
	for subdir in subdirs:
		path_dir = d + "/" + subdir
		result["files"].extend([path_dir + "/" + f for f in eos.listdir(path_dir) if ".root" in f])
	return result


def get_info(path=info_path_default):
	# Get YAML information:
	with open(path, 'r') as f:
		info = yaml.load(f)
	
	# Fill missing information:
	info_filled = info
	for category, dsd in info.iteritems():
		for process, dss in dsd.iteritems():
			for i, ds in enumerate(dss):
				info_filled[category][process][i]["category"] = category
				info_filled[category][process][i]["process"] = process
				if "subprocess" not in ds:
					info_filled[category][process][i]["subprocess"] = process
	
	return info_filled


def get_datasets(path=info_path_default, name=None, subprocess=None, process=None, category=None, generation="spring15", suffix='', set_info=False):
	# Get dataset info:
	info = get_info(path=path)
	
	# Arguments:
	if subprocess and not isinstance("subprocess", list):
		subprocess = [subprocess]
	
	## All datasets are fetched by subprocess or more general info. (Name is converted to subprocess)
	call = -1
	if not name and not subprocess:
		call = False
	elif not name and subprocess:
		call = True
	elif name and not subprocess:
		subprocess = get_subprocess(name=name)
		call = True
	assert call != -1
	
	if category and not isinstance(category, list):
		category = [category]
	elif not category:
		category = info.keys()
	if process and not isinstance(process, list):
		process = [process]
	
	# Apply some search parameters before starting:
	info = {p: dss for c, dsd in info.iteritems() for p, dss in dsd.iteritems() if c in category}   # Filter categories, then ignore
	if process:
		info = {p: dss for p, dss in info.iteritems() if p in process}      # Filter processes
	
	# Find the dataset(s):
	datasets = {}
	for process, list_of_ds in info.iteritems():		# e.g., sq150to4j, qcdmg
		datasets[process] = []
		for ds in list_of_ds:		# The info for each dataset
			if ds["generation"] == generation:
				if call:
					if ds["subprocess"] in subprocess:
						datasets[process].append(dataset(info=ds, suffix=suffix, set_info=set_info))
				else:
					datasets[process].append(dataset(info=ds, suffix=suffix, set_info=set_info))
	
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


def get_paths(miniaod_name):
	das_url = "https://cmsweb.cern.ch"
	das_query = "file dataset={}".format(miniaod_name)
	data = das.get_data(das_url, das_query, 0, 0, 0, ckey=das.x509(), cert=das.x509())
	return [f["file"][0]["name"] for f in data["data"]]

## Variable conversions:
def get_subprocess(path=info_path_default, name=None):
	# Arguments:
	if name and not isinstance(name, list):
		name = [name]
	
	# Get dataset info:
	info = get_info(path=path)
	dss = [ds for c, dsd in info.iteritems() for p, dss in dsd.iteritems() for ds in dss]    # Make a list of all dataset infos.
	
	# Get subprocesses:
	if name:
		subprocesses = [ds["subprocess"] for ds in dss if ds["name"] in name]
	else:
		subprocesses = [ds["subprocess"] for ds in dss]
	
	return subprocesses
# /FUNCTIONS

# VARIABLES:
# /VARIABLES
