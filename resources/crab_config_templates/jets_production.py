from CRABClient.UserUtilities import config
configure = config()

# Variables
kind = "jets"
process = "%%PROCESS%%"           # "qcdp", "sq150to4j", etc.
subprocess = "%%SUBPROCESS%%"     # "qcdp50", "sq150to4j", etc. This is used in the output name.
n = 10000                         # Number of events per job.
units = %%UNITS%%                 # The number of events to run over
# /Variables

configure.General.requestName = '{0}_{1}'.format(subprocess, kind)
configure.General.workArea = 'crab_projects'
configure.JobType.pluginName = 'Analysis'
configure.JobType.psetName = '%%CMSSWCONFIG%%'       # The CMSSW configuration file name
configure.JobType.pyCfgParams = %%LISTOFPARAMS%%     # The parameters passed to the CMSSW configuration file

configure.Data.inputDataset = '%%DATASET%%'          # Input dataset name
configure.Data.inputDBS = '%%INSTANCE%%'             # "global" (official), "phys03" (private), etc.

configure.Data.splitting = 'EventAwareLumiBased'
configure.Data.unitsPerJob = n
configure.Data.totalUnits = units
configure.Data.outLFNDirBase = '/store/user/elhughes'         # Only other option: "/store/group/<groupname>/<subdir>"
configure.Data.publication = True
configure.Data.outputDatasetTag = '{0}_{1}'.format(subprocess, kind)

configure.JobType.maxMemoryMB = 5000

configure.Site.storageSite = 'T3_US_FNALLPC'
