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
	{"wjets", "W #rightarrow jets"},
};

map<TString, TString> groom_names {
	{"f", "filtered"},
	{"p", "pruned"},
	{"s", "soft-dropped"},
	{"t", "trimmed"},
	{"u", "ungroomed"},
};

Double_t get_weight() {
	return (29.128 + 2.183)/2.183;
}
