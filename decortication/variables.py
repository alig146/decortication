# IMPORTS:
import numpy
#import samples
import argparse       # For commandline options
from collections import OrderedDict
from decortication import infrastructure
# /IMPORTS

# VARIABLES:
identifiers = OrderedDict()
identifiers["kind"] = {"plural": "kinds"}
identifiers["category"] = {"plural": "categories"}
identifiers["process"] = {"plural": "processes"}
identifiers["subprocess"] = {"plural": "subprocesses"}
identifiers["generation"] = {"plural": "generations"}
identifiers["suffix"] = {"plural": "suffixes"}
tt_names = {		# Should I store this in the DB?
	"tuple": "tuplizer/events",
	"miniaod": "Events",
}
all_kinds = infrastructure.get_db_info().keys()
# :VARIABLES

# CLASSES:
class variable:
	def __init__(self, name="", name_formatted="", unit=None, minimum=None, maximum=None):
		self.name = name
		self.name_formatted = name_formatted
		self.minimum = minimum
		self.maximum = maximum

class arguments:
	def __init__(self):
		# Argument parser:
		parser = argparse.ArgumentParser()
	
		parser.add_argument(
			"-c", "--category", dest="category",
			type=str,
			default=None,
			help="The categories of the sample you want to tuplize (e.g. \"qcd\")",
			metavar="STR"
		)
		parser.add_argument(
			"-p", "--process", dest="process",
			type=str,
			default=None,
			help="The processes of the sample you want to tuplize (e.g. \"qcdmg\")",
			metavar="STR"
		)
		parser.add_argument(
			"-sp", "--subprocess", dest="subprocess",
			type=str,
			default=None,
			help="The subprocesses of the sample you want to tuplize (e.g. \"qcdmg1000\")",
			metavar="STR"
		)
		parser.add_argument(
			"-g", "--generation", dest="generation",
			type=str,
			default=None,
			help="The miniaod generation (e.g. 'spring15')",
			metavar="STR"
		)
		parser.add_argument(
			"-s", "--suffix", dest="suffix",
			type=str,
			default=None,
			help="The tuple suffix (e.g. 'pt400')",
			metavar="STR"
		)
		parser.add_argument(
			"-k", "--kind", dest="kind",
			type=str,
			default=None,
			help="The kind of dataset",
			metavar="STR"
		)
		parser.add_argument(
			"-a", "--algorithm", dest="algorithm",
			type=str,
			default="ca12",
			help="The fatjet algorithm",
			metavar="STR"
		)
		parser.add_argument(
			"-n", "--n", dest="n",
			type=int,
			default=-1,
			help="An integer number",
			metavar="INT"
		)
		parser.add_argument(
			"-d", "--dir", dest="dir",
			type=str,
			default=None,
			help="Input directory",
			metavar="STR"
		)
		parser.add_argument(
			"-f", "--input", dest="input",
			type=str,
			default=None,
			help="Input file(s)",
			metavar="STR"
		)
		parser.add_argument(
			"-o", "--output", dest="output",
			type=str,
			default=None,
			help="Output file(s)",
			metavar="STR"
		)
		parser.add_argument(
			"-c1", "--cut1", dest="cut1",
			type=float,
			default=None,
			help="A cut",
			metavar="FLT"
		)
		parser.add_argument(
			"-c2", "--cut2", dest="cut2",
			type=float,
			default=None,
			help="A cut",
			metavar="FLT"
		)
		parser.add_argument(
			"-c3", "--cut3", dest="cut3",
			type=float,
			default=None,
			help="A cut",
			metavar="FLT"
		)
		parser.add_argument(
			"-v", "--verbose", dest="verbose",
			type=int,
			default=0,
			help="Verbose level ('0' is lowest)",
			metavar="INT"
		)
		parser.add_argument(
			"-j", "--json", dest="json",
			action='store_true',
			help="A JSON switch",
		)
		
		self.args = parser.parse_args()
		# Parse identifiers:
		for var, var_d in identifiers.items():
			if getattr(self.args, var):
				setattr(self, var_d["plural"], getattr(self.args, var).split(","))
				setattr(self, var, getattr(self, var_d["plural"])[0])
			else:
				setattr(self, var_d["plural"], [])
				setattr(self, var, getattr(self.args, var))
		# Parse input
		if getattr(self.args, "input"):
			setattr(self, "input", getattr(self.args, "input").split(","))
		else:
			setattr(self, "input", [])
		setattr(self, "f", getattr(self, "input"))
		# Set an attribute that's useful for querying the DB:
		self.get_query()
	
	def Print(self):
		for var, var_d in identifiers.items():
			print "{}: {}".format(var, getattr(self, var))
			print "{}: {}".format(var_d["plural"], getattr(self, var_d["plural"]))
	
	def get_query(self):
		self.query = {}
		for var, var_d in identifiers.items():
			if var not in ["kind"]:
				value = getattr(self, var_d["plural"])
				if value:
					self.query[var] = value
		return self.query
# /CLASSES

# FUNCTIONS:




def get_variable(name="", collection="", event=None):
	if name not in variables_all:
		print "ERROR (variables.get_variable): The variable you entered, {0}, is not recognized. The following variables are valid:\n{1}".format(name, variables_all)
		return False
	else:
		result = {}
		try:
			if name in variables["jet"]:
				result[collection] = getattr(event, "{0}_{1}".format(collection))
			elif name == "m_avg":
				result[collection] = numpy.mean(getattr(event, "{0}_{1}".format(collection)))
			elif name == "dm":
				result[collection] = -1*numpy.diff(getattr(event, "{0}_{1}".format(collection)))[0]
		except Exception as ex:
			print ex
			print "ERROR (variables.get_variable): I couldn't find the variable in the event."
			return False
		else:
			return result

def parse_kind(kind=None):
	if kind:
		if isinstance(kind, str): kind = [kind]
		return [infrastructure.get_kind(k) for k in kind]
	else:
		return infrastructure.get_kinds()
	
# /FUNCTIONS

# VARIABLES:
#variables = {
#	"jet": ["m", "pt", "eta", "phi", "y"],
#	"dijet": ["m_avg", "dm"],
#	"event": ["pt_hat", "ht"],
#}
#variables_all = reduce(lambda x, y: x + y, [values for key, values in variables.iteritems()])
variables = [
	variable(name="pt_hat", name_formatted="p_{T} hat"),
	variable(name="m", name_formatted="m"),
	variable(name="pt", name_formatted="p_{T}"),
	variable(name="eta", name_formatted="#eta"),
	variable(name="phi", name_formatted="#phi"),
]
# /VARIABLES
