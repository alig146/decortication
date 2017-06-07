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
	{"15", "2.2"},
	{"16", "35.5"},
	{"all", "37.7"},
};

Double_t get_weight(TString ds="") {
	if (ds == "jetht" || ds == "15") return 1;
	else return (35.545 + 2.183)/2.183;
//	else return (29.128 + 2.183)/2.183;
}


TFile* get_ana(TString cut="pre") {
	return TFile::Open("~/anatuples/anatuple_cutpt400eta25_prextau.root");		// Contains new preselection (without tau21 and deta) but no dalitz
	
//	if (cut == "sb2") return TFile::Open("~/anatuples/anatuple_ca12_fall15_cutpt400_presel.root");		// 
////	else return TFile::Open("~/anatuples/anatuple_dalitz_predeta.root");		// Contains dalitz variables
//	else return TFile::Open("~/anatuples/anatuple_cutpt400eta25_prextau.root");		// Contains new preselection (without tau21) but no dalitz
}
