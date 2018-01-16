####################################################################
# Type: MODULE                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os
from decortication import infrastructure
# :IMPORTS

# VARIABLES:
site_names = {
	"hexcms": ["hexcms", "hexfarm"], 
	"cmslpc": ["cmslpc", "fnal.gov"],
	"lxplus": ["lxplus"],
}
path_config_default = infrastructure.get_res_path("sites.yaml")
# :VARIABLES

# CLASSES:
class directory:
	def __init__(self, info):
		for key, value in info.items(): setattr(self, key, value)
		if not hasattr(self, "eos"): self.eos = False
	
	def __copy__(self):
		return directory(self.__dict__)
	
	def cd(self, path):
		if path[0] == "/": self.path = path
		else:
			if self.path[-1] != "/": self.path += "/"
			self.path += path
		return path
	
	def ls(self, crab=True, recursive=True):
		if not self.eos:
			import fnmatch
			files = []
			# Deal with date directories:
			dir_date = sorted(os.listdir(self.path))[-1]
			p = os.path.join(self.path, dir_date)
			# Get all root files inside the date directory:
			for origin, dirnames, filenames in os.walk(p):
				for filename in fnmatch.filter(filenames, '*.root'):
					files.append(os.path.join(origin, filename))
				if not recursive: break
			return files
		else: # recursive doesn't work:
			from subprocess import Popen, PIPE
			path = self.path
			if path != "/": path += "/"
			if crab:
				cmd = 'eos root://{} ls {}'.format(self.url_eos, path)
				raw_output = Popen([cmd], shell=True, stdout=PIPE, stderr=PIPE).communicate()
				date = [thing for thing in raw_output[0].split("\n") if thing][-1]		# Take the most recent
				path += date +"/"
			cmd = 'eos root://{} ls {}'.format(self.url_eos, path)
			print cmd
			raw_output = Popen([cmd], shell=True, stdout=PIPE, stderr=PIPE).communicate()
			# SKIPPED CRAB SUBDIR SECTION!
			files = [path + thing for thing in raw_output[0].split("\n") if ".root" in thing]		# Take the most recent
			return files

class site:
	def __init__(self, info):
		for key, value in info.items(): setattr(self, key, value)
	
	def get_dir(self, name):
		if name in self.dirs: return self.dirs[name]
		return False
# :CLASSES

# FUNCTIONS:
def get_site(site_name=None):
	sites = parse_configuration()
	if not site_name: site_name = get_site_name()
	if site_name: return [s for s in sites if s.name == site_name][0]
	return False

def get_site_name():
	# [Get the "site name" of the machine you're using.]
	
	import socket
	hostname = socket.gethostname()
	for site_name, alts in site_names.items():
		for alt in alts:
			if alt in hostname: return site_name
	return False

def parse_configuration(path=path_config_default):
	# [Read in "sites.yaml" and make appropriate objects]
	
	sites = []
	import yaml, re
	with open(path, 'r') as f: yinfo = yaml.load(f)
	for site_name, info in yinfo.items():
		info["name"] = site_name
		info["dirs"] = {}
		for key, value in info.items():
			match = re.search("^dir_(\w+)", key)
			if match:
				info_dir = value
				info_dir["name"] = match.group(1)
				if "url_eos" in info: info_dir["url_eos"] = info["url_eos"]
				info["dirs"][info_dir["name"]] = directory(info_dir)
		
		sites.append(site(info))
	return sites
# :FUNCTIONS
