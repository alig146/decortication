####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
from truculence import *
import samples
import plots
import qcd
import ttbar
import lqtoue
# /IMPORTS

# CLASSES:
# /CLASSES


# FUNCTIONS:
def get_ntuple(process=None, version="spring15", ms=None, pt_mins=None, ttree_name="analyzer/events"):
	if process in samples.datasets:
		if process == "qcd":
			return qcd.get_tchain(version=version, ttree_name=ttree_name, pt_mins=pt_mins)
		elif process == "ttbar":
			return ttbar.get_ttree(version=version, ttree_name=ttree_name)
		elif process == "lqtoue":
			return lqtoue.get_ttree(version=version, ttree_name=ttree_name, ms=ms)
		else:
			print "ERROR (decorticate.get_ttree): The \"{0}\" process isn't implemented, yet.".format(process)
			return False
		return tts
	else:
		print "ERROR (decorticate.get_ttree): The \"{0}\" process was not recognized.".format(process)
		return False

def make_plots(process=None, version="spring15", ms=None, pt_mins=None, ttree_name="analyzer/events", max_events=-1, out_file="", out_dir=""):
	tts = get_ntuple(process=process, version=version, ms=ms, pt_mins=pt_mins, ttree_name=ttree_name)
	if tts:
		for name, tt in tts.iteritems():
			th1s = plots.make_th1s(tt, max_events=max_events)
			analysis.save_histograms([th1s, {}], samples.ntuple_location + "/{0}_plots.root".format(name))
	else:
		print "ERROR (decorticate.make_plots): Failed to get the ntuple for the \"{0}\" process.".format(process)
		return False

# draft:
def make_combined_plots(processes=["qcd", "ttbar", "lqtoue"], ms=300, pts=None, leg_labels=[], create_plots=False, max_events=-1, out_file="", out_dir=""):
	th1s = []
	for process in processes:
		tts = get_ntuple(process=process, ms=ms, pts=pts)
		print process, len(tts)
		for sample_name, tt in tts.iteritems():
			th1s.append(plots.make_th1s(tt, max_events=max_events)["ak8_pf_pt"])
	tc = analysis.superimpose(th1s, leg_labels=leg_labels, normalize=True)
	tc.SaveAs("test.pdf")
# /FUNCTIONS

# VARIABLES:
# /VARIABLES
