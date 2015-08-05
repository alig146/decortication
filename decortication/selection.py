# CLASSES:
class selection:
	# Construction:
	def __init__(self, n_in=-1, n_out=-1):
		self.n_in = n_in
		self.n_out = n_out
		self.passed = self.n_in
		
		if n_in > 0 and n_out >= 0:
			self.acceptance = n_out / float(n_in)
	# /Construction
	

#class cut:
#	
# /CLASSES

# FUNCTIONS:
#def select(cuts, dataset):
# /FUNCTIONS
