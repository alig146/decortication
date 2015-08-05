# IMPORTS:
import numpy
import samples
# /IMPORTS

# CLASSES:
class variable:
	def __init__(self, name="", name_formatted="", unit=None, minimum=None, maximum=None):
		self.name = name
		self.name_formatted = name_formatted
		self.minimum = minimum
		self.maximum = maximum
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
# /FUNCTIONS

# VARIABLES:
#variables = {
#	"jet": ["m", "pt", "eta", "phi", "y"],
#	"dijet": ["m_avg", "dm"],
#	"event": ["pt_hat", "ht"],
#}
#variables_all = reduce(lambda x, y: x + y, [values for key, values in variables.iteritems()])
variables = [
	variable(name="m", name_formatted="m"),
	variable(name="pt", name_formatted="p_{T}"),
	variable(name="eta", name_formatted="#eta"),
	variable(name="phi", name_formatted="#phi"),
]
# /VARIABLES
