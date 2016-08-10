####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, sys
from ROOT import *
from array import array		# Necessary for creating branches
from time import time
import random
import numpy
import inspect
from truculence import utilities, root
from decortication import dataset
#from truculence import *
# /IMPORTS

# VARIABLES:

# /VARIABLES

# CLASSES:
class analyzer:
	def __init__(self,
		tuples,                         # A list or dictionary of input file paths.
		name=None,
		out_dir=None,                   # The directory where the output should go.
		out_file=None,                  # The name of the output file (including ".root")
		save=True,
		v=False,
		tt_names=["analyzer/events"],   # The names of the input TTrees
		count=True,
	):
		# Arguments and variables:
		self.name = inspect.stack()[1][1][:-3] if name == None else name		# This makes the name attribute be the script name if it's not already called something.
		self.time_string = utilities.time_string()[:-4]		# A time string indicating when the analyzer was created
		self.save = save
		self.count = count
		
		# Organize input:
		if isinstance(tuples, dict):
			self.tuples_in = tuples		# This is for potential debugging.
		elif isinstance(tuples, str) or isinstance(tuples, list):
			if isinstance(tuples, str):
				tuples = [tuples]
			if isinstance(tuples, list):
				if isinstance(tuples[0], str):
					tuples = {self.name: tuples}
				else:
					tuples = {self.Name: tuples}
		else:
			print "ERROR (analyzer): \"tuples\" should be a string, list, or dictionary."
		
		# Determine if tuples are raw (file locations) or dataset instances:
		
		if v: print "Making TChain(s) ..."
		self.tt_in = {}
		self.tt_info = {}
		self.tc = TCanvas("tc_{}".format(name), "tc_{}".format(name), 500, 500)
		SetOwnership(self.tc, 0)
		samples = tuples.keys()
		for sample, tups in tuples.iteritems():
			ns = []
			
			# Handle different input schemes (either list of tuples or list of file names):
			food = 2 if isinstance(tups[0], dataset.dataset) else 1
			if food == 2:
				# A bit KLUDGY:
				fs = []
				for tup in tups:
					fs += [f if "root://cmsxrootd.fnal.gov/" in f else "root://cmsxrootd.fnal.gov/" + f for f in tup.files]
					ns += tup.ns
				tups = fs
			if v: print "\tMaking TChain(s) for {} ...".format(sample)
#			self.tt_in[sample] = []
			for tt_name in tt_names:
				if v: print "\t\tTChain named {}:".format(tt_name)
				tt = TChain(tt_name)
				for tup in tups:
					tt.Add(tup)
					if v: print "\t\t+ {}".format(tup)
				SetOwnership(tt, 0)
				if (len(tt_names) > 1) and (len(samples) > 1):
					key = "_".join([sample, tt_name])
				elif (len(tt_names) > 1) and (len(samples) == 1):
					key = tt_name
				elif len(tt_names) == 1:
					key = sample
				else:
					print "ERROR (analyzer.__init__): The tuples configuration is weird:\n{}".format(tuples)
					sys.exit()
				self.tt_in[key] = tt
				info = {
					"ns": ns
				}
				self.tt_info[key] = info
#				self.tc[key] = TCanvas("tc_{}".format(key), "tc_{}".format(key), 500, 500)
#				SetOwnership(self.tc[key], 0)
		
		# ROOT setup:
#		if v: print "\tSetting up ROOT ..."
		gROOT.SetStyle("Plain")
		gStyle.SetTitleBorderSize(0)
		gStyle.SetPalette(1)
		gROOT.SetBatch()                 # Prevent canvas windows from opening
#		SetOwnership(gROOT, 0)
		
		# Organize output:
		if save:
			# Set attributes to defaults if they aren't set:
			## Output directory:
			if not out_dir:
				self.out_dir = "results/{}_{}".format(self.name, self.time_string)
			if not os.path.exists(self.out_dir):
				os.makedirs(self.out_dir)
			## Output file:
			if not out_file:
				self.out_file = "{}_{}.root".format(self.name, self.time_string)
			
			# Define new attributes:
			self.out_path = self.out_dir + "/" + self.out_file
			## ROOT output:
			self.out = TFile(self.out_path, "RECREATE")
			SetOwnership(self.out, 0)
			### Tuple output:
			self.tt_out = {}
			for key, tt in self.tt_in.iteritems():
				self.tt_out[key] = TTree(key, 'anatuple')
				SetOwnership(self.tt_out[key], 0)
			### Histograms:
			self.plots = []
		
		# Event loops
		self.loops = {}
		for key, tt in self.tt_in.iteritems():
			self.loops[key] = event_loop(self, key)
	
	def define_branches(self,
		variables,               # A dictionary keyed by the outputbranch names and valued by the dimension
	):
		branches = {}
		for sample in self.tt_out.keys():
			branches[sample] = {}
			for var, dim in variables.iteritems():
				branches[sample][var] = array('f', [-1]*dim)
				tt = self.tt_out[sample]
				tt.Branch(var, branches[sample][var], '{}[{}]/F'.format(var, dim))
			
		self.branches = branches
		return branches
	
	def write(self, Print=False):
		if hasattr(self, "out"):
			for plot in self.plots:
				self.out.WriteTObject(plot)
				if Print:
					self.tc.cd()
					plot.Draw()
					if not os.path.exists(self.out_dir + "/plots"):
						os.makedirs(self.out_dir + "/plots")
					self.tc.SaveAs("{}/plots/{}.pdf".format(self.out_dir, plot.GetName()))
			for tt in self.tt_out.values():
				self.out.WriteTObject(tt)
#				print tt.GetName(), len(tt.GetListOfBranches())
			self.out.Close()

class event_loop:
	def __init__(self,
		ana,                # The analyzer it's in
		key,                # Key used to identify the loop
		n_default=-1,               # The default number of events to run over (use "-1" for "all") (see "run" to see why)
		progress=True,              # Turn on progress bar.
	):
		self.ana = ana
		self.key = key
		self.n_default = n_default
		self.ns = self.ana.tt_info[self.key]["ns"]
		self.n = sum(self.ns)
		self.n_run = 0		# The number of events to loop over in the current "run".
#		self.rand = True               # True: select the events randomly, False: select events from the beginning
#		self.v = True                  # Verbose mode
		tt_in = ana.tt_in[key]
		self.progress = progress
		# Apply cuts:
		if hasattr(self.ana, "cut"):
			gROOT.cd()
			tt_in = tt_in.CopyTree(self.ana.cut)
		self.tt_in = tt_in
		self.tt_out = None
		if ana.save:
			self.tt_out = ana.tt_out[key]
	
	def update(self, v=True):
		# Update branches:
		if hasattr(self.ana, "branches"):
			self.branches = self.ana.branches[self.key]
		else:
			self.branches = False
		
		# Apply cuts:
		if hasattr(self.ana, "cut"):
			gROOT.cd()
			self.tt_in = self.tt_in.CopyTree(self.ana.cut)
		
		if v: print "Fetching the number of events in {} ...".format(self.key)
#		self.n_total = self.tt_in.GetEntries()                      # The total number of events in the input dataset
		if self.ana.count:
			self.ns = root.tc_nevents(self.tt_in)             # The total number of events in each file of the input TChain
			self.n = sum(self.ns)
		else:
			if not self.ns:
				print "This isn't implemented, yet!"
				print "I have to use the key to look in the DB for tuple nevents"
				sys.exit()
#				samples = dataset.fetch_samples(process=self.key)
#				tuples = []
#				for sample in samples:
#					tuples.extend([tup for tup in sample.tuples if tup.generation == "spring15" and tup.suffix == "pt400"])
#				self.n_total_list = [N for tup in tuples for N in tup.ns]
		if v: print "\tThere are {} events.".format(self.n)
	
	def run(self,
		n=None,                 # The number of events to run over ("-1" means "all")
		arguments=None,
		rand=True, v=True,
		variables=[
			"ak4_pf_pt", "ak4_pf_sigma", "ak4_pf_nevents", "ak4_gn_pt_hat",
			"ca12_pf_px", "ca12_pf_py", "ca12_pf_pz", "ca12_pf_e", "ca12_pf_pt", "ca12_pf_M", "ca12_pf_m", "ca12_pf_eta", "ca12_pf_phi","ca12_pf_tau1", "ca12_pf_tau2","ca12_pf_tau3", "ca12_pf_tau4", "ca12_pf_ht", "ak8_pf_ht"
		],
	):
		t0 = time()
		self.update(v=v)
		
		# Parse n:
		if n == None:
			n = self.n_default
		if n == -1:
			n = self.n
		self.n_run = n
		
		n_events_tt = self.n
		if v: print "Processing the {} event loop ...\n\tOf the {} total events, I'm processing {} ({:.1f} %).".format(self.key, n_events_tt, n, (100*float(n)/n_events_tt, 100)[n == self.n])
		
		# Two loop designs: (1) fewer than all events with rand on, (2) all events or rand off:
		# (1):		THIS IS BROKEN!
		if n != self.n and rand:
			# Pick events:
			ns_event = sorted(random.sample(range(n_events_tt), n))		# Pick n random events, sort them for speed.
			self.ns = ns_event
			
			# Event loop:
			for i_event, n_event in enumerate(ns_event):
				# Prepare event info:
				n_event_file = self.tt_in.LoadTree(n_event)
				branches = [self.tt_in.GetBranch(v) for v in variables]
				branches = [b for b in branches if b]		# Exclude any branches that don't exist: like pt_hat for a signal.
				for i_var, branch in enumerate(branches):
					branch.GetEntry(n_event_file)
			
				# Deal with event:
				self.treatment(self, self.tt_in)
			
				# Display progress:
				if self.progress:
					utilities.progress(i_event, len(ns_event), text="Event {}".format(n_event))
		
		# (2):
		else:
			# Event loop:
			for i_event, event in enumerate(self.tt_in):
				# Allow for fewer than max events:
				if i_event >= n:
					break
			
				# Prepare event info:
				i_event_file = self.tt_in.LoadTree(i_event)
			
				# Deal with event:
				self.treatment(self, self.tt_in, arguments)
			
				# Display progress:
				if self.progress:
					utilities.progress(i_event, n, text="Event {}".format(i_event))
	
		# Print some info:
		time_total = time() - t0
		if v: print "\ttime = {:.02f} s, n_events = {}, rand = {}".format(time_total, n, rand)
	
		# Return some info:
		result = {}
		result["time"] = time_total
		return result
	
	def treatment(self, event):		# The function that the event loop runs on each event
		return True
# /CLASSES

# FUNCTIONS:
#def event_loop(
#	tt,                     # The TTree (TChain) to run over
#	branches_out,           # ?
#	tt_out,                 # ?
#	n_events=100,           # The number of events to run over
#	variables=variables,    #
#	rand=True,              # True: select the events randomly, False: select events from the beginning
#	v=True                  # Verbose mode
#):
#	t0 = time()
#	n_events_tt = tt.GetEntries()
#	if v: print "Processing {} loop ...\n\tOf the {} total events, I'm processing {:.1f} %.".format(name, n_events_tt, (100*float(n_events)/n_events_tt, 100)[n_events == -1])
#	
#	# Two loop designs: (1) fewer than all events with rand on, (2) all events or rand off:
#	# (1):
#	if n_events != -1 and rand:
#		# Pick events:
#		ns_event = sorted(random.sample(range(n_events_tt), n_events))		# Pick n_events random events, sort them for speed.
#		
#		# Event loop:
#		for i_event, n_event in enumerate(ns_event):
#			# Prepare event info:
#			n_event_file = tt.LoadTree(n_event)
#			branches = [tt.GetBranch(v) for v in variables]
#			branches = [b for b in branches if b]		# Exclude any branches that don't exist: like pt_hat for a signal.
#			for i_var, branch in enumerate(branches):
#				branch.GetEntry(n_event_file)
#			
#			# Deal with event:
##			print "before treat"
#			treat_event(tt, n_events, branches_out, tt_out, n_event=n_event)
##			print "after treat"
#			
#			# Display progress:
#			utilities.progress(i_event, len(ns_event), text="Event {}".format(n_event))
#		
#	# (2):
#	else:
#		if n_events == -1:
#			n_events = n_events_tt
#		
#		# Event loop:
#		for i_event, event in enumerate(tt):
#			# Allow for fewer than max events:
#			if i_event >= n_events:
#				break
#			
#			# Prepare event info:
#			i_event_file = tt.LoadTree(i_event)
#			
#			# Deal with event:
#			treat_event(event, n_events, branches_out, tt_out, n_event=i_event)
#			
#			# Display progress:
#			utilities.progress(i_event, n_events, text="Event {}".format(i_event))
#	
#	# Print some info:
#	time_total = time() - t0
#	if v: print "\ttime = {:.02f} s, n_events = {}, rand = {}".format(time_total, n_events, rand)
#	
#	# Return some info:
#	result = {}
#	result["time"] = time_total
#	return result
# /FUNCTIONS
