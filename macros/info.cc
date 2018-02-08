vector<TString> names_sig = {"sq100to4j", "sq150to4j", "sq200to4j", "sq250to4j", "sq300to4j", "sq400to4j", "sq500to4j"};
vector<int> masses_sig = {100, 150, 200, 250, 300, 400, 500};

map<TString, TString> name_proper {
	{"sq100to4j", "#it{m}_{#tilde{q}} = 100 GeV"},
	{"sq150to4j", "#it{m}_{#tilde{q}} = 150 GeV"},
	{"sq173to4j", "#it{m}_{#tilde{q}} = 173 GeV"},
	{"sq175to4j", "#it{m}_{#tilde{q}} = 175 GeV"},
	{"sq200to4j", "#it{m}_{#tilde{q}} = 200 GeV"},
	{"sq250to4j", "#it{m}_{#tilde{q}} = 250 GeV"},
	{"sq300to4j", "#it{m}_{#tilde{q}} = 300 GeV"},
	{"sq400to4j", "#it{m}_{#tilde{q}} = 400 GeV"},
	{"sq500to4j", "#it{m}_{#tilde{q}} = 500 GeV"},
	{"sq600to4j", "#it{m}_{#tilde{q}} = 600 GeV"},
	{"sq700to4j", "#it{m}_{#tilde{q}} = 700 GeV"},
	{"sg100to5j", "#it{m}_{#tilde{g}} = 100 GeV"},
	{"sg150to5j", "#it{m}_{#tilde{g}} = 150 GeV"},
	{"sg175to5j", "#it{m}_{#tilde{g}} = 175 GeV"},
	{"sg200to5j", "#it{m}_{#tilde{g}} = 200 GeV"},
	{"sg250to5j", "#it{m}_{#tilde{g}} = 250 GeV"},
	{"sg300to5j", "#it{m}_{#tilde{g}} = 300 GeV"},
	{"sg350to5j", "#it{m}_{#tilde{g}} = 350 GeV"},
	{"sg400to5j", "#it{m}_{#tilde{g}} = 400 GeV"},
	{"sg450to5j", "#it{m}_{#tilde{g}} = 450 GeV"},
	{"sg500to5j", "#it{m}_{#tilde{g}} = 500 GeV"},
	{"sg550to5j", "#it{m}_{#tilde{g}} = 550 GeV"},
	{"sg600to5j", "#it{m}_{#tilde{g}} = 600 GeV"},
	{"sg650to5j", "#it{m}_{#tilde{g}} = 650 GeV"},
	{"qcdp", "QCD (2 #rightarrow 2)"},
	{"qcdmg", "QCD (2 #rightarrow 4)"},
	{"ttbar", "t#bar{t}"},
	{"wjets", "W #rightarrow 2q"},
	{"jetht", "JetHT '15 + '16"},
	{"jetht15", "JetHT 2015"},
	{"jetht16", "JetHT 2016"},
	{"all", "Total MC"},
	{"inj", "JetHT + #it{m}_{#tilde{q}} = 150 GeV"},
	{"data", "Data"},
	{"data15", "Data (2015)"},
};

map<TString, TString> variable_proper {
	{"ht", "#it{H}_{T}"},
	{"m", "mass"},
	{"msq", "#it{m}_{#tilde{q}}"},
	{"msg", "#it{m}_{#tilde{g}}"},
	{"m0", "#it{m} of leading fatjet"},
	{"m0ak8", "#it{m} of leading AK8 jet"},
	{"m0ca12", "#it{m} of leading CA12 jet"},
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
	{"pt", "#it{p}_{T}"},
	{"pt0", "#it{p}_{T} of leading fatjet"},
	{"ptsq0", "#it{p}_{T} of leading squark"},
	{"tau210", "#tau_{21} of the leading fatjet"},
	{"tau420", "#tau_{42} of the leading fatjet"},
	{"tau430", "#tau_{43} of the leading fatjet"},
};

map<TString, TString> unit_proper {
	{"ht", "GeV"},
	{"m", "GeV"},
	{"msq", "GeV"},
	{"msg", "GeV"},
	{"m0", "GeV"},
	{"m0ak8", "GeV"},
	{"m0ca12", "GeV"},
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
	{"pt", "GeV"},
	{"pt0", "GeV"},
	{"ptsq0", "GeV"},
	{"tau210", ""},
	{"tau420", ""},
	{"tau430", ""},
};

vector<TString> significance_proper {
	"",
	"s/#sqrt{b}",
	"s/#sqrt{s + b}",
	"#sqrt{s + b} - #sqrt{b}",
	"#it{Z}_{bi}"
};

map<TString, TString> cut_proper {
	{"pre", "pre-selection"},
	{"ht945", "#it{H}_{T} > 945 GeV"},
	{"ht900", "#it{H}_{T} > 900 GeV"},
	{"ht850", "#it{H}_{T} > 850 GeV"},
	{"sig", "signal region"},
	{"SR", "signal region"},
	{"sigxdeta", "#it{N}-1 (signal region)"},
	{"sigxmasyp", "#it{N}-1 (signal region)"},
	{"sigxtau21", "#it{N}-1 (signal region)"},
	{"sigxtau42", "#it{N}-1 (signal region)"},
	{"sigxtau43", "#it{N}-1 (signal region)"},
	{"sigxtau4", "before #tau_{4} cuts"},
	{"sigl", "loose signal region"},
	{"sb", "control region"},
	{"sbinj", "control region"},
	{"SB", "control region"},
	{"sbb", "b-tagged control region"},
	{"sbbinj", "b-tagged control region"},
	{"sbt", "tight control region"},
	{"sbtb", "b-tagged tight control region"},
	{"sbl", "loose control region"},
	{"sblb", "b-tagged loose control region"},
	{"sbl42", "loose-#tau_{42} control region"},
	{"sbl42b", "b-tagged loose-#tau_{42} control region"},
	{"sbl43", "loose-#tau_{43} control region"},
	{"sbl43b", "b-tagged loose-#tau_{43} control region"},
	{"sbide", "inverted-#Delta#eta control region"},
	{"sbideb", "b-tagged inverted-#Delta#eta control region"},
	{"pretsbl", "loose CR w/ #it{H}_{T} > 1100 GeV"},
	{"pretsblb", "b-tagged loose CR w/ #it{H}_{T} > 1100 GeV"},
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
	{"16e", "4.0"},
	{"16f", "3.1"},
	{"16ef", "7.1"},
	{"sum", "(2.3 + 35.9)"},
	{"all", "38.2"},		// 38.180 /fb
};

TString get_xtitle(TString var) {
	TString title = variable_proper[var];
	TString unit = unit_proper[var];
	if (unit != "") title += "  [" + unit + "]";
	return title;
}

void set_xtitle(TH1* h, TString var) {
	h->GetXaxis()->SetTitle(get_xtitle(var));
}
void set_xtitle(TGraph* g, TString var) {
	g->GetXaxis()->SetTitle(get_xtitle(var));
}
void set_xtitle(THStack* hs, TString var) {
	hs->GetXaxis()->SetTitle(get_xtitle(var));
}


void set_title(TH1* h, TString var_x, TString var_y="Events") {
	// Plot title:
	h->SetTitle("");
	
	// x-title:
	set_xtitle(h, var_x);
	
	// y-title:
	TString unit_x = unit_proper[var_x];
	std::ostringstream oss;
	oss << var_y << "/" << h->GetXaxis()->GetBinWidth(1) << " " << unit_x;
	h->GetYaxis()->SetTitle(oss.str().c_str());
}


Double_t get_weight(TString ds="", TString era="") {
	if (ds == "jetht") return 1.0;
	else if (era == "15") return 2.258/38.180;
	else if (ds == "old") return 38.180/2.183;
	else return 1.0;
}


TFile* get_ana(TString option="") {
	if (option == "xpu") return TFile::Open("~/anatuples/anatuple_cutpt400eta25_pre.root.xpu");
	else if (option == "sq100") return TFile::Open("~/anatuples/anatuple_sq100to4j_cutpt300eta20_pre.root");
	else if (option == "bosons") return TFile::Open("~/anatuples/anatuple_vbosons_moriond17_cutpt400eta25_pre.root");
	else if (option == "qcdp") return TFile::Open("~/anatuples/anatuple_qcdp_moriond17_cutpt300eta20_pre.root");
	else if (option == "ttbarhg") return TFile::Open("~/anatuples/anatuple_ttbarhg_moriond17_cutpt300eta20_pre.root");
	else if (option == "qcdmgext") return TFile::Open("~/anatuples/temp/anatuple_qcdmg_moriond17_cutpt400eta25_pre.root");
	else if (option == "sqto4j") return TFile::Open("~/anatuples/anatuple_sqto4j_moriond17cutht700_cutpt300eta20.root");
	else if (option == "sqto4jprehtjec") return TFile::Open("~/anatuples/anatuple_sqto4j_moriond17cutht700_cutpt300eta20_prehtjec.root");
	else if (option == "sgto5j") return TFile::Open("~/anatuples/anatuple_sgto5j_moriond17cutht500_cutpt300eta20.root");
	else if (option == "sgto5jprehtjec") return TFile::Open("~/anatuples/anatuple_sgto5j_moriond17cutht500_cutpt300eta20_prehtjec.root");
	else if (option == "wzjets") return TFile::Open("~/anatuples/anatuple_wzjets_moriond17_cutpt300eta20_pre.root");
	else if (option == "sigxtau4") return TFile::Open("~/anatuples/anatuple_cutpt400eta25_pre_sigxtau4.root");
	else if (option == "v6") return TFile::Open("~/anatuples/anatuple_cutpt400eta25_pre.root.bkp");
	else return TFile::Open("~/anatuples/anatuple_cutpt300eta20_pre.root");
	
//	if (cut == "sb2") return TFile::Open("~/anatuples/anatuple_ca12_fall15_cutpt400_presel.root");		// 
////	else return TFile::Open("~/anatuples/anatuple_dalitz_predeta.root");		// Contains dalitz variables
//	else return TFile::Open("~/anatuples/anatuple_cutpt400eta25_prextau.root");		// Contains new preselection (without tau21) but no dalitz
}


bool is_sig(TString name) {
	for (unsigned i = 0; i < names_sig.size(); ++i) {
		if (name == names_sig[i]) return true;
	}
	return false;
}

TString get_path(TString package="decortication") {
	return TString(getenv("CMSSW_BASE")) + "/src/Deracination/Straphanger/test/" + package + "/macros/";
}

