from CRABClient.UserUtilities import config
configure = config()

kind = '%%KIND%%'
mask = '%%MASK%%'

configure.General.requestName = '%%REQUESTNAME%%'
configure.General.workArea = 'crab_projects'
configure.General.transferLogs = True
configure.JobType.pluginName = '%%PLUGINNAME%%'
configure.JobType.psetName = '%%CMSSWCONFIG%%'       # The CMSSW configuration file name
configure.JobType.pyCfgParams = %%LISTOFPARAMS%%     # The parameters passed to the CMSSW configuration file
if kind == "tuple": configure.JobType.inputFiles = ["jec_data", "pileup_data"]          # Files and directories that CRAB has access to.

if kind == "aod": configure.Data.outputPrimaryDataset = '%%DATASET%%'          # Output dataset
if kind not in ["aod", "gen"]: 
	configure.Data.inputDataset = '%%DATASETFULL%%'          # Input dataset name
	configure.Data.inputDBS = '%%INSTANCE%%'             # "global" (official), "phys03" (private), etc.

if configure.JobType.pluginName == "PrivateMC": configure.Data.splitting = 'EventBased'
else: configure.Data.splitting = 'EventAwareLumiBased'
configure.Data.unitsPerJob = %%UNITSPER%%
if configure.JobType.pluginName == "PrivateMC": configure.Data.totalUnits = %%UNITS%%
configure.Data.outLFNDirBase = '/store/user/elhughes'         # Only other option: "/store/group/<groupname>/<subdir>"
configure.Data.publication = %%PUBLICATION%%
configure.Data.outputDatasetTag = '%%REQUESTNAME%%'
if mask: configure.Data.lumiMask = mask

configure.JobType.maxMemoryMB = 6000

configure.Site.storageSite = 'T3_US_FNALLPC'
