from decortication.dataset import fetch_entries

processes = ["qcdp", "qcdmg"]
lum = 38.180*1000

for process in processes:
	miniaods = fetch_entries("miniaod", {"process": process, "generation":["moriond17", "moriond17ext"]})
	results = {}
	for miniaod in miniaods:
		if miniaod.subprocess not in results:
			results[miniaod.subprocess] = [miniaod.n, miniaod.get_sample().sigma]
		else: results[miniaod.subprocess][0] += miniaod.n
	for subprocess, values in results.items():
		values.append(values[1]*lum/values[0])
		print subprocess, values
