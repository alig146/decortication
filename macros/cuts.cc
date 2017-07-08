void cuts() {return;}

map<TString, TString> cut_info{
	// (pre) Preselection:
	{"fjp_pre", "htak8>900&&Max$(m_t)>50&&Min$(pt)>400&&Max$(abs(eta))<2.0"},
	
	
	// Single cuts:
	/// (tau21):
	{"fjp_tau21", "Max$(tau21)<0.75"},
	
	/// (deta) Mass asymmetry cut:
	{"fjp_deta", "deta<1.0"},
	
	/// (masy) Mass asymmetry cut:
	{"fjp_masy", "masy_p<0.1"},
	
	
	// SIG: Signal region:
	///(sig) Default signal region:
	{"fjp_sig", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sig", "deta<1.0&&tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75"},
	//// (sig15):
	{"fjp_sig15", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1&&run<260628"},
	{"fj_sig15", "deta<1.0&&tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75&&run<260628"},
	
	/// (sigx) Signal region n-1 cuts:
	{"fjp_sigxdeta", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sigxmasyp", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75"},
	{"fjp_sigxtau21", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1"},
	{"fjp_sigxtau", "deta<1.0&&Max$(tau21)<0.75&&masy_p<0.1"},
	
	/// (sigl) Loose signal region:
	{"fjp_sigl", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sigl", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.50&&tau21[0]<0.75"},
	//// (sigl15):
	{"fjp_sigl15", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1&&run<260628"},
	{"fj_sigl15", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.50&&tau21[0]<0.75&&run<260628"},
	
	/// (sigs) Include Dalitz var:
	{"fjp_sigs", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1&&Max$(sd)<0.15"},
	{"fj_sigs", "deta<1.0&&tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75&&sd[0]<0.15"},
	
	/// (sigp) Use pruned nsubjettiness:
	{"fjp_sigp", "deta<1.0&&Max$(tau43_p)<0.80&&Max$(tau42_p)<0.45&&Max$(tau21_p)<0.75&&masy_p<0.1"},
	{"fj_sigp", "deta<1.0&&tau43_p[0]<0.80&&tau42_p[0]<0.45&&tau21_p[0]<0.75"},
	
	/// (sigide): Inverted deta cut in signal region:
	{"fjp_sigide", "deta>1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21_p)<0.75&&masy_p<0.1"},
	{"fjp_siglide", "deta>1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&Max$(tau21_p)<0.75&&masy_p<0.1"},
	
	
	// SB: Sideband
	/// (sb) Default sideband:
	{"fjp_sbold", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sb", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},
	
	/// (sbx) Sideband n-1 cuts:
//	{"fjp_sbxdeta", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1"},
//	{"fjp_sbxtau21", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1"},
	
	/// (sbs) Sideband, Dalitz distance squared:
//	{"fjp_sbs", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Max$(sd)<0.15"},
//	{"fj_sbs", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&sd[0]<0.15"},
	
	/// (sbp) Sideband, pruned taus
//	{"fjp_sbp", "deta<1.0&&Max$(tau43_p)<0.90&&Max$(tau42_p)<0.55&&(Min$(tau42_p)>0.45||Min$(tau43_p)>0.80)&&Max$(tau21_p)<0.75&&masy_p<0.1"},
//	{"fj_sbp", "deta<1.0&&tau43_p[0]<0.90&&tau42_p[0]<0.55&&(tau42_p[0]>0.45||tau43_p[0]>0.80)&&tau21_p[0]<0.75"},
	
	/// (sbl) Loose sideband:
	{"fjp_sblold", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sbl", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sbl", "deta<1.0&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},
	//// (sbls):
//	{"fjp_sbls", "deta<1.0&&htak8>900&&Max$(m_t)>50&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Max$(sd)<0.15"},
//	{"fj_sbls", "deta<1.0&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&sd[0]<0.15"},
	
	/// (sbt) Tight sideband:
	{"fjp_sbtold", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sbt", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sbt", "deta<1.0&&tau43[0]<0.85&&tau42[0]<0.50&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},
	
	// (sbide):
	{"fjp_sbide", "deta>1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21_p)<0.75"},
	{"fj_sbide", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75"},
	
	
	// SBB: Sidband, b-tagged:
	/// (sbb) Default b-tagged sideband:
	{"fjp_sbb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.46"},
	{"fj_sbb", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.46"},
	
	/// (sbxb):
//	{"fjp_sbxtau21b", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46"},
	
	/// (sbsb) b-tagged sideband, Dalitz distance squared:
//	{"fjp_sbsb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.46&&Max$(sd)<0.15"},
//	{"fj_sbsb", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.46&&sd[0]<0.15"},
//	{"fjp_sbslb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.46&&Max$(sd)<0.28"},
//	{"fj_sbslb", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.46&&sd[0]<0.28"},
	
	/// (sblb) Loose b-tagged sideband:
	{"fjp_sblb", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.46"},
	{"fj_sblb", "deta<1.0&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.46"},
//	{"fjp_sblsb", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.46&&Max$(sd)<0.15"},
//	{"fj_sblsb", "deta<1.0&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.46&&sd[0]<0.15"},
//	{"fjp_sblp", "deta<1.0&&Max$(tau43_p)<0.95&&Max$(tau42_p)<0.60&&(Min$(tau42_p)>0.45||Min$(tau43_p)>0.80)&&Max$(tau21_p)<0.75&&masy_p<0.1"},
//	{"fj_sblp", "deta<1.0&&tau43_p[0]<0.95&&tau42_p[0]<0.60&&(tau42_p[0]>0.45||tau43_p[0]>0.80)&&tau21[0]<0.75"},
	
	// (sbtb) Tighter sideband, b-tagged:
	{"fjp_sbtb", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21_p)<0.75&&masy_p<0.1&&Min$(bd)>0.46"},
	{"fj_sbtb", "deta<1.0&&tau43[0]<0.85&&tau42[0]<0.50&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.46"},
	
	// (sbideb):
	{"fjp_sbideb", "deta>1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21_p)<0.75&&Min$(bd)>0.46"},
	{"fj_sbideb", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75&&bd[0]>0.46"},
	
//	// Tuple cuts:
//	{"tuple_presel", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5)"},
//	{"tuple_fjp_sig", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.8&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.45&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1])"},
//	{"tuple_fjp_sbb", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.9&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.9&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.55&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.55&&(((ca12_pf_tau4[0]/ca12_pf_tau3[0])>0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])>0.8)||((ca12_pf_tau4[0]/ca12_pf_tau2[0])>0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])>0.45))&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1]&&ca12_pf_bd_csv[0]>0.46&&ca12_pf_bd_csv[1]>0.46)"}
////	{"fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
};

TCut get_cut(TString cut, Double_t weight=1, bool pre=true) {
	// Check if the cut name is valid:
	if (cut_info.find(cut) == cut_info.end()) {
		cout << "[!!] Cut " << cut << " not found!" << endl;
		return TCut(cut, "0");
	}
	
	// Construct cut:
	TCut tcut = TCut(cut, cut_info[cut]);
	
	/// Add preselection if asked (default):
	if (pre && cut != "fjp_pre") {
		TCut tcut_pre = TCut("pre", cut_info["fjp_pre"]);
		tcut = tcut + tcut_pre;
//		cout << tcut_pre.GetTitle() << endl;
//		cout << tcut.GetTitle() << endl;
	}
	
	/// Add weight:
	TString weight_string;
	weight_string.Form("%f", weight);
	tcut = tcut * "w" * "wtt" * weight_string;
	
	return tcut;
}


