####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, sys
import decortication
from truculence import analysis
# /IMPORTS

# VARIABLES:
# /VARIABLES

# CLASSES:
# /CLASSES

# FUNCTIONS:
def get_crab_config(
	sample=None,                               # A sample object
	miniaod=None,                              # A miniaod object
	generation="",
	suffix="",
	instance="",
	cmssw_config="fatjetproducer_cfg.py",
	cmssw_params={                              # The CMSSW configuration file parameters (these all get converted to strings)
		"crab": True,
	},
	units=-1,                                   # The number of events to run over ("-1" means "all")
	cut_pt_filter=300,
	kind="tuple",
	mass=200,
):
	# Parse arguments and set other variables:
	dataset_name = ""
	## Basic stuff:
	if not sample and not miniaod:
		print "ERROR: Right now, crab_create needs a sample or a miniaod."
		sys.exit()
	elif miniaod:
		miniaod.set_connections(down=False, up=True)
		sample = miniaod.sample
		generation = miniaod.generation
		instance = miniaod.instance
		if units == -1:
			units = miniaod.n
		dataset_name = miniaod.name
	process = sample.process
	subprocess = sample.subprocess
	
	## CMSSW parameters:
	cmssw_params["subprocess"] = subprocess
	cmssw_params["generation"] = generation
	if kind == "tuple":
		suffix = "pt{}".format(cut_pt_filter)
		cmssw_params["suffix"] = suffix
#	cmssw_params["dataset"] = dataset.name                    # See comment on line above.
#	cmssw_params["cmssw"] = analysis.get_cmssw()              # I stopped using this. The version is found inside of the CMSSW config. (Not changed for jets.)
	if "tuple" in kind:
		cmssw_params["cutPtFilter"] = cut_pt_filter
		cmssw_params["cutPtFilter"] = cut_pt_filter
	params_str = "[\n"
	for key, value in cmssw_params.iteritems():
		params_str += "\t'{}={}',\n".format(key, value)
	params_str += "]"
	
#	params_str = str(["{0}={1}".format(key, value) for key, value in cmssw_params.iteritems()])
	# Prepare the template:
	## Get the template:
	template_path = os.path.join(decortication.__path__[0], "..", "resources/crab_config_templates/{}_production.py".format(kind))
	with open(template_path, 'r') as f:
		template = f.read()
	## Replace fields:
	template = template.replace("%%PROCESS%%", process)
	template = template.replace("%%SUBPROCESS%%", subprocess)
	template = template.replace("%%GENERATION%%", generation)
	template = template.replace("%%SUFFIX%%", suffix)
	template = template.replace("%%DATASET%%", dataset_name)
	template = template.replace("%%NAME%%", sample.name)
	template = template.replace("%%CMSSWCONFIG%%", cmssw_config)
	template = template.replace("%%LISTOFPARAMS%%", params_str)
	template = template.replace("%%UNITS%%", str(units))
#	template = template.replace("%%CMSSW%%", analysis.get_cmssw())
	template = template.replace("%%INSTANCE%%", instance)
	
	return template
# /FUNCTIONS
