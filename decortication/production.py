####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, sys
from decortication import infrastructure
from truculence import analysis
# /IMPORTS

# VARIABLES:
# /VARIABLES

# CLASSES:
# /CLASSES

# FUNCTIONS:
def get_crab_config(
	kind="aod",
	sample=None,                               # A sample object
	generation="",
	suffix="",
	instance="",
	cmssw_config="fatjetproducer_cfg.py",
	cmssw_params={                              # The CMSSW configuration file parameters (these all get converted to strings)
		"crab": True,
	},
	units=-1,                                   # The number of events to run over ("-1" means "all")
	cut_pt_filter=300,
	cut_eta_filter=2.5,
):
	# Parse arguments and set other variables:
	dataset_name = ""
	## Basic stuff:
	if not sample and not miniaod:
		print "ERROR: Right now, crab_create needs a sample or a miniaod."
		sys.exit()
	elif miniaod:
		sample = miniaod.get_sample()
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
		suffix = "cutpt{}eta{}".format(cut_pt_filter, int(cut_eta_filter*10))
		cmssw_params["suffix"] = suffix
#	cmssw_params["dataset"] = dataset.name                    # See comment on line above.
#	cmssw_params["cmssw"] = analysis.get_cmssw()              # I stopped using this. The version is found inside of the CMSSW config. (Not changed for jets.)
	if kind == "tuple":
		cmssw_params["cutPtFilter"] = cut_pt_filter
		cmssw_params["cutEtaFilter"] = cut_eta_filter
		cmssw_params["data"] = sample.data
	params_str = "[\n"
	for key, value in cmssw_params.iteritems():
		params_str += "\t'{}={}',\n".format(key, value)
	params_str += "]"
	
#	params_str = str(["{0}={1}".format(key, value) for key, value in cmssw_params.iteritems()])
	# Prepare the template:
	## Get the template:
	template_path = get_res_path("crab_config_templates/{}_production.py".format(kind))
	with open(template_path, 'r') as f:
		template = f.read()
	## Replace fields:
	template = template.replace("%%PROCESS%%", process)
	template = template.replace("%%SUBPROCESS%%", subprocess)
	template = template.replace("%%GENERATION%%", generation)
	template = template.replace("%%SUFFIX%%", suffix)
	template = template.replace("%%DATASET%%", dataset_name)
	template = template.replace("%%NAME%%", sample.name)
	template = template.replace("%%PLUGINNAME%%", "PrivateMC" if kind in ["aod", "gen"] else "Analysis")
	template = template.replace("%%CMSSWCONFIG%%", cmssw_config)
	template = template.replace("%%LISTOFPARAMS%%", params_str)
#	template = template.replace("%%UNITS%%", str(units))
#	template = template.replace("%%CMSSW%%", analysis.get_cmssw())
	template = template.replace("%%INSTANCE%%", instance)
	if sample.mask: template = template.replace("%%MASK%%", "configure.Data.lumiMask = '{}'".format(sample.mask))
	else: template = template.replace("%%MASK%%", "")
	
	
	return template
# /FUNCTIONS
