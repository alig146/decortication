import samples
from ROOT import TChain
from truculence import *
from decortication import samples, plots

def get_tchain(ds_version="spring15", ttree_name="analyzer/events", tchain_name="T", tchain_title="", pts=None):
	ds_name = "qcd"
	
	if pts == None:
		pts = samples.qcd_pts_mins
	elif not isinstance(pts, list):
		pts = [pts]
	
	if set(pts).issubset(set(samples.qcd_pts_mins)):
		tcs = {}
		tc = TChain(tchain_name, tchain_title)
		for sample_name, values in samples.info[ds_name][ds_version].iteritems():
			if values[2][0] in pts:
				location = "{0}/{1}_ntuple.root/{2}".format(samples.ntuple_location, sample_name, ttree_name)
				tc.Add(location)
		tcs["QCD_TuneCUETP8M1_13TeV_pythia8"] = tc
		return tcs
	else:
		print "ERROR (qcd.get_tchain): The pTs you entered (\"{0}\") were not recognized. You have to enter the lower limits of the pt bins you're interested in. The following values are accepted:\n\t{1}".format(pts, samples.qcd_pts_mins)
		return False

def make_plots(dataset_name="spring15", ttree_name="analyzer/events", max_events=-1):
	sample_name = "QCD_TuneCUETP8M1_13TeV_pythia8"
	print "Making tchain ..."
	tc = make_tchain(dataset_name=dataset_name, ttree_name=ttree_name)
	print "> There are {0} events in the tuple.".format(tc.GetEntries())
	print "> Making TH2 ..."
	th2 = plots.make_th2(tc, max_events=max_events)
	print "> Making TH1 ..."
	th1 = plots.make_th1(tc, max_events=max_events)
	print "> Saving plots ..."
	analysis.save_histograms([th1, th2], samples.ntuple_location + "/{0}_plots.root".format(sample_name))

