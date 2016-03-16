####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
from itertools import combinations
from truculence import physics
from numpy import mean
# /IMPORTS

# VARIABLES:
# /VARIABLES

# CLASSES:
# /CLASSES

# FUNCTIONS:
def get_pair(event, cut_pt=175, cut_m=50, cut_eta=2.5, r=12, ca=True, pf=True, v=False, leading=True):
	# Get information about the event from the tuple:
	prefix = "{0}{1}_{2}".format(("ak", "ca")[ca == True], r, ("gn", "pf")[pf == True])
	pxs = getattr(event, "{0}_px".format(prefix))
	pys = getattr(event, "{0}_py".format(prefix))
	pzs = getattr(event, "{0}_pz".format(prefix))
	es = getattr(event, "{0}_e".format(prefix))
	pts = getattr(event, "{0}_pt".format(prefix))
	Ms = getattr(event, "{0}_M".format(prefix))
	mts = getattr(event, "{0}_m_t".format(prefix))
	mps = getattr(event, "{0}_m_p".format(prefix))
	mss = getattr(event, "{0}_m_s".format(prefix))
	mfs = getattr(event, "{0}_m_f".format(prefix))
	etas = getattr(event, "{0}_eta".format(prefix))
	phis = getattr(event, "{0}_phi".format(prefix))
	tau1s = getattr(event, "{0}_tau1".format(prefix))
	tau2s = getattr(event, "{0}_tau2".format(prefix))
	tau3s = getattr(event, "{0}_tau3".format(prefix))
	tau4s = getattr(event, "{0}_tau4".format(prefix))
	
	# Make jet objects for the event:
	jets = []
	for i, pt in enumerate(pts):
#		M = Ms[i]
#		m = ms[i]
#		e = es[i]
#		eta = etas[i]
#		phi = phis[i]
##		theta = thetas[i]
		jet_temp = physics.jet(pxs[i], pys[i], pzs[i], es[i], tau=(tau1s[i], tau2s[i], tau3s[i], tau4s[i]))
		jet_temp.m_t = mts[i]
		jet_temp.m_p = mps[i]
		jet_temp.m_s = mss[i]
		jet_temp.m_f = mfs[i]
		jets.append(jet_temp)
#		print i, eta, jet_temp.eta
#		print i, phi, jet_temp.phi, " ({}, {}, {})".format(pxs[i], pys[i], pzs[i])
	
	pair = False
	
	if leading:
		jets = [j for j in jets if (j.pt >= cut_pt) and (abs(j.eta) <= cut_eta)]
		if len(jets) >= 2:
			pair = (jets[0], jets[1])
	else:
		# Apply cuts:
		jets = [j for j in jets if (j.pt >= cut_pt) and (abs(j.eta) <= cut_eta)]
	
		# Select jet pair:
	#	pairs = sorted([pair for pair in [p for p in combinations(jets, 2) if any(j.m >= cut_m for j in p)]], key=physics.delta_m)
		pairs = sorted([pair for pair in [p for p in combinations(jets, 2) if mean([j.m for j in p]) >= cut_m]], key=physics.delta_m)
		if v: print "There were {} jet(s) left after applying the pT cut of {} GeV. This resulted in {} viable pair(s) after the m cut of {} GeV.".format(len(jets), cut_pt, len(pairs), cut_m)
		if pairs:
			pair = pairs[0]
	
	return pair
# /FUNCTIONS
