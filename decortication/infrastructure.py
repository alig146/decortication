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
# :CLASSES

# FUNCTIONS:
def complete(sample_tree, db_info):
	# Complete sample:
	sample_dict = sample_tree["sample"]
	sample_dict_complete = sample_dict
	for key, meta in db_info["sample"].items():
		if key not in sample_dict:
			sample_dict_complete[key] = meta["default"]
		value = sample_dict_complete[key]
		
		# Account for uppercase references ("PROCESS", etc.):
		if isinstance(value, str):
			if (not value.isdigit()) and (value == value.upper()) and (value not in ["PARENT", "CHILD"]):
				sample_dict_complete[key] = sample_dict_complete[value.lower()]
			elif value in ["PARENT", "CHILD"]:
				print "ERROR (infrastructure.complete): Something is weird in the sample_dict_complete:"
				print sample_dict_complete
				sys.exit()
	
	# Complete miniaods:
	miniaod_dicts = sample_tree["miniaods"]
	miniaod_dicts_complete = []
	for miniaod_dict in miniaod_dicts:
		for key, meta in db_info["miniaod"].items():
			if key not in miniaod_dict:
				miniaod_dict[key] = meta["default"]
			value = miniaod_dict[key]
			
			# Parse "name":
			if key == "name":
				if value.count("/") < 2:
					miniaod_dict[key] = "/{}/".format(sample_dict_complete[key]) + value
				elif value.count("/") == 2:
					miniaod_dict[key] = "/" + value
			
			# Account for uppercase references ("PROCESS", etc.):
			if isinstance(value, str):
				if (not value.isdigit()) and (value == value.upper()) and (value not in ["PARENT", "CHILD"]):
					miniaod_dict[key] = miniaod_dict[value.lower()]
				elif value == "PARENT":
					miniaod_dict[key] = sample_dict_complete[key]
				elif value == "CHILD":
					print "ERROR (infrastructure.complete): 'CHILD' hasn't been implemented, yet."
					print miniaod_dict
					sys.exit()
		
		miniaod_dicts_complete.append(miniaod_dict)
	
	return {"sample": sample_dict_complete, "miniaods": miniaod_dicts_complete}


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


def get_ds_info(path_samples=ds_info_default, path_meta=db_info_default):
	# Makes a list of dictionaries keyed by kind: [{"sample": sample1_dict, "miniaods": [miniaod1_dict, miniaod2_dict]}, ...]
	# Returns a dictionary for each kind, valued by lists of info dicts.
	
	db_info = get_db_info(path=path_meta)
	primaries = {kind: [key for key, meta in kind_info.items() if meta["primary"]] for kind, kind_info in db_info.items()}
	
	# Get YAML information:
	with open(path_samples, 'r') as f:
		ds_info = yaml.load(f)
	
	# Prepare structure:
	sample_trees = []
	
	# Parse the "ds_info":
	for category, processes in ds_info.items():
		for process, samples in processes.items():
			for sample in samples:
				sample_tree = {}
				if "miniaods" in sample:
					sample_tree["miniaods"] = sample["miniaods"]
				else:
					sample_tree["miniaods"] = []
				sample = {key: value for key, value in sample.items() if key != "miniaods"}
				
				# Add elements:
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
				
				# Organize into temporary structure for completing:
				sample_tree["sample"] = sample
				
				sample_trees.append(sample_tree)
	
	# Complete the info in each sample_tree:
	sample_trees_complete = [complete(sample_tree, db_info) for sample_tree in sample_trees]
	
	# Format returned structure:
	samples_return = [sample_tree["sample"] for sample_tree in sample_trees_complete]
	miniaods_return = []
	for sample_tree in sample_trees_complete:
		miniaods_return += sample_tree["miniaods"]
	return {
		"sample": samples_return,
		"miniaod": miniaods_return,
	}
# :FUNCTIONS
