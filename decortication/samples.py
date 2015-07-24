ntuple_location = "/eos/uscms/store/user/tote/data/fat"

# Signals:
sqtojjjj_info = {}
lqtottau_info = {
	"spring15": {
		"LQLQToTopTau_M-200_TuneCUETP8M1_13TeV_pythia8": [
			"/LQLQToTopTau_M-200_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			0.01132,
			200,
		],
		"LQLQToTopTau_M-300_TuneCUETP8M1_13TeV_pythia8": [
			"/LQLQToTopTau_M-300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			0.3178,
			300,
		],
		"LQLQToTopTau_M-500_TuneCUETP8M1_13TeV_pythia8": [
			"/LQLQToTopTau_M-500_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			0.06163,
			500,
		],
	},
}

# Backgrounds:
qcd_info = {
	"spring15": {
		"QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			19204300.0,
			(50, 80),
		],
		"QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			2762530.0,
			(80, 120),
		],
		"QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			471100,
			(120, 170),
		],
		"QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			117276,
			(170, 300),
		],
		"QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			7823,
			(300, 470),
		],
		"QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			648.2,
			(470, 600),
		],
		"QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM",
			186.9,
			(600, 800),
		],
		"QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM",
			32.293,
			(800, 1000),
		],
		"QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			9.4183,
			(1000, 1400),
		],
		"QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8": [
			"/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			0.84265,
			(1400, 1800),
		],
	},
	"phys14": {
		"QCD_Pt-50to80_Tune4C_13TeV_pythia8": [22110000.0],
		"QCD_Pt-80to120_Tune4C_13TeV_pythia8": [3116000.0],
		"QCD_Pt-120to170_Tune4C_13TeV_pythia8": [486200.0],
		"QCD_Pt-170to300_Tune4C_13TeV_pythia8": [120300.0],
		"QCD_Pt-300to470_Tune4C_13TeV_pythia8": [7475.0],
		"QCD_Pt-470to600_Tune4C_13TeV_pythia8": [587.1],
		"QCD_Pt-600to800_Tune4C_13TeV_pythia8": [167.0],
		"QCD_Pt-800to1000_Tune4C_13TeV_pythia8": [28.25],
		"QCD_Pt-1000to1400_Tune4C_13TeV_pythia8": [8.195],
		"QCD_Pt-1400to1800_Tune4C_13TeV_pythia8": [0.7346],
	},
}
ttbar_info = {
	"spring15": {
		"TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8": [
			"/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM",
			670.3
		],
	},
}

qcd_samples = {j: k for key, value in qcd_info.iteritems() for j, k in value.iteritems()}		# Combined, single dictionary
ttbar_samples = {j: k for key, value in ttbar_info.iteritems() for j, k in value.iteritems()}
lqtottau_samples = {j: k for key, value in lqtottau_info.iteritems() for j, k in value.iteritems()}
samples = {}
samples.update(qcd_samples)
samples.update(ttbar_samples)
samples.update(lqtottau_samples)

collections = [		# This should match the list that's in FatjetAnalyzer.cc
	"ak8_pf", "ca8_pf", "ak10_pf", "ca10_pf", "ak12_pf", "ca12_pf", "ak14_pf", "ca14_pf",
	"ak8_gn", "ca8_gn", "ak10_gn", "ca10_gn", "ak12_gn", "ca12_gn", "ak14_gn", "ca14_gn",
]
