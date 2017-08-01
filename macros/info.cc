map<TString, TString> name_proper {
	{"sq100to4j", "m_{#tilde{q}} = 100 GeV"},
	{"sq150to4j", "m_{#tilde{q}} = 150 GeV"},
	{"sq200to4j", "m_{#tilde{q}} = 200 GeV"},
	{"sq250to4j", "m_{#tilde{q}} = 250 GeV"},
	{"sq300to4j", "m_{#tilde{q}} = 300 GeV"},
	{"sq400to4j", "m_{#tilde{q}} = 400 GeV"},
	{"sq500to4j", "m_{#tilde{q}} = 500 GeV"},
	{"qcdp", "QCD (2 #rightarrow 2)"},
	{"qcdmg", "QCD (2 #rightarrow 4)"},
	{"ttbar", "t#bar{t}"},
	{"wjets", "W #rightarrow 2q"},
	{"jetht", "JetHT '15 + '16"},
	{"jetht15", "JetHT 2015"},
	{"jetht16", "JetHT 2016"},
};

map<TString, TString> groom_names {
	{"f", "filtered"},
	{"p", "pruned"},
	{"s", "soft-dropped"},
	{"t", "trimmed"},
	{"u", "ungroomed"},
};
map<TString, TString> lum_string {
	{"15", "2.3"},		// 2.258 /fb
	{"16", "35.9"},		// 35.922 /fb
	{"all", "38.2"},		// 38.180 /fb
};

Double_t get_weight(TString ds="", TString era="") {
//	if (ds == "jetht" || ds == "15") return 1;
	if (era == "15") return 2.258/38.180;
	else if (ds == "old") return 38.180/2.183;
	else return 1.0;
}


TFile* get_ana(TString cut="pre") {
	return TFile::Open("~/anatuples/anatuple_cutpt400eta25_pre.root");		// Contains new preselection (without tau21 and deta) but no dalitz
	
//	if (cut == "sb2") return TFile::Open("~/anatuples/anatuple_ca12_fall15_cutpt400_presel.root");		// 
////	else return TFile::Open("~/anatuples/anatuple_dalitz_predeta.root");		// Contains dalitz variables
//	else return TFile::Open("~/anatuples/anatuple_cutpt400eta25_prextau.root");		// Contains new preselection (without tau21) but no dalitz
}
