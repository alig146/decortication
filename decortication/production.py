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
	dataset=None,                               # The dataset object
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
	## Units:
	if units == -1:
		units = dataset.miniaod_n
	## CMSSW parameters:
	cmssw_params["subprocess"] = dataset.subprocess           # I started using this instead of "dataset", but didn't change it for jets.
#	cmssw_params["dataset"] = dataset.name                    # See comment on line above.
#	cmssw_params["cmssw"] = analysis.get_cmssw()              # I stopped using this. The version is found inside of the CMSSW config. (Not changed for jets.)
	if "tuple" in kind:
		cmssw_params["cutPtFilter"] = cut_pt_filter
	params_str = "[\n"
	for key, value in cmssw_params.iteritems():
		params_str += "\t'{}={}',\n".format(key, value)
	params_str += "]"
	
#	params_str = str(["{0}={1}".format(key, value) for key, value in cmssw_params.iteritems()])
	## CRAB parameters:
	instance = "global" if dataset.process in ["qcdp", "qcdmg", "ttbar"] else "phys03"
	
	# Prepare the template:
	## Get the template:
	template_path = os.path.join(decortication.__path__[0], "..", "resources/crab_config_templates/{}_production.py".format(kind))
	with open(template_path, 'r') as f:
		template = f.read()
	## Replace fields:
	template = template.replace("%%PROCESS%%", dataset.process)
	template = template.replace("%%SUBPROCESS%%", dataset.subprocess)
	template = template.replace("%%DATASET%%", "/" + dataset.name + "/" + dataset.miniaod)
	template = template.replace("%%NAME%%", dataset.name)
	template = template.replace("%%CMSSWCONFIG%%", cmssw_config)
	template = template.replace("%%LISTOFPARAMS%%", params_str)
	template = template.replace("%%UNITS%%", str(units))
#	template = template.replace("%%CMSSW%%", analysis.get_cmssw())
	template = template.replace("%%INSTANCE%%", instance)
	
	return template
# /FUNCTIONS
