####################################################################
# Type: SCRIPT                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import sys
from time import time
#import decortication
from decortication import dataset, variables
# /IMPORTS

# CLASSES:
# /CLASSES

# VARIABLES:
#j=False
# /VARIABLES

# FUNCTIONS:
def discover_tuples():
	samples = dataset.fetch_samples()
	tuples_new = []
	for sample in samples:
		tuples_new_temp = []
		print "\tSearching for {} tuples ...".format(sample.Name)
		tuples = sample.find_tuples()
#		if tuples:
#			print "\t\tTuples found: {}".format([tup.Name for tup in tuples])
#		else:
#			print "\t\tNo tuples found."
		for tup in tuples:
#			if tup.generation in ["spring15-inverted", "spring15-cutht700"]:
#				tuples_new.append(tup)
			if not tup.check():
				tuples_new_temp.append(tup)
		if tuples_new_temp:
			print "\t\tFound new tuples: {}".format(tuples_new_temp)
			tuples_new.extend(tuples_new_temp)
	return tuples_new

def main():
	# Arguments:
	a = variables.arguments()
	args = a.args
	if not a.kinds:
		a.kinds = variables.all_kinds
	j = not args.json
	
	# Step 1: check if anything needs to be added to or updated in the DB:
	print "Step 1: Checking if anything needs to be added to or updated in the DB ..."
	datasets = dataset.parse_db_yaml(completed=False)
	
	print "\tChecking samples.yaml against the DB ..."
	n_added = 0
	n_updated = 0
	for kind, dss in datasets.items():
		for ds in dss:
			check_result = ds.check()
			# Deal with entries that aren't in the DB:
			if not check_result:
				n_added += 1
				print "\tAdding {} to the DB ...".format(ds.Name)
				ds.write()
			
			# Update enries in the DB that need updating (e.g., if you recently edited "samples.yaml"):
			else:
				keys_update = [key for key, value in check_result[1].items() if value and key != "time"]		# "check_result[1]" contains information about what should be updated in the DB.
				if keys_update:
					n_updated += 1
					info = {key: getattr(ds, key) for key in keys_update}
					print "\tUpdating the following values for {} ...".format(ds.Name)
					print "\t{}".format(info)
					ds.update(info)
	
	## Print a summary:
	print "Step 1 summary:"
	if n_added:
		print "\t{} entries added.".format(n_added)
	else:
		print "\tNothing needed to be added."
	if n_updated:
		print "\t{} entries updated.".format(n_updated)
	else:
		print "\tNothing needed to be updated."
	
	
	# Step 2: search (but don't scan) for new tuples:
	print "Step 2: Searching for new tuples ..."
	tuples_new = discover_tuples()
	n_added = 0
	for tup in tuples_new:
#		print tup.update({"path": tup.path})
		print "Adding {} to the DB ...".format(tup.Name)
		tup.write()
		n_added += 1
	
	## Print a summary:
	print "Step 2 summary:"
	if n_added:
		print "\t{} tuples added.".format(n_added)
	else:
		print "\tNo tuples needed to be added."
	
	# Step 3: Fetch entries to scan:
	print "Step 3: Scanning entries ..."
	entries_dict = {}
	for kind in a.kinds:
		entries_dict[kind] = dataset.fetch_entries(kind, a.query)
	n_entries = sum([len(l) for l in entries_dict.values()])
	if n_entries:
		print "\tThere are {} entries to scan.".format(n_entries)
	else:
		print "\tThere were no entries to scan. Your query was the following:\n{}\nkinds = {}".format(a.query, a.kinds)
	for kind, entries in entries_dict.items():
		for entry in entries:
#			print entry.das
#			print dataset.set_files(entry, j=j, DAS=entry.das)
			print "\tFixing {} ...".format(entry.Name)
			entry.fix()
			print "\tScanning {} ...".format(entry.Name)
			entry.scan(j=j)
	return True
# /FUNCTIONS

# MAIN:
if __name__ == "__main__":
	main()
# /MAIN

