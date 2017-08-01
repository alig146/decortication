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
	subprocess="",
	sample=None,
	miniaod=None,
	kind="aod",
	generation="",
	suffix="",
	dataset_out="",
	dataset_in="",
	instance="global",
	cmssw_config="aod_cfg.py",
	cmssw_params=None,                          # Input a dictionary
	units=-1,                                   # The number of events to run over ("-1" means "all")
	unitsper=100,
	publish=True,
	cut_pt_filter=300,
	cut_eta_filter=2.5,
):
	# Parse arguments and set other variables:
	assert((sample or miniaod) and kind and generation and dataset_out)
	if miniaod: sample = miniaod.get_sample()
	if not subprocess: subprocess = sample.subprocess
	
	## Request name:
	request_name = "{}_{}_{}".format(kind, subprocess, generation)
	if suffix: request_name += "_" + suffix
	
	## CMSSW configuration file parameters:
	if cmssw_params: assert(isinstance(cmssw_params, dict))
	else: cmssw_params = {}
	if "crab" not in cmssw_params: cmssw_params["crab"] = True
	if "subprocess" not in cmssw_params: cmssw_params["subprocess"] = subprocess
	if "generation" not in cmssw_params: cmssw_params["generation"] = generation
	if suffix and "suffix" not in cmssw_params: cmssw_params["suffix"] = suffix
	if kind == "tuple":
		cmssw_params["cutPtFilter"] = cut_pt_filter
		cmssw_params["cutEtaFilter"] = cut_eta_filter
		cmssw_params["data"] = sample.data
	### Make a string for these parameters for the CRAB configuration file:
	params_str = "[\n"
	for key, value in cmssw_params.iteritems():
		params_str += "\t'{}={}',\n".format(key, value)
	params_str += "]"
	
	## Other variables:
	mask = False
	if miniaod: mask = miniaod.mask
	
	# Prepare the template:
	## Get the template:
	template_path = infrastructure.get_res_path("crab_config_templates/dataset_production.py")
	with open(template_path, 'r') as f:
		template = f.read()
	## Replace fields:
	template = template.replace("%%KIND%%", kind)
	template = template.replace("%%REQUESTNAME%%", request_name)
	template = template.replace("%%PLUGINNAME%%", "PrivateMC" if kind in ["aod", "gen"] else "Analysis")
	template = template.replace("%%CMSSWCONFIG%%", cmssw_config)
	template = template.replace("%%LISTOFPARAMS%%", params_str)
	template = template.replace("%%DATASET%%", dataset_out)
	template = template.replace("%%DATASETFULL%%", dataset_in)
	template = template.replace("%%INSTANCE%%", instance)
	template = template.replace("%%UNITSPER%%", str(unitsper))
	template = template.replace("%%UNITS%%", str(units))
	template = template.replace("%%PUBLICATION%%", str(publish))
	template = template.replace("%%MASK%%", mask if mask else "")
	
	return template
# /FUNCTIONS
