####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os
import decortication
from truculence import analysis
# /IMPORTS

# VARIABLES:
# /VARIABLES

# CLASSES:
# /CLASSES

# FUNCTIONS:
def get_crab_config(
	miniaod=None,                              # A miniaod object (optional)
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
	## Basic stuff:
	miniaod.set_connections(down=False, up=True)
	sample = miniaod.sample
	process = sample.process
	subprocess = miniaod.subprocess
	generation = miniaod.generation
	suffix = "pt{}".format(cut_pt_filter)
	instance = miniaod.instance
	
	## Units:
	if units == -1:
		units = miniaod.n
	## CMSSW parameters:
	cmssw_params["subprocess"] = subprocess
	cmssw_params["generation"] = generation
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
	template = template.replace("%%DATASET%%", miniaod.name)
	template = template.replace("%%NAME%%", sample.name)
	template = template.replace("%%CMSSWCONFIG%%", cmssw_config)
	template = template.replace("%%LISTOFPARAMS%%", params_str)
	template = template.replace("%%UNITS%%", str(units))
#	template = template.replace("%%CMSSW%%", analysis.get_cmssw())
	template = template.replace("%%INSTANCE%%", instance)
	
	return template
# /FUNCTIONS
