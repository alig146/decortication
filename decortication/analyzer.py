####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, sys
from ROOT import gROOT, gStyle, TCanvas, TFile, TChain, TTree, SetOwnership
#from ROOT import *
from array import array		# Necessary for creating branches
from time import time
import random
import numpy
import inspect
from truculence import utilities, root, cmssw
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
		tt_names=["tuplizer/events"],   # The names of the input TTrees
		count=None,
		use_condor=False,
	):
		# Basic configuration:
		gROOT.SetBatch()                # Prevent ROOT canvas windows from opening
		
		# Arguments and variables:
		self.name = inspect.stack()[1][1][:-3] if name == None else name		# This makes the name attribute be the script name if it's not already called something.
		self.time_string = utilities.time_string()[:-4]		# A time string indicating when the analyzer was created
		self.save = save
		self.count = count
		self.condor = use_condor
		self.out_file = out_file
		self.out_dir = out_dir
		self.tuples_in = tuples        # This is useful debugging.
		self.tuples = {}
		self.tt_names = tt_names
		
		# Organize input:
		if isinstance(tuples, str):
			tuples = [tuples]
		if isinstance(tuples, list):
			if all(isinstance(tup, str) for tup in tuples):
				self.tuples = {self.name: tuples}
			elif all(isinstance(tup, dataset.dataset) for tup in tuples):
				for tup in tuples:
					if tup.process not in self.tuples: self.tuples[tup.process] = []
					self.tuples[tup.process].append(tup)
			else:
				print "ERROR (analyzer): unrecognized input:"
				print self.tuples_in
				sys.exit()
		elif isinstance(tuples, dict):
			self.tuples = tuples
		else:
			print "ERROR (analyzer): \"tuples\" should be a string, list, or dictionary."
			print "tuples = {}".format(tuples)
			sys.exit()
		
		# Calculate event number if necessary:
		if self.count == None:
			if any([isinstance(tup, str) for tup in utilities.flatten_list([thing for thing in self.tuples.values()])]): self.count = True
			else: self.count = False
		
		## Create TChains:
		if v: print "Making TChain(s) ..."
		self.tt_in = {}
		self.tt_info = {}
		self.tc = TCanvas("tc_{}".format(name), "tc_{}".format(name), 500, 500)
		SetOwnership(self.tc, 0)
		samples = self.tuples.keys()
		for sample, tups in self.tuples.items():
			ns = []
			
			# Handle different input schemes (either list of tuples or list of file names):
			food = 2 if isinstance(tups[0], dataset.dataset) else 1
			if food == 2:
				# A bit KLUDGY:
				fs = []
				for tup in tups:
					fs += [f if not tup.dir.eos else "root://cmsxrootd.fnal.gov/" + f for f in tup.files]
					ns += tup.ns
				tups = fs
			if v: print "\tMaking TChain(s) for {} ...".format(sample)
#			self.tt_in[sample] = []
			if not self.tt_names: tt_names = [sample]
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
					print "ERROR (analyzer.__init__): The tuples configuration is weird:\n{}".format(self.tuples)
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
#		SetOwnership(gROOT, 0)
		
		# Organize output:
		if save:
			# Set attributes to defaults if they aren't set:
			## Output directory:
			if not out_dir and not self.condor: self.out_dir = "results/{}_{}".format(self.name, self.time_string)
			elif self.condor: self.out_dir = "."
			
			if not os.path.exists(self.out_dir): os.makedirs(self.out_dir)
			## Output file:
			if not out_file and not self.condor: self.out_file = "{}_{}.root".format(self.name, self.time_string)
			if self.condor: self.out_file = "job_{}.root".format(self.condor)
			
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
		variables,               # A list of variable dictionaries
	):
		branches = {}
		for sample in self.tt_out.keys():
			branches[sample] = {}
			for var in variables:
				name = var["name"]
				dim = var["dimension"]
				branches[sample][name] = array('d', [-1]*dim)		# If you change the "d" here, you need to change it two lines below!
				tt = self.tt_out[sample]
				tt.Branch(name, branches[sample][name], '{}[{}]/D'.format(name, dim))
			
		self.branches = branches
		self.variables = variables
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
	
	def Print(self):
	# Print useful information about the analyzer.
		print "\nAnalyzer information:"
		print "{} (decortication/analyzer)".format(self.name)
		print "input (original):"
		print "\t{}".format(self.tuples_in)
		print "input (formatted):"
		print "\t{}".format(self.tuples)
		print "\n"
	
	def get_files(self, info=False):
		files = []
		for key, tuples in self.tuples.items():
			for tup in tuples:
				if info:
					if isinstance(tup, dataset.dataset): files.extend([{"file": f, "process": key} for f in tup.files])
					elif isinstance(tup, str): files.append({"file": tup, "process": key})
				else:
					if isinstance(tup, dataset.dataset): files.extend(tup.files)
					elif isinstance(tup, str): files.append(tup)
		
#		return list(set(files))		# You can't do this with a list of dicts.
		return files
	
	def create_jobs(self, cmd="", memory=2000, input_files=None):
	# Create condor jobs for each input file.
#		if not cmd:
#			print "ERROR (analyzer.create_jobs): You need to specify a cmd to run for each job."
#			return False
		
		# Define variables:
		Site = dataset.Site
		data_dir = Site.get_dir("data")
		cmssw_version = cmssw.get_version(parsed=False)
		if not cmd: cmd = "python {}.py -f %%FILE%% -o job_%%N%%.root".format(self.name)
		tstring = utilities.time_string()[:-4]
		path = "condor_jobs/{}/{}".format(self.name, tstring)
		log_path = path + "/logs"
#		out_path = path + "/results"
		out_path = os.path.join(data_dir.path, "analyzer_jobs", tstring)		# Output path.
		files_for_condor = ["{}/{}.py".format(os.getcwd(), self.name), "{}.tar.gz".format(cmssw_version)]
		if isinstance(input_files, str): input_files = [input_files]
		if input_files: input_files = [os.getcwd() + "/" + f for f in input_files if "/" not in f]
		if input_files: files_for_condor.extend(input_files)
		
		# Make directories
		for p in [path, log_path]:
			if not os.path.exists(p): os.makedirs(p)
		
		# Make job files:
		files = self.get_files(info=True)
		## Make job scripts:
		for i, f_dict in enumerate(files):
			f = f_dict["file"]
			if f[:12] == "/store/user/": f = "root://cmseos.fnal.gov/" + f
			job_name = "analyzer_job{}_{}".format(i + 1, tstring)
			job_script = "#!/bin/bash\n"
			job_script += "\n"
			job_script += "# Untar CMSSW area:\n"
			job_script += "tar -xzf {}.tar.gz &&\n".format(cmssw_version)
			for input_file in input_files:
				input_file = input_file.split("/")[-1]
				if "CMSSW_" not in f: job_script += "cp {} {}/src/Analyzers/FatjetAnalyzer/test\n".format(input_file, cmssw_version)
			job_script += "cd {}/src/Analyzers/FatjetAnalyzer/test\n".format(cmssw_version)
			job_script += "\n"
			job_script += "# Setup CMSSW:\n"
			job_script += "source /cvmfs/cms.cern.ch/cmsset_default.sh\n"
			job_script += "scramv1 b ProjectRename\n"
			job_script += "eval `scramv1 runtime -sh`		#cmsenv\n"
			job_script += "\n"
			job_script += cmd.replace("%%FILE%%", f).replace("%%PROCESS%%", f_dict["process"]).replace("%%N%%", str(i + 1)) + "\n"
			if data_dir.eos: job_script += "xrdcp -f job_{}.root root://{}/{}\n".format(i+1, Site.url_eos, out_path)
			else: job_script += "mv -f job_{}.root {}\n".format(i+1, Site.url_eos, out_path)
			with open("{}/{}.sh".format(path, job_name), "w") as out:
				out.write(job_script)
	
		## Make condor configs:
		for i in range(len(files)):
			job_name = "analyzer_job{}_{}".format(i + 1, tstring)
			job_config = "universe = vanilla\n"
			job_config += "Executable = {}.sh\n".format(job_name)
			job_config += "Should_Transfer_Files = YES\n"
			job_config += "WhenToTransferOutput = ON_EXIT\n"
			job_config += "Transfer_Input_Files = {}\n".format(",".join(files_for_condor))
#			job_config += "Output_Destination = results\n"
#			job_config += "Transfer_Output_Files = job_{}.root\n".format(i+1)
			job_config += "Transfer_Output_Files = \"\"\n"
			job_config += "Output = logs/{}.stdout\n".format(job_name)
			job_config += "Error = logs/{}.stderr\n".format(job_name)
			job_config += "Log = logs/{}.log\n".format(job_name)
			job_config += "notify_user = ${LOGNAME}@FNAL.GOV\n"
			if Site.name == "hexcms": job_config += "x509userproxy = $ENV(HOME)/myproxy\n"
			else: job_config += "x509userproxy = $ENV(X509_USER_PROXY)\n"
			job_config += "request_memory = {}\n".format(memory)
			job_config += "Queue 1\n"
		
			with open("{}/{}.jdl".format(path, job_name), "w") as out:
				out.write(job_config)
	
		## Make run script:
		run_script = "#!/bin/bash\n"
		run_script += "\n"
		run_script += "# Grid proxy existence & expiration check:\n"
		run_script += "PCHECK=`voms-proxy-info -timeleft`\n"
		run_script += "if [[ ($? -ne 0) || (\"$PCHECK\" -eq 0) ]]; then\n"
		run_script += "\tvoms-proxy-init -voms cms --valid 168:00\n"
		run_script += "fi\n"
		run_script += "\n"
		run_script += "# Make tarball:\n"
		run_script += "echo 'Making a tarball of the CMSSW area ...'\n"
		run_script += "tar --exclude-caches-all -zcf ${CMSSW_VERSION}.tar.gz -C ${CMSSW_BASE}/.. ${CMSSW_VERSION}\n"
		run_script += "\n"
		run_script += "# Prepare output directory:\n"
		if data_dir.eos: run_script += "eos root://{} mkdir -p {}\n".format(Site.url_eos, out_path)
		else: run_script += "mkdir -p {}\n".format(out_path)
		run_script += "\n"
		run_script += "# Submit condor jobs:\n"
		for i in range(len(files)):
			job_name = "analyzer_job{}_{}".format(i + 1, tstring)
			run_script += "condor_submit {}.jdl\n".format(job_name)
		
		with open("{}/run.sh".format(path), "w") as out:
			out.write(run_script)
	
		print "The jobs are in {}".format(path)
		
		return path


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
		if not self.n:
			print "[!!] The TChain you want to run over has no events."
			sys.exit()
		if v: print "\tThere are {} events.".format(self.n)
	
	def run(self,
		n=None,                 # The number of events to run over ("-1" means "all")
		arguments=None,
		rand=False, v=True,
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
