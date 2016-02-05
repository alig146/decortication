# IMPORTS:
import os
import yaml
import decortication
import dataset
# /IMPORTS

# VARIABLES:
collections = [		# This should match the list that's in FatjetAnalyzer.cc
	"ak4_pf", "ak8_pf", "ca8_pf", "ak10_pf", "ca10_pf", "ak12_pf", "ca12_pf", "ak14_pf", "ca14_pf",
	"ak4_gn", "ak8_gn", "ca8_gn", "ak10_gn", "ca10_gn", "ak12_gn", "ca12_gn", "ak14_gn", "ca14_gn",
]
# /VARIABLES

# FUNCTIONS:
def get_datasets(path=os.path.join(decortication.__path__[0], "..", "resources/samples.yaml"), process=None, flavor=None):
#	print path
	with open(path, 'r') as f:
		info = yaml.load(f)
	
	datasets = {}
	for process, i in info.iteritems():		# e.g., sqtojjjj, qcdmg
		datasets[process] = {}
		for flavor, ds in i.iteritems():		# e.g., miniaod, jets
			datasets[process][flavor] = []
			for d in ds:		# The samples
				dataset_temp = dataset.dataset(
					name_full=d["name"],
					process=process,
					flavor=flavor,
				)
				for key, value in d.iteritems():
					if key != "name":
						setattr(dataset_temp, key, value)
				datasets[process][flavor].append(dataset_temp)
	return datasets

def get_dataset(name=None, process=None, generation=None, flavor=None, m=None, pts=None, hts=None):
	# Prepare:
	dataset_dict = get_datasets()
	
	# (1) Get by name:
	if name != None:
		# Make a list of all datasets:
		datasets = []
		for process_, flavors in dataset_dict.iteritems():
			for _flavor, ds in flavors.iteritems():
				datasets += ds
		
		# Look through it for the dataset in question:
		datasets = [d for d in datasets if (d.name == name)]
#		print datasets
		if (flavor != None):
			datasets = [d for d in datasets if (d.flavor == flavor)]
#		print datasets
		if (generation != None):
			datasets = [d for d in datasets if (d.generation == generation)]
#		print datasets
		
		# Return result:
		if len(datasets) == 1:
			return datasets[0]
		elif len(datasets) > 1:
			print "WARNING (samples.get_dataset): There were multiple datasets that matched your criterion of name = {0}, flavor = {1}, and generation = {2}. This function returns just the first one.".format(name, flavor, generation)
			return datasets[0]
		else:
			print "ERROR (samples.get_dataset): No dataset matched your criterion of name = {0}, flavor = {1}, and generation = {2}.".format(name, flavor, generation)
			return False
	
	# (2) Get by parameters:
	elif m != None:
		return [d for d in dataset_dict[process][flavor] if d.m == m]
	elif pts != None:
		return [d for d in dataset_dict[process][flavor] if d.pts == pts]
	elif hts != None:
		return [d for d in dataset_dict[process][flavor] if d.hts == hts]
	else:
		return [d for d in dataset_dict[process][flavor]]
# /FUNCTIONS

# VARIABLES:
datasets = []
for process, flavors in get_datasets().iteritems():
	for flavor, ds in flavors.iteritems():
		datasets += ds
# /VARIABLES
