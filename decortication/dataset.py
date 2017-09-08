####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os, yaml, json, re, sys, copy
from collections import OrderedDict
from time import time
import sqlite3
from subprocess import Popen, PIPE
from truculence import das, crab, lhe, utilities
import decortication
from decortication import eos, variables, infrastructure, site
# /IMPORTS

# VARIABLES
Site = site.get_site()
dir_data = Site.get_dir("data")

username = "tote"
data_dir = "/store/user/" + username
lhe_dir = "/uscms_data/d3/{}/lhe".format(username)
tuple_dir = data_dir + "/data/fat"
signal_processes = ["sqto4j", "sqto2j"]
info_path_default = infrastructure.get_res_path("samples.yaml")
# os.path.join(os.path.realpath(decortication.__path__[0]), "..", "resources/samples.yaml")
db_keys_path_default = infrastructure.get_res_path("database.yaml")
db_path_default = infrastructure.get_res_path("samples.db")
json_dir_default = "resources/json"
luminosity_default = 10000

## Information for DB tables:
keys_db = {}
#KLUDGE for compatibility:
with open(db_keys_path_default, 'r') as f:
	db_info = utilities.ordered_load(f)
	for kind, info in db_info.items():
		keys_db[kind] = OrderedDict()
		for key, meta_dict in info.items():
			if "primary" not in meta_dict:
				meta_dict["primary"] = False
			keys_db[kind][key] = (meta_dict["type"], meta_dict["primary"])

primary_keys_master = {kind: [key for key, values in key_dict.items() if values[1]] for kind, key_dict in keys_db.items()}

database_info = infrastructure.get_db_info()

# /VARIABLES

# CLASSES:
class dataset:
	def __init__(self, kind, info=None, category=None, process=None, subprocess=None, generation=None, suffix=None, isolated=False):
		if not info:
			info = {}
		self.info = info
		# "kind", "primary_key_list":
		self.kind = kind
		if kind in keys_db:
			self.primary_key_list = [key for key, values in database_info[kind].items() if values["primary"]]
		else:
			"WARNING (dataset.dataset): The '{}' kind is not recognized.".format(kind)
			self.primary_key_list = []
		
		# Add variables to "info":
		for primary_key in self.primary_key_list:
			if primary_key not in info:
				if locals()[primary_key]:
					info[primary_key] = locals()[primary_key]
				else:
					print "WARNING (dataset.dataset.init): The dataset object you wanted to make needs to have the following primary keys: {}".format(self.primary_key_list)
					info[primary_key] = None
		
		# Get "db_info":
		self.primary_keys = OrderedDict()
		for key in self.primary_key_list:
			self.primary_keys[key] = info[key]
		db_info = fetch_info(primary_keys=self.primary_keys, kind=self.kind)
#		print self.primary_keys
		
		# Compare "info" with "db_info" to construct "info_final":
		info_final = {}
#		if self.kind == "miniaod": print info["das"], db_info["das"]
		for key in keys_db[self.kind].keys():
			if key in info:                        # Replace any "db_info" fields that are in "info".
				info_final[key] = info[key]
			elif key in db_info:
				info_final[key] = db_info[key]
			else:
				info_final[key] = None
#		print info_final
		# Set attributes from "info_final":
		for key, value in info_final.items():
			setattr(self, key, value)
		
		# Fill "calculable" attributes:
		## "Name":
		self.Name = "_".join(self.primary_keys.values())
		self.Name_safe = self.Name.replace("-", "")
		## "dir":		// Kludge
		if self.kind == "sample": self.path = self.name
#		else: self.path = self.get_sample().path + "/" + self.path
		## "json" and "json_full":
		if not self.json:
			self.json = "{}/{}.json".format(json_dir_default, self.Name)
		self.json_full = os.path.join(decortication.__path__[0], "..", self.json)
		## "ns", "files":
		if self.kind != "sample" and os.path.exists(self.json_full):
			set_ns(self, j=True)
			set_files(self, j=True)
#		## "n":
#		if not self.n and hasattr(self, "ns"):
#			self.n = sum(self.ns)
		## "lhe_file":
		if hasattr(self, "lhe_path"):
			if self.lhe_path:
				self.lhe_file = self.lhe_path.split("/")[-1]
		
		self.site = Site
#		self.dir = site.directory({"path": self.path, "eos": self.site.get_dir("data").eos})
		if self.path:
			self.dir = copy.copy(self.site.get_dir("data"))
			self.dir.cd(self.path)
#		# Connect to any children:
#		if not isolated:
#			self.set_connections(down=True, up=False)
		
		# Kludge: this needs to be governed by infrastructure:
		if self.kind == "tuple":
			self.das = False
			self.instance = "global"
		
		# Aliases:
		self.sp = self.subprocess
	# :init
	
	
	def __str__(self):
		return "<{} instance named {}>".format(self.kind, self.Name)
	
	def __repr__(self):
		return "<{} instance named {}>".format(self.kind, self.Name)
	
	
	def Print(self):
		# Basic stuff:
		print "{} object".format(self.kind.capitalize())
		print "\t* Identifiers:"
		for var in variables.identifiers.keys():
			if hasattr(self, var):
				print "\t\t* {}: {}".format(var, getattr(self, var))
		if hasattr(self, "name"): print "\t* name = {}".format(self.name)
		print "\t* data: {}".format(bool(self.data))
		if self.time: print "\t* Last updated on {}".format(utilities.time_to_string(self.time))
		else: print "\t* UNSCANNED"
		# Path and files:
		if hasattr(self, "das"):
			print "\t* path: {} (das = {}, instance = {})".format(self.path, self.das, self.instance)
		else:
			print "\t* path: {}".format(self.path)
		if hasattr(self, "files"):
			print "\t\t* {} files".format(len(self.files))
			print "\t\t* example file: {}".format(self.files[0])
		if hasattr(self, "mask"):
			print "\t* mask: {}".format(self.mask)
		# Parameters:
		if hasattr(self, "sigma"):
			print "\t* sigma = {}".format(self.sigma)
		if hasattr(self, "luminosity"):
			print "\t* luminosity = {}".format(self.luminosity)
		if hasattr(self, "n"):
			print "\t* n = {}".format(self.n)
			print "\t* preweight = {}".format(self.preweight)
			print "\t* weight = {}".format(self.weight)
		# LHE:
		if hasattr(self, "lhe_file"):
			print "\t* LHE information:"
			print "\t\t* File: {}".format(self.lhe_file)
			print "\t\t* Cut: {}".format(self.lhe_cut)
			print "\t\t* Events: {}".format(self.lhe_n)
		print
	
	def get_sample(self):
		return fetch_sample(self.subprocess)
	
	def get_parent(self):
		kind = infrastructure.get_kind(self.kind)
		parent_kind = kind.get_parent()
		return fetch_entry(parent_kind.name, {key: getattr(self, key) for key in parent_kind.get_primary_keys()})
	
	def set_lhe_n(self):
		if not self.kind == "miniaod":
			return False
		else:
			lhe_info = lhe.get_info(self.lhe_path)
			if lhe_info: return lhe_info["nevents"]
			else: False
	
	
	
	
	
	def set_connections(self, down=True, up=False):
		good = True
		kinds = []
		if down:        # Add children kinds.
			kinds.extend([(kind, "child") for kind, keys in primary_keys_master.items() if set(self.primary_keys.keys()) < set(keys)])
		if up:          # Add parent kinds.
			kinds.extend([(kind, "parent") for kind, keys in primary_keys_master.items() if set(self.primary_keys.keys()) > set(keys)])
		
		for kind, age in kinds:
			query = {key: value for key, value in self.primary_keys.items() if key in primary_keys_master[kind]}
			entries = fetch_entries(kind, query, isolated=True)
			for entry in entries:
				setattr(entry, "".format(self.kind), self)
				setattr(entry, "{}".format(self.kind), self)
			if age == "child":
				setattr(self, "{}s".format(kind), entries)
			elif age == "parent":
				if len(entries) == 1:
					setattr(self, "{}".format(kind), entries[0])
				elif len(entries) > 1:
					print "ERROR (dataset.set_connections): {} had multiple parents of the same kind ({})".format(self.Name, kind)
					good = False
				else:
					print "WARNING (dataset.set_connections): {} had no {} parent.".format(self.Name, kind)
					good = False
		return good
	
	def set_files(self, j=True, v=False):
		files = []
		if j:
			if os.path.exists(self.json_full):
				with open(self.json_full) as infile: files = json.load(infile)["files"]
		if not files:
			if self.path and not self.das:
	#			if os.path.exists(self.path):		# I CAN'T DO THIS BECAUSE OF EOS!
				files = self.dir.ls()
			if not files and self.das:		# Check DAS
				print "Checking DAS for file list of {} ...".format(self.Name)
				result = das.get_info(self.name, instance=self.instance)
	#			print result["raw"]
				files = result["files"]
		self.files = files
		return files
		
	def set_ns(self, j=True):
		ns = []
		if j:
			if os.path.exists(self.json_full):
				with open(self.json_full) as infile: ns = json.load(infile)["ns"]
		if not ns:
			if not ns and not self.das:
	#			if os.path.exists(self.path):		# I CAN'T DO THIS BECAUSE OF EOS!
				print "Getting the ns from {} ...".format(self.path)
				from truculence import analysis		# I don't import analysis at the top because it imports ROOT, which breaks cmsRun. Since this function shouldn't get called during cmsRun, we're okay. Yes, this is kludgy.
				ns = analysis.get_nevents(self.dir, [f for f in self.files], tt_name=variables.tt_names[self.kind])
			elif not ns and self.das:		# Check DAS
				print "Checking DAS for nevents list of {} ...".format(self.Name)
				result = das.get_info(self.name, instance=self.instance)
				ns = result["ns"]
		self.ns = ns
		return ns
	
	
	def scan(self, j=False):
#		print "Scanning {} ...".format(self.Name)
#		if self.kind == "miniaod": print "\t{}".format(self.name)
		info = dict(self.primary_keys)
		sample = self.get_sample()
		
		# "path":
#		if not self.path or self.path == "None":
#			if self.kind == "sample":
#				self.path = dir_data.path + "/" + self.name
#			elif self.kind == "miniaod":
#				if hasattr(sample, "path"):
#					self.path = sample.path + "/" + sample.name
#			elif self.kind == "tuple":
#				if hasattr(sample, "path"):
#					self.path = sample.path + "/tuple_{}".format(self.Name)
#			if self.path:
##				self.dir = self.path.split("/")[-1]		# This is to keep "dir" defined because "self" isn't reinitilized.
#				info["path"] = self.path
#		elif self.path[-1] == "/":		# Erase trailing "/" in path if it exists.
#			self.path = self.path[:-1]
##			self.dir = self.path.split("/")[-1]
#			info["path"] = self.path
		
		# "name_full", "instance":
		if hasattr(self, "name"):
			self.name_full = self.name
		
		# "files", "ns", "n":
		if self.kind != "sample":
			in_das = False
			if hasattr(self, "das"):
				in_das = self.das
#			set_files(self, j=j, DAS=in_das)
#			print self.path
			self.set_files(j=j)
			self.set_ns(j=j)
			if len(self.files) > 0:
				if len(self.ns) > 0:
					self.save_json()
				else:
					print "ERROR (dataset.scan): the ns list is empty."
			else:
				print "ERROR (dataset.scan): the file list is empty."
#				print self.files
			if self.ns:
				self.n = sum(self.ns)
				info["n"] = self.n
		
		# "lhe_path":
		if self.kind == "miniaod":
			if not self.lhe_path and self.lhe_cut:
				self.lhe_path = "{}/{}_cut{}.lhe".format(lhe_dir, self.subprocess, self.lhe_cut)
				info["lhe_path"] = self.lhe_path
		
		# "lhe_n":
		if self.kind == "miniaod":
			if self.lhe_path and not self.lhe_n:
				print "Getting nevents from {} ...".format(self.lhe_path)
				lhe_n = self.set_lhe_n()
				if lhe_n:
					info["lhe_n"] = lhe_n
		
		# "weight":
		if self.kind == "miniaod":
			if self.data:
				self.weight = 1
			else:
				if "weight" in [stuff for stuff in infrastructure.get_ds_info(completed=False)["miniaod"] if stuff["generation"] == self.generation and stuff["subprocess"] == self.subprocess][0]: print "WARNING: Skipping weight calculation because it's defined in the YAML."
				else:
					if self.n:
	#					print sample.sigma, sample.luminosity
						self.weight = self.preweight*sample.sigma*sample.luminosity/self.n
					else:
						print "WARNING (dataset.py): Trying to set the weight when the necessary variables aren't defined."
						self.weight == None
			info["weight"] = self.weight
		
		# Update DB:
		update_result = update_db(self.kind, info)
		
		return update_result
	
	
	def update(self, info):
		for key, value in info.items():
			setattr(self, key, value)
		info.update(self.primary_keys)
		return update_db(self.kind, info, db_path=db_path_default)
	
	
	def fix(self):		# Horrible name ...
	# Compare self.info to db_info.
		update_info = {}
		
		db_info = infrastructure.get_db_info()
		for key, info in db_info[self.kind].items():
#			print key, info
			value_new = None
			value_default = info["default"]
			if isinstance(value_default, str):
				if (not value_default.isdigit()) and value_default == value_default.upper() and value_default not in ["PARENT"]:
					if value_default.lower() in update_info:
						value_new = info[value_default.lower()]
					else:
						value_new = getattr(self, value_default.lower())
				if value_default in ["PARENT"]:
					parent = self.get_parent()
					value_new = getattr(parent, key)
			elif getattr(self, key) == None:
				value_new = value_default
			if value_new != None:
				update_info[key] = value_new
		if update_info:
			for key, value in update_info.items():
				setattr(self, key, value)
			return self.update(update_info)
		else:
			return True
	
	
	def find_tuples(self, v=False):
		tuples = []
		p = self.path
		if hasattr(self, "sample") or self.kind == "sample":
			p = self.dir.path
		if v: print "Searching in " + p
		if p and p != "None":
			tuple_dirs = [d for d in listpath(p) if "tuple" in d]
			for d in tuple_dirs:
				pieces = d.split("_")
				if len(pieces) == 4:
					kind = pieces[0]
					subprocess = pieces[1]
					generation = pieces[2]
					suffix = pieces[3]
					if (subprocess == self.subprocess) and (kind == "tuple"):
						info = {
							"category": self.category,		# KLUDGE: this doesn't use meta.yaml
							"process": self.process,
							"subprocess": subprocess,
							"generation": generation,
							"suffix": suffix,
							"path": "{}/{}".format(p, d),
						}
						tup = dataset("tuple", info=info, isolated=True)
						tup.set_connections(down=False, up=True)
						tuples.append(tup)
				else:
					print "WARNING (dataset.find_tuples): Something is wrong with the naming of {}/{}.".format(p, d)
		else: print "[!!] Dataset object {} has a path value of {}.".format(self.Name, self.path)
		return tuples
	
	
	def write(self, db_path=db_path_default):
		info = {}
		for key_db, meta_db in keys_db[self.kind].items():
			primary = meta_db[1]
			if hasattr(self, key_db):
				info[key_db] = getattr(self, key_db)
			elif primary:
				print "ERROR (dataset.write): Cannot write. {} object doesn't have a {} attribute, which is a primary key.".format(self.kind, key_db)
				return False
		return insert_db(self.kind, info, db_path=db_path_default)
	
	def save_json(self):
		dir_json = os.path.dirname(self.json_full)
		if not os.path.exists(dir_json):
			os.makedirs(dir_json)
		info = {
			"files": self.files,
			"ns": self.ns,
			"time": self.time
		}
		with open(self.json_full, "w") as out:
			json.dump(info, out)
	
	def check(self):
		return check_db(self)
# /CLASSES

# FUNCTIONS:
def explore_dataset_dir(d):
	result = {}
	dates = eos.listdir(d)
	d += "/" + dates[-1]
	result["dir"] = d
	result["files"] = []
	subdirs = eos.listdir(d)		# "0000", "0001", etc.
	for subdir in subdirs:
		path_dir = d + "/" + subdir
		result["files"].extend([path_dir + "/" + f for f in eos.listdir(path_dir) if ".root" in f])
	return result


def parse_db_yaml(path=info_path_default, kind=None, subprocess=None, generation=None, completed=True):
	# Arguments:
	kinds = variables.parse_kind(kind)
	
	ds_info = infrastructure.get_ds_info(completed=completed)
	
	datasets = {}
	for k, info_list in ds_info.iteritems():
		# Kind information:
		Kind = infrastructure.get_kind(k)
#		primary_keys = kind.get_primary_keys()
		
		datasets[Kind.name] = []
		for info in info_list:
			datasets[Kind.name].append(dataset(Kind.name, info=info, isolated=True))
	
	# Apply filters:
	datasets = {key: value for key, value in datasets.items() if key in [k.name for k in kinds]}
	if subprocess: datasets = {key: [v for v in value if v.subprocess == subprocess] for key, value in datasets.items()}
	if generation: datasets = {key: [v for v in value if v.generation == generation] for key, value in datasets.items()}
	
	return datasets


def write_db():
	infrastructure.create_tables()
	datasets = parse_db_yaml()
	for kind, dss in datasets.items():
		for ds in dss:
#			print ds
			ds.write()
	return True


#def get_primitives(path_samples=infrastructure.ds_info_default, path_meta=infrastructure.db_info_default):
#	ds_info = infrastructure.get_ds_info(path=path_samples)
#	db_info = infrastructure.get_db_info(path=path_meta)
#	primaries = {kind: [key for key, meta in kind_info.items() if meta["primary"]] for kind, kind_info in db_info.items()}
#	
#	# Fill defaults from db_info:
#	ds_info_complete = ds_info
#	for kind, kind_info in db_info.items():
#		for key, meta in kind_info.items():
#			for i, info in enumerate(ds_info[kind]):
#				if key not in info:
#					ds_info_complete[kind][i][key] = meta["default"]
#				ds_info_complete[kind][i]["primary"] = primaries[kind]
#	
#	# Return primitives in a dictionary:
##	return {kind: [dataset(kind, info=entry, isolated=True) for entry in entries] for kind, entries in info.items()}
#	return {kind: [info for info in infos] for kind, infos in ds_info_complete.items()}


def get_info(path=info_path_default):
	# Get YAML information:
	with open(path, 'r') as f:
		info = yaml.load(f)
	
	t = time()
	
	# Fill missing information:
	info_filled = info
	for category, dsd in info.iteritems():
		for process, dss in dsd.iteritems():
			for i, ds in enumerate(dss):
				info_filled[category][process][i]["category"] = category
				info_filled[category][process][i]["process"] = process
				if "subprocess" not in ds:
					info_filled[category][process][i]["subprocess"] = process
#				if "n" not in ds:
#					info_filled[category][process][i]["n"] = info_filled[category][process][i]["miniaod_n"]
				if "signal" not in ds:
					info_filled[category][process][i]["signal"] = False
				if "hts" in ds:
					info_filled[category][process][i]["parameter1"] = info_filled[category][process][i]["hts"][0]
					info_filled[category][process][i]["parameter2"] = info_filled[category][process][i]["hts"][1]
				if "pts" in ds:
					info_filled[category][process][i]["parameter1"] = info_filled[category][process][i]["pts"][0]
					info_filled[category][process][i]["parameter2"] = info_filled[category][process][i]["pts"][1]
				if "m" in ds:
					info_filled[category][process][i]["parameter1"] = info_filled[category][process][i]["m"]
				if "ms" in ds:
					info_filled[category][process][i]["parameter1"] = info_filled[category][process][i]["ms"][0]
					info_filled[category][process][i]["parameter2"] = info_filled[category][process][i]["ms"][1]
				if "luminosity" not in ds:
					info_filled[category][process][i]["luminosity"] = luminosity_default
				info_filled[category][process][i]["time"] = t
				for i_miniaod in range(len(info_filled[category][process][i]["miniaods"])):
					if "subprocess" not in info_filled[category][process][i]["miniaods"][i_miniaod]:
						info_filled[category][process][i]["miniaods"][i_miniaod]["subprocess"] = info_filled[category][process][i]["subprocess"]
					if "das" not in info_filled[category][process][i]["miniaods"][i_miniaod]:
						info_filled[category][process][i]["miniaods"][i_miniaod]["das"] = True
#					if "dir" not in info_filled[category][process][i]["miniaod"][i_miniaod]:
#						info_filled[category][process][i]["miniaod"][i_miniaod]["dir"] = info_filled[category][process][i]["name"]
	
	return info_filled


def get_paths(miniaod_name_full):
	das_url = "https://cmsweb.cern.ch"
	das_query = "file dataset={}".format(miniaod_name_full)
	data = das.get_data(das_url, das_query, 0, 0, 0, ckey=das.x509(), cert=das.x509())
	return [f["file"][0]["name"] for f in data["data"]]

## Variable conversions:
def get_subprocess(path=info_path_default, name=None):
	# Arguments:
	if name and not isinstance(name, list):
		name = [name]
	
	# Get dataset info:
	info = get_info(path=path)
	dss = [ds for c, dsd in info.iteritems() for p, dss in dsd.iteritems() for ds in dss]    # Make a list of all dataset infos.
	
	# Get subprocesses:
	if name:
		subprocesses = [ds["subprocess"] for ds in dss if ds["name"] in name]
	else:
		subprocesses = [ds["subprocess"] for ds in dss]
	
	return subprocesses


def sync_yaml(write_nones=False):
	primitives_dict = get_primitives()
	for kind, primitives in primitives_dict.items():
		for primitive in primitives:
			if not write_nones:
				primitive = {key: value for key, value in primitive.items() if value != None and value != "PARENT"}
			update_db(kind, primitive)


def fetch_info(subprocess=None, generation=None, suffix=None, kind="*", primary_keys=None, db_path=db_path_default, single=True):
	# Arguments:
	if not primary_keys:
		primary_keys = {}
		if subprocess:
			primary_keys["subprocess"] = subprocess
		if generation:
			primary_keys["generation"] = generation
		if suffix:
			primary_keys["suffix"] = suffix
	
	# Open database:
	conn = sqlite3.connect(db_path)
	c = conn.cursor()
	
	# Prepare SQLite command:
	cmd_where = "WHERE "
	for key, value in primary_keys.items():
		if value:
			cmd_where += "{}='{}' AND ".format(key, value)
	if cmd_where == "WHERE ":
		cmd_where = ""
	else:
		cmd_where = cmd_where[:-5]
	cmd = "SELECT * FROM {} {}".format(kind, cmd_where)
#	print cmd
	
	# Query:
	try:
		c.execute(cmd)
	except Exception as ex:
		print ex
	else:
		if single:
			raw = c.fetchone()
			if raw:
				d = {}
				for i, key in enumerate(keys_db[kind].keys()):
					d[key] = raw[i]
				return d
		else:
			print "WARNING (dataset.fetch_info): single=False hasn't been implemented, yet."
#			raws = c.fetchall()
#			if raws:
#			for raw in raws:
#				info = {}
#				for i, key in enumerate(keys_db["sample"].keys()):
#					info[key] = raw[i]
#				samples.append(samp(info, isolated=isolated))
	return {}


def fetch_sample(subprocess, db_path=db_path_default):
	query = {
		"subprocess": subprocess
	}
	return fetch_entry("sample", query)


def fetch_samples(db_path=db_path_default, subprocess=None, process=None, category=None, isolated=False):
	query = {}
	if subprocess:
		query["subprocess"] = subprocess
	if process:
		query["process"] = process
	if category:
		query["category"] = category
	return fetch_entries("sample", query, isolated=isolated)


def fetch_miniaod(subprocess, generation, db_path=db_path_default):
	query = {
		"subprocess": subprocess,
		"generation": generation,
	}
	return fetch_entry("miniaod", query)


def fetch_miniaods(subprocess, db_path=db_path_default, isolated=False):
	# Open database:
	conn = sqlite3.connect(db_path)
	c = conn.cursor()
	
	# Prepare SQLite command:
	cmd = "SELECT * FROM miniaod WHERE subprocess='{}'".format(subprocess)
	
	# Query:
	c.execute(cmd)
	raws = c.fetchall()
	
	# Parse:
	if raws:
		maods = []
		for raw in raws:
			d = {}
			for i, key in enumerate(keys_db["miniaod"].keys()):
				d[key] = raw[i]
			maods.append(maod(d, isolated=isolated))
		return maods
	else:
		return False


def fetch_tuple(subprocess, generation, suffix, db_path=db_path_default, isolated=False):
	query = {
		"subprocess": subprocess,
		"generation": generation,
		"suffix": suffix,
	}
	return fetch_entry("tuple", query, isolated=isolated)


def fetch_tuples(category=None, suffix=None, subprocess=None, generation=None, process=None, db_path=db_path_default, isolated=False):
	query = {}
	if category:
		query["category"] = category
	if process:
		query["process"] = process
	if subprocess:
		query["subprocess"] = subprocess
	if generation:
		query["generation"] = generation
	if suffix:
		query["suffix"] = suffix
	return fetch_entries("tuple", query, isolated=isolated)


def prepare_fetch(k, query):
	kind = infrastructure.get_kind(k)
	# Check that "primary_keys" shares something with the keys of "kind":
#	info = {key: value for key, value in query.items() if key in primary_keys_master[kind]}		# Take only primary keys that are primary keys of the kind.
	if query == None: query = {}
	info = query
	info = {k: v for k, v in info.items() if k in kind.get_keys()}

	# Prepare SQLite command:
	cmd_where = ""
	ands = []
	for key, value in info.items():
		if value:
			if not isinstance(value, list):
				value = [value]
			ors = []
			for v in value:
				ors.append("{}='{}'".format(key, v))
			ands.append("(" + " OR ".join(ors) + ")")
	cmd_where += " AND ".join(ands)
	if cmd_where:
		cmd_where = "WHERE " + cmd_where
	cmd = "SELECT * FROM {} {}".format(kind.name, cmd_where)
#	print cmd
	return cmd

def fetch_entry(kind, query, db_path=db_path_default, isolated=True):
		cmd = prepare_fetch(kind, query)
		if cmd:
			# Open database:
			conn = sqlite3.connect(db_path)
			c = conn.cursor()
			
			# Query:
			c.execute(cmd)
			raw = c.fetchone()
		
			# Parse:
			if raw:
				d = {}
				for i, key in enumerate(keys_db[kind].keys()):
					d[key] = raw[i]
				return dataset(kind, info=d, isolated=isolated)
		return None

def fetch_entries(kind, query=None, db_path=db_path_default, isolated=True):
		cmd = prepare_fetch(kind, query)
#		print cmd
		
		if cmd:
			# Open database:
			conn = sqlite3.connect(db_path)
			c = conn.cursor()
			
			# Query:
			try:
				c.execute(cmd)
			except Exception as ex:
				print cmd
				print ex
			else:
				raws = c.fetchall()
				# Parse:
				if raws:
					results = []
					for raw in raws:
#						print raw
#						print 
						d = {}
						for i, key in enumerate(keys_db[kind].keys()):
							d[key] = raw[i]
						results.append(dataset(kind, info=d, isolated=isolated))
					return results
		return []


def fetch_db(db_path=db_path_default, category=None, process=None, subprocess=None):
	# Argument parsing:
	if category and not isinstance(category, list):
		category = [category]
	if process and not isinstance(process, list):
		process = [process]
	if subprocess and not isinstance(subprocess, list):
		subprocess = [subprocess]
	
	# Open database:
	conn = sqlite3.connect(db_path)
	c = conn.cursor()
	
	dss = []
	if category:
		cmd_where = ""
		for cat in category:
			cmd_where += "category='{}' OR ".format(cat)
		cmd_where = cmd_where[:-4]
		c.execute("SELECT * FROM dataset WHERE {}".format(cmd_where))
	elif process:
		cmd_where = ""
		for p in process:
			cmd_where += "process='{}' OR ".format(p)
		cmd_where = cmd_where[:-4]
		c.execute("SELECT * FROM dataset WHERE {}".format(cmd_where))
	elif subprocess:
		cmd_where = ""
		for sp in subprocess:
			cmd_where += "subprocess='{}' OR ".format(sp)
		cmd_where = cmd_where[:-4]
		c.execute("SELECT * FROM dataset WHERE {}".format(cmd_where))
	else:
		c.execute("SELECT * FROM dataset")
	results_raw = c.fetchall()
	for raw in results_raw:
		d = {}
		for i, key in enumerate(keys_db["dataset"].keys()):
			d[key] = raw[i]
		dss.append(dataset(info=d))
	return dss


def print_db(db_path=db_path_default):
	conn = sqlite3.connect(db_path)
	c = conn.cursor()
	
	for name in keys_db.keys():
		c.execute("SELECT * FROM {}".format(name))
		results = c.fetchall()
		print name, results


def insert_db(name, info, db_path=db_path_default):
	if set([k for k, v in keys_db[name].items() if v[1]]) < set(info.keys()):
		cmd = "INSERT INTO {} VALUES(".format(name)
		
		for key_db, key_info in keys_db[name].items():
			dtype = key_info[0]
			primary = key_info[1]
			db_value = "NULL"
			if key_db in info:
				value = info[key_db]
				if value != None:
					db_value = "{}".format(value)
					if dtype == "text":
						db_value = "'{}'".format(value)
					elif dtype == "integer":
						db_value = "{}".format(int(value))
				else:
					db_value = "NULL"
			
			cmd += "{}, ".format(db_value)
		
		cmd = cmd[:-2] + ")"
		
		conn = sqlite3.connect(db_path)
		c = conn.cursor()
		try:
			c.execute(cmd)
		except Exception as ex:
			print cmd
			print ex
			return False
		else:
			conn.commit()
			return True
	else:
		print "ERROR (dataset.insert_db): The info was insufficient to insert a row. See below."
		print info.keys()
		return False


def update_db(kind, info, db_path=db_path_default):
	if "time" not in info:
		info["time"] = time()
	
	print info
	
	values = []
	wheres = []
	
	for key, value in info.items():
		if key in database_info[kind]:
			dtype = database_info[kind][key]["type"]
			primary = database_info[kind][key]["primary"]
			if primary:
				if dtype == "text":
					wheres.append("{}='{}'".format(key, value))
				else:
					wheres.append("{}={}".format(key, value))
			else:
				if dtype == "text":
					values.append("{}='{}'".format(key, value))
				else:
					values.append("{}={}".format(key, value))
		else:
			print "WARNING (dataset.update_db): {} isn't a {} database variable. It was not updated.".format(key, kind)
	
	if values and wheres:
		cmd = "UPDATE {} SET {} WHERE {}".format(kind, ", ".join(values), " AND ".join(wheres))
		conn = sqlite3.connect(db_path)
		c = conn.cursor()
		try:
			print cmd
			c.execute(cmd)
		except Exception as ex:
			print cmd
			print ex
			return False
		else:
			conn.commit()
			return True
	else:
		return False


def listpath(path):
	match = re.search("^/store/user/tote", path)
	if match:		# If in EOS
		return eos.listdir(path)
	else:
		if os.path.exists(path): return os.listdir(path)
		else: return []


def check_db(thing):		# Check if thing is in the database.
	# There are three things to compare: the "thing", the DB version of the thing, and the completed YAML version.
	kind = thing.kind
	thing_db = fetch_entry(kind, thing.primary_keys)
	thing_yaml = parse_db_yaml(completed=False, kind=kind, subprocess=thing.subprocess, generation=None if not thing.kind == "miniaod" else thing.generation)[kind]
	if len(thing_yaml) > 1:
		print "AAAAAAAA (check_db)"
		return False
	thing_yaml = thing_yaml[0]
	
	results = {}
	if thing_db:
		for key in keys_db[kind].keys():
			v = getattr(thing, key)
			v_db = getattr(thing_db, key)
			v_yaml_has = hasattr(thing_yaml, key)
			v_yaml = False
			if v_yaml_has: v_yaml = getattr(thing_yaml, key)
			results[key] = {}
			results[key]["new"] = v
			results[key]["old"] = v
			results[key]["change"] = False
		
			# If v and v_db differ, take on the value of v
			if not utilities.isclose(v, v_db):
				results[key]["new"] = v
				results[key]["old"] = v_db
				results[key]["change"] = True
#				print "DB", results[key]
		
			# If v and v_yaml 
			if v_yaml_has and not utilities.isclose(v, v_yaml):
				results[key]["new"] = v_yaml
				results[key]["old"] = v
				results[key]["change"] = True
#				print "YAML", results[key]
	return results


def check_db_against_yaml(thing_db):
	kind = thing_db.kind
	thing_yaml = parse_db_yaml(completed=False, kind=kind, subprocess=thing_db.subprocess, generation=None if not thing_db.kind == "miniaod" else thing_db.generation)[kind]
	if len(thing_yaml) > 1:
		print "AAAAAAAA (check_db)"
		return False
	thing_yaml = thing_yaml[0]
	
	results = {}
	for key in keys_db[kind].keys():
		v_db = getattr(thing_db, key)
		v_yaml_has = hasattr(thing_yaml, key)
		v_yaml = False
		if v_yaml_has: v_yaml = getattr(thing_yaml, key)
		results[key] = {}
		results[key]["new"] = v_db
		results[key]["old"] = v_db
		results[key]["change"] = False
	
		# If v_db and v_yaml:
		if v_yaml_has and not utilities.isclose(v_db, v_yaml):
			results[key]["new"] = v_yaml
			results[key]["old"] = v_db
			results[key]["change"] = True
	return results


def check_yaml_against_db(thing_yaml):		# Check if thing is in the database.
	kind = thing_yaml.kind
	thing_db = fetch_entry(kind, thing_yaml.primary_keys)
	
	if thing_db: return True
	else: return False


def sync_db(self):
	check_result = check_db(self)
	if check_result:
		info = {}
		(replace, update) = check_result
		for key, value in update.items():
			if value:
				info[key] = getattr(self, key)
		info["time"] = time()
		self.update(info)
		return True
#		if sum(replace.values()) == len(replace.values()):
##				return self.replace()
#			return True
#		else:
#			return True
	else:
		print "Adding {} to the DB ...".format(self.Name)
		return self.write()


def set_files(thing, j=True, DAS=True):
	files = []
	if j:
		if os.path.exists(thing.json_full):
			with open(thing.json_full) as infile:
				files = json.load(infile)["files"]
	if not files:
		if thing.path and not DAS:
#			if os.path.exists(self.path):		# I CAN'T DO THIS BECAUSE OF EOS!
			files = crab.find_files(thing.path)["files"]
		if not files and DAS:		# Check DAS
			print "Checking DAS for file list of {} ...".format(thing.Name)
			result = das.get_info(thing.name, instance=thing.instance)
#			print result["raw"]
			files = result["files"]
	thing.files = files
	return files


def set_ns(thing, j=True, DAS=True):
	ns = []
	if j:
		if os.path.exists(thing.json_full):
			with open(thing.json_full) as infile:
				ns = json.load(infile)["ns"]
	if not ns:
		if not ns and not DAS:
#			if os.path.exists(self.path):		# I CAN'T DO THIS BECAUSE OF EOS!
			print "Getting the ns from {} ...".format(thing.path)
			from truculence import analysis		# I don't import analysis at the top because it imports ROOT, which breaks cmsRun. Since this function shouldn't get called during cmsRun, we're okay. Yes, this is kludgy.
			ns = analysis.get_nevents(thing.dir, thing.files, tt_name=variables.tt_names[thing.kind])
		elif not ns and DAS:		# Check DAS
			print "Checking DAS for nevents list of {} ...".format(thing.Name)
			result = das.get_info(thing.name, instance=thing.instance)
			ns = result["ns"]
	thing.ns = ns
	return ns


def fetch_connections(primary_keys):
	print set(primary_keys.keys())
	kinds_children = [kind for kind, keys in primary_keys_master.items() if set(primary_keys.keys()) < set(keys)]
	kinds_parents = [kind for kind, keys in primary_keys_master.items() if set(primary_keys.keys()) > set(keys)]
	print "children:", kinds_children
	print "parents:", kinds_parents
	
	sys.exit()
	# Arguments:
	if not primary_keys:
		primary_keys = {}
		if subprocess:
			primary_keys["subprocess"] = subprocess
		if generation:
			primary_keys["generation"] = generation
		if suffix:
			primary_keys["suffix"] = suffix
	
	# Open database:
	conn = sqlite3.connect(db_path)
	c = conn.cursor()
	
	# Prepare SQLite command:
	cmd_where = "WHERE "
	for key, value in primary_keys.items():
		cmd_where += "{}='{}' AND ".format(key, value)
	if cmd_where == "WHERE ":
		cmd_where = ""
	else:
		cmd_where = cmd_where[:-5]
	cmd = "SELECT * FROM {} {}".format(kind, cmd_where)
#	print cmd
	
	# Query:
	c.execute(cmd)
	raw = c.fetchone()
	
	# Parse:
	if raw:
		d = {}
		for i, key in enumerate(keys_db[kind].keys()):
			d[key] = raw[i]
		
		return d
	else:
		return {}

def sort_datasets(dss, collapse=True):
# Given a list of datasets, sort it into a dictionary keyed by primary key tuples.
	results = {}
	for ds in dss:
		key = [ds.kind]
		key += [getattr(ds, k) for k in ["process", "generation", "suffix"]]
		# Get rid of "ext" in generations:
		if key[2][-3:] == "ext": key[2] = key[2][:-3]
		
		key = tuple(key)
		
		if key not in results:
			results[key] = []
		results[key].append(ds)
	
	# Collapse keys:
	## This reduces the keys to the least number of identifying parameters.
	if collapse:
		if len(set([k[0] for k in results.keys()])) != 1:		# If all of the kinds are not the same.
			return results
		results_collapsed = {}
		for keys, value in results.items():
#			print keys, value
			i_collapse = []		# Items to remove
			for i, key in enumerate(keys):
				count = len([k[i] for k in results.keys() if k[i] == key])
				if count == len(results):
					i_collapse.append(i)
			try:
				i_collapse.remove(1)		# The "process" should always be there.
			except:
				pass
			results_collapsed["_".join([key for i, key in enumerate(keys) if i not in i_collapse])] = value
		
		return results_collapsed
# /FUNCTIONS

# VARIABLES:
# /VARIABLES
