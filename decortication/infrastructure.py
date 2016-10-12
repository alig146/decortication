####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import sys, os, yaml
import decortication
from truculence import utilities
# :IMPORTS

# VARIABLES:
ds_info_default = os.path.join(decortication.__path__[0], "..", "resources/samples.yaml")
db_info_default = os.path.join(decortication.__path__[0], "..", "resources/database.yaml")
parents = {		# KLUDGE
	"sample": None,
	"miniaod": "sample",
	"tuple": "miniaod",
}
# :VARIABLES

# CLASSES:
class dataset_kind:
	def __init__(self, name, plural=None, path=db_info_default):
		self.name = name
		self.plural = plural
		if self.plural == None:
			self.plural = self.name + "s"
		self.path = path
	
	
	def __str__(self):
		return self.name
	
	
	def get_primary_keys(self, path=None):
		if path == None:
			path = self.path
		db_info = get_db_info(path=path)[self.name]
		return [key for key, info in db_info.items() if info["primary"]]
	
	
	def get_relative(self, up_down, path=None):		# up_down: 1 for parent, -1 for child
		if path == None:
			path = self.path
		
		db_info = get_db_info(path=path)
		kind_hierarchy = db_info.keys()
		i_self = kind_hierarchy.index(self.name)
		i_relative = i_self - up_down		# parents have lower indices ...
		if i_relative < 0: i_relative = 0
		if i_relative >= len(kind_hierarchy): i_relative = len(kind_hierarchy) - 1
		
		relative_name = kind_hierarchy[i_relative]
		return dataset_kind(relative_name, path=path)
	
	
	def get_parent(self, path=None):
		return self.get_relative(1, path=path)
	
	
	def get_child(self, path=None):
		return self.get_relative(-1, path=path)
# :CLASSES

# FUNCTIONS:
# Database information things:
def get_db_info(path=db_info_default):
	# Returns dictionary of meta information, keyed by kind.
	
	# Read in the YAML:
	with open(path, 'r') as f:
		db_info = utilities.ordered_load(f)
		info_db_full = db_info
		for kind, info in db_info.items():
			for key, meta_dict in info.items():
				# Fill defaults (if they aren't specified):
				if "type" not in meta_dict:
					info_db_full[kind][key]["type"] = "text"
				if "primary" not in meta_dict:
					info_db_full[kind][key]["primary"] = False
				if "default" not in meta_dict:
					info_db_full[kind][key]["default"] = None
		return info_db_full

# Kind things:
def get_kinds(path=db_info_default):
	db_info = get_db_info(path=path)
	return [dataset_kind(kind_name) for kind_name in db_info.keys()]

def get_kind(kind_name, path=db_info_default):
	for kind in get_kinds(path=path):
		if kind.name == kind_name:
			return kind

# Dataset information things:
def complete(dataset_info, db_info):
	
	to_return = {}
	
	for kind in get_kinds():
		to_return[kind.plural] = []
		
		dicts_incomplete = dataset_info[kind.plural]
		for i, dict_incomplete in enumerate(dicts_incomplete):
			dict_complete = {k: v for k, v in dict_incomplete.items()}		# Copy.
			for key, meta in db_info[kind.name].items():
				if key not in dict_incomplete:
					dict_complete[key] = meta["default"]		# Maybe I should type things at this point.
				value = dict_complete[key]
				
				# Account for uppercase references ("PROCESS", etc.):
				if isinstance(value, str):
					if (not value.isdigit()) and (value == value.upper()) and (value not in ["PARENT"]):
						dict_complete[key] = dict_complete[value.lower()]
					elif value in ["PARENT"]:
						if kind.name == "sample":
							print "ERROR (infrastructure.complete): Something is weird in the sample dict_complete:"
							print dict_complete
							sys.exit()
						else:
							dict_complete[key] = to_return[kind.get_parent().plural][0][key]
			to_return[kind.plural].append(dict_complete)
	
	return to_return
#		
#		
#		# OLD COMPLETE: I can delete this.
#	# Complete sample:
#	sample_dict = dataset_info["sample"]
#	sample_dict_complete = sample_dict
#	for key, meta in db_info["sample"].items():
#		if key not in sample_dict:
#			sample_dict_complete[key] = meta["default"]
#		value = sample_dict_complete[key]
#		
#		# Account for uppercase references ("PROCESS", etc.):
#		if isinstance(value, str):
#			if (not value.isdigit()) and (value == value.upper()) and (value not in ["PARENT", "CHILD"]):
#				sample_dict_complete[key] = sample_dict_complete[value.lower()]
#			elif value in ["PARENT", "CHILD"]:
#				print "ERROR (infrastructure.complete): Something is weird in the sample_dict_complete:"
#				print sample_dict_complete
#				sys.exit()
#	
#	# Complete miniaods:
#	miniaod_dicts = dataset_info["miniaods"]
#	miniaod_dicts_complete = []
#	for miniaod_dict in miniaod_dicts:
#		for key, meta in db_info["miniaod"].items():
#			if key not in miniaod_dict:
#				miniaod_dict[key] = meta["default"]
#			value = miniaod_dict[key]
#			
#			# Parse "name":
#			if key == "name":
#				if value.count("/") < 2:
#					miniaod_dict[key] = "/{}/".format(sample_dict_complete[key]) + value
#				elif value.count("/") == 2:
#					miniaod_dict[key] = "/" + value
#			
#			# Account for uppercase references ("PROCESS", etc.):
#			if isinstance(value, str):
#				if (not value.isdigit()) and (value == value.upper()) and (value not in ["PARENT", "CHILD"]):
#					miniaod_dict[key] = miniaod_dict[value.lower()]
#				elif value == "PARENT":
#					miniaod_dict[key] = sample_dict_complete[key]
#				elif value == "CHILD":
#					print "ERROR (infrastructure.complete): 'CHILD' hasn't been implemented, yet."
#					print miniaod_dict
#					sys.exit()
#		
#		miniaod_dicts_complete.append(miniaod_dict)
#	
#	return {"sample": sample_dict_complete, "miniaods": miniaod_dicts_complete}



def get_ds_info(path_samples=ds_info_default, path_meta=db_info_default):
	# Makes a list of dictionaries keyed by kind: [{"sample": sample1_dict, "miniaods": [miniaod1_dict, miniaod2_dict]}, ...]
	# Returns a dictionary for each kind, valued by lists of info dicts.
	
	db_info = get_db_info(path=path_meta)
	primaries = {kind: [key for key, meta in kind_info.items() if meta["primary"]] for kind, kind_info in db_info.items()}
	kinds = get_kinds(path=path_meta)
	
	# Get YAML information:
	with open(path_samples, 'r') as f:
		ds_info = yaml.load(f)
	
	# Prepare structure:
	dataset_infos = []
	
	# Parse the "ds_info":
	for category, processes in ds_info.items():
		for process, dss in processes.items():
			for ds in dss:
				dataset_info = {}
				# Handle "sample" kind:
				sample = {key: value for key, value in ds.items() if key not in [k.plural for k in kinds]}
				## Add inferred values: 
				sample.update({
					"category": category,
					"process": process,
				})
				## Create "parameters" element:
				parameters = [value for key, value in sample.items() if key in ["m", "ms", "hts", "pts"]]
				parameters = [item if isinstance(item, list) else [item] for item in parameters]
				parameters = [item for sublist in parameters for item in sublist]
				for i, p in enumerate(parameters):
					sample["parameter{}".format(i+1)] = p
				
				## Organize into temporary structure for completing:
				dataset_info["samples"] = [sample]
				
				# Hand other kinds:
				for kind in [k for k in kinds if k.name != "sample"]:
					dataset_info[kind.plural] = []
					if kind.plural in ds:
						dataset_info[kind.plural] = ds[kind.plural]
				
				# Finish:
				dataset_infos.append(dataset_info)
	
	# Complete the info in each dataset_info:
	dataset_infos_complete = [complete(dataset_info, db_info) for dataset_info in dataset_infos]
#	return dataset_infos_complete
	# Format returned structure:
	to_return = {}
	for dataset_info in dataset_infos_complete:
#		print dataset_info
		for kind in kinds:
			if kind.name not in to_return:		# I revert from kind plural to singular here.
				to_return[kind.name] = []
			to_return[kind.name].extend(dataset_info[kind.plural])
	return to_return
# :FUNCTIONS
