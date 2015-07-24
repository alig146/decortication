import samples
#from ROOT import TChain
from truculence import *
from decortication import samples, plots

def get_ttrees(dataset_name="spring15", ttree_name="analyzer/events"):
	tts = {}
	for sample_name in samples.lqtottau_info[dataset_name].keys():
		location = "{0}/{1}_ntuple.root".format(samples.ntuple_location, sample_name)
		tts[sample_name] = analysis.get_ttree(location)
	return tts

def make_plots(dataset_name="spring15", ttree_name="analyzer/events", max_events=-1):
	print "Getting ttrees ..."
	tts = get_ttrees(dataset_name=dataset_name, ttree_name=ttree_name)
	for sample_name in samples.lqtottau_info[dataset_name].keys():
		print "Making plots for {0} ...".format(sample_name)
		tt = get_ttrees()[sample_name]
		print "> There are {0} events in the tuple.".format(tt.GetEntries())
		print "> Making TH2 ..."
		th2 = plots.make_th2(tt, max_events=max_events)
		print "> Making TH1 ..."
		th1 = plots.make_th1(tt, max_events=max_events)
		print "> Saving plots ..."
		analysis.save_histograms([th1, th2], samples.ntuple_location + "/{0}_plots.root".format(sample_name))
