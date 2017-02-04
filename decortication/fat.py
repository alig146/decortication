####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
from itertools import combinations
from truculence import physics
from numpy import mean
from re import search
# /IMPORTS

# VARIABLES:
# /VARIABLES

# CLASSES:
# /CLASSES

# FUNCTIONS:
def get_pair(event, cut_pt=0, cut_m=0, cut_eta=100, alg="ca12", pf=True, v=False, leading=True):
	# Parse:
	match = search("(\w+)(\d+)", alg)
	if match:
		alg_name = match.group(1)
		alg_r = int(match.group(2))
	else:
		alg_name = "ca"
		alg_r = 12
	
	# Get information about the event from the tuple:
	prefix = "{}_{}".format(alg, ("gn", "pf")[pf == True])
	pxs = getattr(event, "{0}_px".format(prefix))
	pys = getattr(event, "{0}_py".format(prefix))
	pzs = getattr(event, "{0}_pz".format(prefix))
	es = getattr(event, "{0}_e".format(prefix))
	pts = getattr(event, "{0}_pt".format(prefix))
	ms = getattr(event, "{0}_m".format(prefix))
	etas = getattr(event, "{0}_eta".format(prefix))
	phis = getattr(event, "{0}_phi".format(prefix))
	tau1s = getattr(event, "{0}_tau1".format(prefix))
	tau2s = getattr(event, "{0}_tau2".format(prefix))
	tau3s = getattr(event, "{0}_tau3".format(prefix))
	tau4s = getattr(event, "{0}_tau4".format(prefix))
	jecs = getattr(event, "{0}_jec".format(prefix))
	jmcs = getattr(event, "{0}_jmc".format(prefix))
	
	# JetID variables:
	neef = getattr(event, "{0}_neef".format(prefix))    # Neutral EM energy fraction
	ceef = getattr(event, "{0}_ceef".format(prefix))    # Charged EM energy fraction
	nhef = getattr(event, "{0}_nhef".format(prefix))    # Neutral hadron energy fraction
	chef = getattr(event, "{0}_chef".format(prefix))    # Charged hadron energy fraction
	mef = getattr(event, "{0}_mef".format(prefix))      # Muon energy fraction
	nm = getattr(event, "{0}_nm".format(prefix))        # Neutral multiplicity
	cm = getattr(event, "{0}_cm".format(prefix))        # Charged multiplicity
	n = getattr(event, "{0}_n".format(prefix))          # Number of constituents
	
	# Subjet variables:
#	spx0 = getattr(event, "{0}_spx0".format(prefix))    # pxs of the leading subjets
#	spy0 = getattr(event, "{0}_spy0".format(prefix))
#	spz0 = getattr(event, "{0}_spz0".format(prefix))
#	se0 = getattr(event, "{0}_se0".format(prefix))
#	spt0 = getattr(event, "{0}_spt0".format(prefix))
#	sm0 = getattr(event, "{0}_sm0".format(prefix))
#	seta0 = getattr(event, "{0}_seta0".format(prefix))
#	sphi0 = getattr(event, "{0}_sphi0".format(prefix))
	
	# Make jet objects for the event:
	jets = []
	for i, pt in enumerate(pts):
#		M = Ms[i]
#		m = ms[i]
#		e = es[i]
#		eta = etas[i]
#		phi = phis[i]
##		theta = thetas[i]
		jet_temp = physics.jet(pxs[i], pys[i], pzs[i], es[i], tau=(tau1s[i], tau2s[i], tau3s[i], tau4s[i]), jec=jecs[i], jmc=jmcs[i], index=i)
		
		# Assign a JetID variable:
		jet_temp.jetid = False		# True means "passed".
		if (nhef[i] < 0.99 and neef[i] < 0.99 and n[i] > 1):		# Loose
#		if (nhef[i] < 0.90 and neef[i] < 0.90 and n[i] > 1):		# Tight
			if abs(jet_temp.eta) <= 2.4:
#				jet_temp.jetid = True
				if (ceef[i] < 0.99 and chef[i] > 0 and cm[i] > 0):		# Loose and tight are the same here.
					jet_temp.jetid = True
			else:
				jet_temp.jetid = True
		
		jets.append(jet_temp)
#		print i, eta, jet_temp.eta
#		print i, phi, jet_temp.phi, " ({}, {}, {})".format(pxs[i], pys[i], pzs[i])
	
	pair = False
	
	if leading:
		jet_candidates = []
		for j in jets:
			if (j.pt >= cut_pt) and (abs(j.eta) <= cut_eta) and (j.jetid):
				jet_candidates.append(j)
		if len(jet_candidates) >= 2:
			pair = (jet_candidates[0], jet_candidates[1])
	else:
		# Apply cuts:
		jets = [j for j in jets if (j.pt >= cut_pt) and (abs(j.eta) <= cut_eta)]
	
		# Select jet pair:
	#	pairs = sorted([pair for pair in [p for p in combinations(jets, 2) if any(j.m >= cut_m for j in p)]], key=physics.delta_m)
		pairs = sorted([pair for pair in [p for p in combinations(jets, 2) if mean([j.m for j in p]) >= cut_m]], key=physics.delta_m)
		if v: print "There were {} jet(s) left after applying the pT cut of {} GeV. This resulted in {} viable pair(s) after the m cut of {} GeV.".format(len(jets), cut_pt, len(pairs), cut_m)
		if pairs:
			pair = pairs[0]
	
	
	# Add groomed variables to pair:
	if pf and pair:
		for groomer in ["f", "p", "s", "t"]:
			prefix = "{}_pf{}".format(alg, groomer)
			for j in pair:
				setattr(j, "px_" + groomer, getattr(event, prefix + "_px")[j.i]*j.jec)
				setattr(j, "py_" + groomer, getattr(event, prefix + "_py")[j.i]*j.jec)
				setattr(j, "pz_" + groomer, getattr(event, prefix + "_pz")[j.i]*j.jec)
				setattr(j, "pt_" + groomer, getattr(event, prefix + "_pt")[j.i]*j.jec)
				setattr(j, "e_" + groomer, getattr(event, prefix + "_e")[j.i]*j.jec)
				setattr(j, "m_" + groomer, getattr(event, prefix + "_m")[j.i]*j.jmc)
				setattr(j, "eta_" + groomer, getattr(event, prefix + "_eta")[j.i])
				setattr(j, "phi_" + groomer, getattr(event, prefix + "_phi")[j.i])
				setattr(j, "tau1_" + groomer, getattr(event, prefix + "_tau1")[j.i])
				setattr(j, "tau2_" + groomer, getattr(event, prefix + "_tau2")[j.i])
				setattr(j, "tau3_" + groomer, getattr(event, prefix + "_tau3")[j.i])
				setattr(j, "tau4_" + groomer, getattr(event, prefix + "_tau4")[j.i])
	
	# Return:
	return pair
# /FUNCTIONS
