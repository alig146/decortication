#!/bin/bash

shopt -s expand_aliases
alias cachedir='echo -e "Signature: 8a477f597d28d172789f06886806bc55\n# This file is a cache directory tag.\n# For information about cache directory tags, see:\n#       http://www.brynosaurus.com/cachedir/" > CACHEDIR.TAG'

current=`pwd`

# Write "cache files" in the dirs I don't want to transfer with jobs":
cd $CMSSW_BASE/tmp
cachedir
cd $CMSSW_BASE/src/.git
cachedir
cd $CMSSW_BASE/src/Analyzers/FatjetAnalyzer/test/crab_projects
cachedir
cd $CMSSW_BASE/src/Analyzers/FatjetAnalyzer/test/condor_jobs
cachedir
cd $CMSSW_BASE/src/Analyzers/FatjetAnalyzer/test/analysis
cachedir
cd $CMSSW_BASE/src/Producers
cachedir

cd $current
