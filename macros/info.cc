map<TString, TString> name_proper {
	{"sq100to4j", "#it{m}_{#tilde{q}} = 100 GeV"},
	{"sq150to4j", "#it{m}_{#tilde{q}} = 150 GeV"},
	{"sq200to4j", "#it{m}_{#tilde{q}} = 200 GeV"},
	{"sq250to4j", "#it{m}_{#tilde{q}} = 250 GeV"},
	{"sq300to4j", "#it{m}_{#tilde{q}} = 300 GeV"},
	{"sq400to4j", "#it{m}_{#tilde{q}} = 400 GeV"},
	{"sq500to4j", "#it{m}_{#tilde{q}} = 500 GeV"},
	{"qcdp", "QCD (2 #rightarrow 2)"},
	{"qcdmg", "QCD (2 #rightarrow 4)"},
	{"ttbar", "t#bar{t}"},
	{"wjets", "W #rightarrow 2q"},
	{"jetht", "JetHT '15 + '16"},
	{"jetht15", "JetHT 2015"},
	{"jetht16", "JetHT 2016"},
	{"all", "Total MC"},
	{"inj", "JetHT + #it{m}_{#tilde{q}} = 150 GeV"},
};

map<TString, TString> variable_proper {
	{"ht", "#it{H}_{T}"},
	{"msq", "#it{m}_{#tilde{q}}"},
	{"m0", "#it{m} of leading fatjet"},
	{"mavg", "#bar{#it{m}}"},
	{"mavgp", "#bar{#it{m}}"},
	{"deta", "#left|#Delta#eta#right|"},
	{"masy", "#it{A}_{#it{m}}"},
	{"masyp", "#it{A}_{#it{m}}"},
	{"tau21", "max#left(#tau_{21}#right)"},
	{"tau42", "max#left(#tau_{42}#right)"},
	{"tau43", "max#left(#tau_{43}#right)"},
	{"eta", "#eta"},
	{"eta0", "#eta of leading fatjet"},
	{"phi0", "#phi of leading fatjet"},
	{"pt0", "#it{p}_{T} of leading fatjet"},
	{"tau210", "#tau_{21} of the leading fatjet"},
	{"tau420", "#tau_{42} of the leading fatjet"},
	{"tau430", "#tau_{43} of the leading fatjet"},
};

map<TString, TString> unit_proper {
	{"ht", "GeV"},
	{"msq", "GeV"},
	{"m0", "GeV"},
	{"mavg", "GeV"},
	{"mavgp", "GeV"},
	{"deta", ""},
	{"masy", ""},
	{"masyp", ""},
	{"tau21", ""},
	{"tau42", ""},
	{"tau43", ""},
	{"eta0", ""},
	{"phi0", ""},
	{"pt0", "GeV"},
	{"tau210", ""},
	{"tau420", ""},
	{"tau430", ""},
};

map<TString, TString> cut_proper {
	{"sig", "signal region"},
	{"sigxdeta", "#it{N}-1 (signal region)"},
	{"sigxmasyp", "#it{N}-1 (signal region)"},
	{"sigxtau21", "#it{N}-1 (signal region)"},
	{"sigxtau42", "#it{N}-1 (signal region)"},
	{"sigxtau43", "#it{N}-1 (signal region)"},
	{"sigl", "loose signal region"},
	{"sb", "control region"},
	{"sbb", "b-tagged control region"},
	{"sbl", "loose control region"},
	{"sblb", "b-tagged loose control region"},
	{"sbl42", "loose-#tau_{42} control region"},
	{"sbl42b", "b-tagged loose-#tau_{42} control region"},
	{"sbl43", "loose-#tau_{43} control region"},
	{"sbl43b", "b-tagged loose-#tau_{43} control region"},
	{"sbide", "inverted-#Delta#eta control region"},
	{"sbideb", "b-tagged inverted-#Delta#eta control region"},
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
	{"sum", "(2.3 + 35.9)"},
	{"all", "38.2"},		// 38.180 /fb
};

TString get_xtitle(TString var) {
	TString title = variable_proper[var];
	TString unit = unit_proper[var];
	if (unit != "") title += " [" + unit + "]";
	return title;
}

Double_t get_weight(TString ds="", TString era="") {
	if (ds == "jetht") return 1;
	else if (era == "15") return 2.258/38.180;
	else if (ds == "old") return 38.180/2.183;
	else return 1.0;
}


TFile* get_ana(TString cut="pre") {
	return TFile::Open("~/anatuples/anatuple_cutpt400eta25_pre.root");		// Contains new preselection (without tau21 and deta) but no dalitz
	
//	if (cut == "sb2") return TFile::Open("~/anatuples/anatuple_ca12_fall15_cutpt400_presel.root");		// 
////	else return TFile::Open("~/anatuples/anatuple_dalitz_predeta.root");		// Contains dalitz variables
//	else return TFile::Open("~/anatuples/anatuple_cutpt400eta25_prextau.root");		// Contains new preselection (without tau21) but no dalitz
}
