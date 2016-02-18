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
):
	# Parse arguments and set other variables:
	## Units:
	if units == -1:
		units = dataset.n_miniaod
	## CMSSW parameters:
	cmssw_params["dataset"] = dataset.process
	params_str = str(["'{}'='{}'," for key, value in cmssw_params.iteritems()])
	## CRAB parameters:
	instance = "global" if dataset.process in ["qcdp", "qcdmg", "ttbar"] else "phys03"
	
	# Prepare the template:
	## Get the template:
	template_path = os.path.join(decortication.__path__[0], "..", "resources/crab_config_templates/jets_production.py")
	with open(template_path, 'r') as f:
		template = f.read()
	## Replace fields:
	template = template.replace("%%PROCESS%%", dataset.process)
	template = template.replace("%%SUBPROCESS%%", dataset.subprocess)
	template = template.replace("%%DATASET%%", dataset.name + "/" + dataset.miniaod)
	template = template.replace("%%CMSSWCONFIG%%", cmssw_config)
	template = template.replace("%%LISTOFPARAMS%%", params_str)
	template = template.replace("%%UNITS%%", units)
	template = template.replace("%%CMSSW%%", analysis.get_cmssw())
	template = template.replace("%%INSTANCE%%", instance)
	
	return template
# /FUNCTIONS
