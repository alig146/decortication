####################################################################
# Type: SCRIPT                                                     #
#                                                                  #
# Description: [description]                                       #
####################################################################

# IMPORTS:
import sys
from collections import OrderedDict
from decortication import eos, dataset
import urllib
# :IMPORTS

# CLASSES:
# :CLASSES

# VARIABLES:
background_info_qcd = [
	{"process": "qcdmg", "generation": "moriond17"},
	{"process": "qcdp", "generation": "moriond17"},
]
background_info_other = [
	{"process": "ttbar", "generation": "moriond17"},
	{"process": "wjets", "generation": "moriond17"},
	{"process": "zjets", "generation": "moriond17"},
	{"process": "zzto4q", "generation": "moriond17"},
	{"process": "zzto2l2q", "generation": "moriond17"},
#	{"process": "zzto4l", "generation": "moriond17"},
	{"process": "wwto4q", "generation": "moriond17"},
	{"process": "wwto2l2q", "generation": "moriond17"},
	{"process": "wz", "generation": "spring16"},
]
signal_info = [
	{"process": "sq100to4j", "generation": "0706"},
	{"process": "sq150to4j", "generation": "0706"},
	{"process": "sq200to4j", "generation": "0706"},
	{"process": "sq250to4j", "generation": "0706"},
	{"process": "sq300to4j", "generation": "0706"},
	{"process": "sq400to4j", "generation": "0706"},
	{"process": "sq500to4j", "generation": "0706"},
]
data_info = [
	{"process": "jetht15", "generation": "0706"},
	{"process": "jetht16", "generation": "feb17"},
]
# :VARIABLES

# FUNCTIONS:
def latex_escape(s):
	return s.replace("$", "\$").replace("_", "\_").replace("%", "\%")


def make_dataset_table_data(dss_info, name, caption):
	miniaods = OrderedDict()
	for info in dss_info:
		miniaods[info["process"]] = dataset.fetch_entries("miniaod", query=info)
#	print miniaods
	
	table = "\\begin{table}[htbp]\n\t\caption{" + caption + "}\n"
	table += "\t\centering\setlength\doublerulesep{0.1in}\n"
	tabular = "\t\t\\begin{tabular}{|l|r|}\hline\n\t\t\t\\textbf{Dataset name} & \\textbf{Int. lum. [fb\\textsuperscript{-1}]} \\\\\hline\n"
	ngroup = 0
#	totals = [0, 2.183, 35.545]
	for key, maods in miniaods.items():
		ngroup += 1
		total = 0
		for miniaod in maods:
			sample = miniaod.get_sample()
			lum = sample.luminosity/1000
			total += lum
			href_bit = "\href{https://cmsweb.cern.ch/das/request?view=list\&limit=50\&instance=prod\%2Fglobal\&input=" + latex_escape(urllib.quote(miniaod.name, safe='')) + "}"
			tabular += "\t\t\t" + href_bit + "{\\texttt{" + latex_escape(miniaod.name) + "}} & " + str(lum) + " \\\\\hline\n"
		tabular += "\\multicolumn{1}{|r|}{\\textbf{Total}} & \\textbf{" + "{:.3f}".format(total) + "}\\\\\hline\n"
		if ngroup != len(miniaods): tabular += "\hline\n"
	tabular += "\t\t\end{tabular}\n"
	table += tabular
	table += "\t\label{table:datasets_data}\n\end{table}"
	
#	print table
	with open("tabular_datasets_{}.tex".format(name), "w") as out:
		out.write(tabular)
	with open("table_datasets_{}.tex".format(name), "w") as out:
		out.write(table)
	
	return table


def make_json_table(dss_info, name, caption):
	miniaods = OrderedDict()
	for info in dss_info:
		miniaods[info["process"]] = dataset.fetch_entries("miniaod", query=info)
	
	table = "\\begin{table}[htbp]\n\t\caption{" + caption + "}\n"
	table += "\t\centering\setlength\doublerulesep{0.1in}\n\t\\resizebox{0.9\\textwidth}{!}{\n"
	tabular = "\t\t\\begin{tabular}{|l|l|}\hline\n\t\t\t\\textbf{Run period} & \\textbf{Luminosity mask filename}\\\\\hline\n"
	for key, value in miniaods.items():
		maod = value[0]
		mask_url = maod.mask
		mask_file = mask_url.split("/")[-1]
		nice_name = "2015" if key == "jetht15" else "2016"
		href_bit = "\href{" + mask_url + "}"
		tabular += "\t\t\t" + nice_name + " & " + href_bit + "{\\texttt{" + latex_escape(mask_file) + "}}\\\\\hline\n"
#		tabular += "\\textbf{Total integrated luminosity} & \\\\\hline\n"
	tabular += "\t\t\end{tabular}\n"
	table += tabular
	table += "\t}\n"
	table += "\t\label{table:json}\n"
	table += "\end{table}"
	
	with open("tabular_json_{}.tex".format(name), "w") as out:
		out.write(tabular)
	with open("table_json_{}.tex".format(name), "w") as out:
		out.write(table)
	
	return table


def make_dataset_table_mc(dss_info, name, caption, grouping=True):
	miniaods = OrderedDict()
	for info in dss_info:
		miniaods[info["process"]] = dataset.fetch_entries("miniaod", query=info)
#	print miniaods
	
	table = "\\begin{table}[htbp]\n\t\caption{" + caption + "}\n"
	table += "\t\centering\setlength\doublerulesep{0.1in}\n\t\\resizebox{0.9\\textwidth}{!}{\n"
	tabular = "\t\t\\begin{tabular}{|l|r|r|}\hline\n\t\t\t\\textbf{Dataset name} & \\textbf{Entries} & \\textbf{Cross section [pb]} \\\\\hline\n"
	ngroup = 0
	for key, maods in miniaods.items():
		ngroup += 1
		for miniaod in maods:
			href_bit = "\href{https://cmsweb.cern.ch/das/request?view=list\&limit=50\&instance=prod\%2Fglobal\&input=" + urllib.quote(miniaod.name, safe='').replace("%", "\%") + "}"
			tabular += "\t\t\t\\begin{tabular}{@{}l@{}}" + href_bit + "{\\texttt{/" + latex_escape(miniaod.name.split("/")[1]) + "}} \\\\ " + href_bit + "{\\footnotesize~~\\texttt{/" + "/".join(latex_escape(miniaod.name).split("/")[2:]) + "}}\end{tabular} & " + str(miniaod.n) + " & " + str(miniaod.get_sample().sigma) + " \\\\\hline\n"
		if grouping and ngroup != len(miniaods) and name != "signal": tabular += "\hline\n"
	tabular +="\t\t\end{tabular}\n"
	table += tabular
	table += "\t}\n"
	table += "\t\label{table:datasets_" + name + "}\n"
	table += "\end{table}"
	
#	print table
	with open("tabular_datasets_{}.tex".format(name), "w") as out:
		out.write(tabular)
	with open("table_datasets_{}.tex".format(name), "w") as out:
		out.write(table)
	
	return table

def main():
	make_dataset_table_data(data_info, "data", "JetHT datasets")
	make_json_table(data_info, "data", "CMS data luminosities and masks")
	make_dataset_table_mc(background_info_qcd, "background_qcd", "QCD background Monte Carlo samples")
	make_dataset_table_mc(background_info_other, "background_other", "$\TTBAR$ and bosonic background Monte Carlo samples", grouping=False)
	make_dataset_table_mc(signal_info, "signal", "Signal Monte Carlo samples")
# :FUNCTIONS

# MAIN:
if __name__ == "__main__":
	main()
# :MAIN

