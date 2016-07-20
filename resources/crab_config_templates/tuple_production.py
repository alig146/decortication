from CRABClient.UserUtilities import config
configure = config()

# Variables
kind = "tuple"
process = "%%PROCESS%%"           # "qcdp", "sq150to4j", etc.
subprocess = "%%SUBPROCESS%%"     # "qcdp50", "sq150to4j", etc. This is used in the output name.
generation = "%%GENERATION%%"
suffix = "%%SUFFIX%%"
n = 10000                         # Number of events per job.
units = %%UNITS%%                 # The number of events to run over
# /Variables

configure.General.requestName = '{0}_{1}_{2}_{3}'.format(kind, subprocess, generation, suffix)
configure.General.workArea = 'crab_projects'
configure.General.transferLogs = True
configure.JobType.pluginName = 'Analysis'
configure.JobType.psetName = '%%CMSSWCONFIG%%'       # The CMSSW configuration file name
configure.JobType.pyCfgParams = %%LISTOFPARAMS%%     # The parameters passed to the CMSSW configuration file
configure.JobType.inputFiles = ["jec_data"]          # Files and directories that CRAB has access to.

configure.Data.inputDataset = '%%DATASET%%'          # Input dataset name
configure.Data.inputDBS = '%%INSTANCE%%'             # "global" (official), "phys03" (private), etc.

configure.Data.splitting = 'EventAwareLumiBased'
configure.Data.unitsPerJob = n
configure.Data.totalUnits = units
configure.Data.outLFNDirBase = '/store/user/elhughes'         # Only other option: "/store/group/<groupname>/<subdir>"
configure.Data.publication = False
configure.Data.outputDatasetTag = '{0}_{1}_{2}_{3}'.format(kind, subprocess, generation, suffix)

configure.JobType.maxMemoryMB = 5000

configure.Site.storageSite = 'T3_US_FNALLPC'
