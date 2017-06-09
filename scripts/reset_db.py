####################################################################
# Type: SCRIPT                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import os
import decortication
from decortication import dataset, infrastructure
# /IMPORTS

# CLASSES:
# /CLASSES

# VARIABLES:
# /VARIABLES

# FUNCTIONS:
def delete_db(db_path=infrastructure.get_res_path("samples.db")):
	try:
		os.remove(db_path)
		return True
	except OSError:
		return False

def main():
	print "Database deleted:", delete_db()
	print "Database created:", dataset.write_db()
	return True
# /FUNCTIONS

# MAIN:
if __name__ == "__main__":
	main()
# /MAIN

