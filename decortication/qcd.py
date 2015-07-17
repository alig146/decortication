import samples
from ROOT import TChain

def make_tchain(dataset_name, ttree_name="analyzer/events", tchain_name="T", tchain_title=""):
	tc = TChain(tchain_name, tchain_title)
	for sample_name in samples.qcd_info[dataset_name].keys():
		location = "{0}/{1}_ntuple.root/{2}".format(samples.ntuple_location, sample_name, ttree_name)
		tc.Add(location)
	return tc
