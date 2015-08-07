import samples
from ROOT import TChain
from truculence import *
from decortication import samples, plots

def get_tchain(version="spring15", ttree_name="analyzer/events", tchain_name="T", tchain_title="", pt_mins=None):
	process = "qcd"
	
	if pt_mins == None:
		pt_mins = samples.qcd_pt_mins
	elif not isinstance(pt_mins, list):
		pt_mins = [pt_mins]
	
	if set(pt_mins).issubset(set(samples.qcd_pt_mins)):
		tcs = {}
		tc = TChain(tchain_name, tchain_title)
		for d in samples.datasets[process][version]:
			if min(d.pts) in pt_mins:
				location = "{0}/{1}_ntuple.root/{2}".format(samples.ntuple_location, d.name, ttree_name)
				tc.Add(location)
		tcs["QCD_TuneCUETP8M1_13TeV_pythia8"] = tc
		return tcs
	else:
		print "ERROR (qcd.get_tchain): The pTs you entered (\"{0}\") were not recognized. You have to enter the lower limits of the pt bins you're interested in. The following values are accepted:\n\t{1}".format(pt_mins, samples.qcd_pt_mins)
		return False

# OLD:
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

