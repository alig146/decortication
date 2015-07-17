from truculence import *
import samples
import math

def make_th1():
	info = {}

def make_th2(ntuple, max_events=-1):
	# Construct TH2s:
	info = {}
	for collection in samples.collections:
		# Set up single FJ plots:
		info["eta_phi_{0}".format(collection)] = ["FJ Phi Versus Eta", "#eta (GeV)", "#phi (GeV)"]
		info["pt_m_{0}".format(collection)] = ["FJ Mass Versus Pt", "p_{T} (GeV)", "m (GeV)"]
		info["eta_pt_{0}".format(collection)] = ["FJ Pt Versus Eta", "#eta (GeV)", "p_{T} (GeV)"]
		info["phi_pt_{0}".format(collection)] = ["FJ Pt Versus Phi", "#phi (GeV)", "p_{T} (GeV)"]
		
		# Set up di-FJ plots:
		info["m0_m1_{0}".format(collection)] = ["FJ Mass", "m^{0} (GeV)", "m^{1} (GeV)", 25, 0, 700, 25, 0, 700]
		info["pt0_pt1_{0}".format(collection)] = ["FJ Pt", "p_{T}^{0} (GeV)", "p_{T}^{1} (GeV)", 25, 0, 700, 25, 0, 700]
		info["pt0_m0_{0}".format(collection)] = ["FJ Mass And Pt", "p_{T}^{0} (GeV)", "m^{0} (GeV)", 25, 0, 700, 25, 0, 700]
		info["pt1_m1_{0}".format(collection)] = ["FJ Mass And Pt", "p_{T}^{1} (GeV)", "m^{1} (GeV)", 25, 0, 700, 25, 0, 700]
		info["m_dm_{0}".format(collection)] = ["FJ #Delta m Versus #bar{m}", "#bar{m} (GeV)", "#Delta m (GeV)", 50, 0, 500, 100, 0, 700]
		info["logm_dm_{0}".format(collection)] = ["FJ #Delta m Versus #bar{m}", "Log(#bar{m})", "#Delta m (GeV)", 50, 0, 500, 70, 2.3, 6.6]
	th2 = analysis.setup_th2(info)
	
	# Fill TH2s:
	if max_events > 0:
		n_events = max_events
	else:
		n_events = ntuple.GetEntries()
	n = -1
	for event in ntuple:		# Loop over the ntuple.
		n += 1
		if n < max_events:
			percent = n/float(n_events) * 100
			if percent % 10 == 0:
				print "{0}%".format(int(percent))
			for collection in samples.collections:
				# Define variables:
				try:		# The variable might not be in the event ...
					# Kinematics:
					pt0 = getattr(event, "{0}_pt".format(collection))[0]
					pt1 = getattr(event, "{0}_pt".format(collection))[1]
					m0 = getattr(event, "{0}_m".format(collection))[0]
					m1 = getattr(event, "{0}_m".format(collection))[1]
					m = (m0 + m1) / 2
					dm = abs(m0 - m1)
					eta0 = getattr(event, "{0}_eta".format(collection))[0]
					eta1 = getattr(event, "{0}_eta".format(collection))[1]
					phi0 = getattr(event, "{0}_phi".format(collection))[0]
					phi1 = getattr(event, "{0}_phi".format(collection))[1]
					dR = ((eta0 - eta1)**2 + (phi0 - phi1)**2)**(0.5)
					
					# Weighting:
					sigma = getattr(event, "{0}_sigma".format(collection))[0]
#					nnorm = getattr(event, "{0}_nevents".format(collection))[0]
#					L = 10000		# The target luminosity in pb-1.
#					w = (sigma/nnorm)*L		# Calculate the event weight.
					w = 1
				except Exception as ex:
					print ex
					pass
				else:
					# Fill histograms:
					## Fill single FJ plots:
					th2["eta_phi_{0}".format(collection)].Fill(eta0, phi0, w)
					th2["eta_phi_{0}".format(collection)].Fill(eta1, phi1, w)
					th2["pt_m_{0}".format(collection)].Fill(pt0, m0, w)
					th2["pt_m_{0}".format(collection)].Fill(pt1, m1, w)
					th2["eta_pt_{0}".format(collection)].Fill(eta0, pt0, w)
					th2["eta_pt_{0}".format(collection)].Fill(eta1, pt1, w)
					th2["phi_pt_{0}".format(collection)].Fill(phi0, pt0, w)
					th2["phi_pt_{0}".format(collection)].Fill(phi1, pt1, w)
					## Fill di-FJ plots:
					th2["m0_m1_{0}".format(collection)].Fill(m0, m1, w)
					th2["pt0_pt1_{0}".format(collection)].Fill(pt0, pt1, w)
					th2["pt0_m0_{0}".format(collection)].Fill(pt0, m0, w)
					th2["pt1_m1_{0}".format(collection)].Fill(pt1, m1, w)
					th2["m_dm_{0}".format(collection)].Fill(m, dm, w)
					th2["logm_dm_{0}".format(collection)].Fill(math.log(m), dm, w)
		else:
			break
	return th2
