# IMPORTS:
from truculence import dataset
# /IMPORTS

# VARIABLES:
ntuple_location = "/eos/uscms/store/user/tote/data/fat"

datasets = {}
# Signals:
## SqToJJJJ:
#datasets["sqtojjjj"] = {
#}
## / SqToJJJJ

## LqToUE:
datasets["lqtoue"] = {
	"spring15": [
		dataset.dataset(
			name_full="/LQToUE_M-200_BetaOne_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=60.6,
			m=200
		),
		dataset.dataset(
			name_full="/LQToUE_M-250_BetaOne_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=20.3,
			m=250,
		),
		dataset.dataset(
			name_full="/LQToUE_M-300_BetaOne_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=8.04,
			m=300,
		),
		dataset.dataset(
			name_full="/LQToUE_M-450_BetaOne_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=0.906,
			m=450,
		),
		dataset.dataset(
			name_full="/LQToUE_M-500_BetaOne_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=0.496,
			m=500,
		),
	],
}
lqtoue_ms = sorted([d.m for d in datasets["lqtoue"]["spring15"]])
## /LqToUE

## LqToTTau:
datasets["lqtottau"] = {
	"spring15": [
		dataset.dataset(
			name_full="/LQLQToTopTau_M-200_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=0.01132,
			m=200,
		),
		dataset.dataset(
			name_full="/LQLQToTopTau_M-300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=0.3178,
			m=300,
		),
		dataset.dataset(
			name_full="/LQLQToTopTau_M-500_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=0.06163,
			m=500,
		),
	],
}
lqtottau_ms = sorted([d.m for d in datasets["lqtottau"]["spring15"]])
## /LqToTTau
# /Signals

# Backgrounds:
## QCD:
datasets["qcd"] = {
	"spring15": [
		dataset.dataset(
			name_full="/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=19204300.0,
			pts=(50, 80),
		),
		dataset.dataset(
			name_full="/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=2762530.0,
			pts=(80, 120),
		),
		dataset.dataset(
			name_full="/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=471100,
			pts=(120, 170),
		),
		dataset.dataset(
			name_full="/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=117276,
			pts=(170, 300),
		),
		dataset.dataset(
			name_full="/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=7823,
			pts=(300, 470),
		),
		dataset.dataset(
			name_full="/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=648.2,
			pts=(470, 600),
		),
		dataset.dataset(
			name_full="/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM",
			sigma=186.9,
			pts=(600, 800),
		),
		dataset.dataset(
			name_full="/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			sigma=32.293,
			pts=(800, 1000),
		),
		dataset.dataset(
			name_full="/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=9.4183,
			pts=(1000, 1400),
		),
		dataset.dataset(
			name_full="/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=0.84265,
			pts=(1400, 1800),
		),
	],
#	"phys14": [
#		"QCD_Pt-50to80_Tune4C_13TeV_pythia8": [22110000.0],
#		"QCD_Pt-80to120_Tune4C_13TeV_pythia8": [3116000.0],
#		"QCD_Pt-120to170_Tune4C_13TeV_pythia8": [486200.0],
#		"QCD_Pt-170to300_Tune4C_13TeV_pythia8": [120300.0],
#		"QCD_Pt-300to470_Tune4C_13TeV_pythia8": [7475.0],
#		"QCD_Pt-470to600_Tune4C_13TeV_pythia8": [587.1],
#		"QCD_Pt-600to800_Tune4C_13TeV_pythia8": [167.0],
#		"QCD_Pt-800to1000_Tune4C_13TeV_pythia8": [28.25],
#		"QCD_Pt-1000to1400_Tune4C_13TeV_pythia8": [8.195],
#		"QCD_Pt-1400to1800_Tune4C_13TeV_pythia8": [0.7346],
#	],
}
qcd_pts = [d.pts for d in datasets["qcd"]["spring15"]]
qcd_pt_mins = sorted([i for i, j in qcd_pts])
## /QCD

## TTbar:
datasets["ttbar"] = {
	"spring15": [
		dataset.dataset(
			name_full="/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			sigma=670.3,
			m=173.34,
		),
	],
}
## /TTbar
# /Backgrounds

processes = [i for i in datasets.keys()]

#samples = {}
#for name, information in info.iteritems():
#	samples[name] = {j: k for key, value in information.iteritems() for j, k in value.iteritems()}		# Combined, single dictionary
#samples["all"] = {}
#for name in info.keys():
#	samples["all"].update(samples[name])

collections = [		# This should match the list that's in FatjetAnalyzer.cc
	"ak8_pf", "ca8_pf", "ak10_pf", "ca10_pf", "ak12_pf", "ca12_pf", "ak14_pf", "ca14_pf",
	"ak8_gn", "ca8_gn", "ak10_gn", "ca10_gn", "ak12_gn", "ca12_gn", "ak14_gn", "ca14_gn",
]
# /VARIABLES

# FUNCTIONS:
def get_datasets(process=None, version=None, m=None, pts=None):
	if m != None:
		return [d for d in datasets[process][version] if d.m == m]
	elif pts != None:
		return [d for d in datasets[process][version] if d.pts == pts]
	else:
		return [d for d in datasets[process][version]]
# /FUNCTIONS
