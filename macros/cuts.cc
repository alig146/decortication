void cuts() {return;}

map<TString, TString> cut_info{
	// (pre) Preselection:
//	{"fjp_pre", "htak8>900&&Max$(m_t)>50&&Min$(pt)>400&&Max$(abs(eta))<2.0"},
	{"fjp_pre", "htak8>900&&Min$(pt)>400&&Max$(abs(eta))<2.0"},
	{"fjp_prehtjec", "htak8jec>945&&Min$(pt)>400&&Max$(abs(eta))<2.0"},
	{"fjp_prehtjec900", "htak8jec>900&&Min$(pt)>400&&Max$(abs(eta))<2.0"},
	
	
	// Single cuts:
	/// (ht):
	{"fjp_ht", "htak8>900"},
	
	/// (tau21):
	{"fjp_tau21", "Max$(tau21)<0.75"},
	
	/// (deta) Mass asymmetry cut:
	{"fjp_deta", "deta<1.0"},
	
	/// (masy) Mass asymmetry cut:
	{"fjp_masy", "masy_p<0.1"},
	
	
	// SIG: Signal region:
	///(sig) Default signal region:
//	{"fjp_sig", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},		// Before tau42 0.45 -> 0.50
//	{"fj_sig", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75"},		// Before tau42 0.45 -> 0.50
	{"fjp_sig", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sig", "tau43[0]<0.80&&tau42[0]<0.50&&tau21[0]<0.75"},
	{"fjp_sigprehtjec", "htak8jec>945&&Min$(pt)>400&&Max$(abs(eta))<2.0&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sigprehtjec900", "htak8jec>900&&Min$(pt)>400&&Max$(abs(eta))<2.0&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	//// (sig15):
	{"fjp_sig15", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1&&run<260628"},
	{"fjp_sig15t", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1&&run<260628&&trig_pfht900"},
	{"fj_sig15", "tau43[0]<0.80&&tau42[0]<0.50&&tau21[0]<0.75&&run<260628"},
	//// (sig16):
	{"fjp_sig16", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1&&run>273157"},
	{"fj_sig16", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75&&run<260628"},
	
	/// (sigx) Signal region n-1 cuts:
	{"fjp_sigxdeta", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sigxmasyp", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75"},
	{"fjp_sigxtau21", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1"},
	{"fjp_sigxtau42", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sigxtau43", "deta<1.0&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sigxtau4", "deta<1.0&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sigxtau", "deta<1.0&&masy_p<0.1"},
	
	/// (sigl) Loose signal region:
	{"fjp_sigl", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sigl", "tau43[0]<0.90&&tau42[0]<0.50&&tau21[0]<0.75"},
	//// (sigl15):
	{"fjp_sigl15", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1&&run<260628"},
	{"fj_sigl15", "tau43[0]<0.90&&tau42[0]<0.50&&tau21[0]<0.75&&run<260628"},
	
	/// (sigs) Include Dalitz var:
	{"fjp_sigs", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1&&Max$(sd)<0.15"},
	{"fj_sigs", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75&&sd[0]<0.15"},
	
	/// (sigp) Use pruned nsubjettiness:
	{"fjp_sigp", "deta<1.0&&Max$(tau43_p)<0.80&&Max$(tau42_p)<0.45&&Max$(tau21_p)<0.75&&masy_p<0.1"},
	{"fj_sigp", "tau43_p[0]<0.80&&tau42_p[0]<0.45&&tau21_p[0]<0.75"},
	
	/// (sigide): Inverted deta cut in signal region:
	{"fjp_sigide", "deta>1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_siglide", "deta>1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	
	/// (sigmsq): Other signal regions based on optimizing for certain mass points:
	{"fjp_sig4075", "deta<1.0&&Max$(tau43)<0.75&&Max$(tau42)<0.40&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig4080", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.40&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig4085", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.40&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig4575", "deta<1.0&&Max$(tau43)<0.75&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig4580", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig5075", "deta<1.0&&Max$(tau43)<0.75&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig5080", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig5580", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.55&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig5585", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.55&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig6085", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.60&&Max$(tau21)<0.75&&masy_p<0.1"},
//	{"fjp_sig500", "deta<1.0&&Max$(tau43)<0.75&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig300", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.40&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sig500", "deta<1.0&&Max$(tau43)<0.725&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	
	/// (siglmasy)
	{"fjp_siglmasy", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.50&&Max$(tau21)<0.75&&masy_p<0.2"},
	
	// SB: Sideband
	/// (sb) Default sideband:
	{"fjp_sbold", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fjp_sb4590", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},		// Before tau42 0.45 -> 0.50
	{"fj_sb4590", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},		// Before tau42 0.45 -> 0.50
	{"fjp_sb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75"},
	{"fjp_sb5590", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sb5590", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75"},
	{"fjp_sb6090", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sb6090", "tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75"},
	{"fjp_sb6095", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sb6095", "tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75"},
	/// (sb15):
	{"fjp_sb15", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&run<260628"},
	{"fj_sb15", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&run<260628"},
	/// (sb16):
	{"fjp_sb16", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&run>273157"},
	{"fj_sb16", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&run>273157"},
	
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
	{"fj_sbl", "tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},
	{"fjp_pretsbl", "htak8>1100&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_pretsbl", "htak8>1100&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},
	
	{"fjp_sbl42", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.60&&Min$(tau42)>0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sbl42", "tau43[0]<0.80&&tau42[0]<0.60&&tau42[0]>0.45&&tau21[0]<0.75"},
	{"fjp_sbl43", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.45&&Min$(tau43)>0.80&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sbl43", "tau43[0]<0.95&&tau42[0]<0.45&&tau43[0]>0.80&&tau21[0]<0.75"},
	
	{"fjp_sbl42b", "deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.60&&Min$(tau42)>0.45&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_sbl42b", "tau43[0]<0.80&&tau42[0]<0.60&&tau42[0]>0.45&&tau21[0]<0.75&&bd[0]>0.5426"},
	{"fjp_sbl43b", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.45&&Min$(tau43)>0.80&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_sbl43b", "tau43[0]<0.95&&tau42[0]<0.45&&tau43[0]>0.80&&tau21[0]<0.75&&bd[0]>0.5426"},
	//// (sbls):
//	{"fjp_sbls", "deta<1.0&&htak8>900&&Max$(m_t)>50&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Max$(sd)<0.15"},
//	{"fj_sbls", "deta<1.0&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&sd[0]<0.15"},
	
	/// (sbt) Tight sideband:
	// Original definition:
	{"fjp_sbt", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.53&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sbt", "tau43[0]<0.85&&tau42[0]<0.53&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75"},
//	{"fjp_sbtorig", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1"},
//	{"fjp_sbt", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1"},
//	{"fj_sbt", "tau43[0]<0.85&&tau42[0]<0.50&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75"},


	{"fjp_sbll", "deta<1.0&&Max$(tau43)>0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&masy_p<0.1"},
	{"fj_sbll", "tau43[0]>0.80&&tau42[0]<0.45&&tau21[0]<0.75"},
	
	// (sbide):
	{"fjp_sbide", "deta>1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75"},
	{"fj_sbide", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75"},
	
	
	// (sblmasy):
	{"fjp_sblmasy", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.2"},
	
	
	// SBB: Sidband, b-tagged:
	/// (sbb) Default b-tagged sideband:
//	{"fjp_sbb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
//	{"fj_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426"},
	{"fjp_sbb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426"},
	
	/// (sbxb):
//	{"fjp_sbxtau21b", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.5426"},
	
	/// (sbsb) b-tagged sideband, Dalitz distance squared:
//	{"fjp_sbsb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426&&Max$(sd)<0.15"},
//	{"fj_sbsb", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426&&sd[0]<0.15"},
//	{"fjp_sbslb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426&&Max$(sd)<0.28"},
//	{"fj_sbslb", "deta<1.0&&tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426&&sd[0]<0.28"},
	
	/// (sblb) Loose b-tagged sideband:
	{"fjp_sblb", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_sblb", "tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426"},
	{"fjp_pretsblb", "htak8>1100&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&((tau42[0]>0.45||tau43[0]>0.80)&&(tau42[1]>0.45||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_pretsblb", "htak8>1100&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426"},
//	{"fjp_sblsb", "deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426&&Max$(sd)<0.15"},
//	{"fj_sblsb", "deta<1.0&&tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426&&sd[0]<0.15"},
//	{"fjp_sblp", "deta<1.0&&Max$(tau43_p)<0.95&&Max$(tau42_p)<0.60&&(Min$(tau42_p)>0.45||Min$(tau43_p)>0.80)&&Max$(tau21_p)<0.75&&masy_p<0.1"},
//	{"fj_sblp", "deta<1.0&&tau43_p[0]<0.95&&tau42_p[0]<0.60&&(tau42_p[0]>0.45||tau43_p[0]>0.80)&&tau21[0]<0.75"},
	
	// (sbtb) Tighter sideband, b-tagged:
	{"fjp_sbtb", "deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.53&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_sbtb", "tau43[0]<0.85&&tau42[0]<0.53&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426"},
	
	
	{"fjp_sbllb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.1&&Min$(bd)>0.5426"},
	{"fj_sbllb", "tau43[0]<0.90&&tau42[0]<0.58&&(tau42[0]>0.50||tau43[0]>0.80)&&tau21[0]<0.75&&bd[0]>0.5426"},
	
	// (sbideb):
	{"fjp_sbideb", "deta>1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&Max$(tau21)<0.75&&Min$(bd)>0.5426"},
	{"fj_sbideb", "tau43[0]<0.80&&tau42[0]<0.45&&tau21[0]<0.75&&bd[0]>0.5426"},
	
	
	// (sblmasyb):
	{"fjp_sblmasyb", "deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&((tau42[0]>0.50||tau43[0]>0.80)&&(tau42[1]>0.50||tau43[1]>0.80))&&Max$(tau21)<0.75&&masy_p<0.2&&Min$(bd)>0.5426"},
	
	
//	// Tuple cuts:
//	{"tuple_presel", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5)"},
//	{"tuple_fjp_sig", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.8&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.45&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1])"},
//	{"tuple_fjp_sbb", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.9&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.9&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.55&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.55&&(((ca12_pf_tau4[0]/ca12_pf_tau3[0])>0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])>0.8)||((ca12_pf_tau4[0]/ca12_pf_tau2[0])>0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])>0.45))&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1]&&ca12_pf_bd_csv[0]>0.5426&&ca12_pf_bd_csv[1]>0.5426)"}
////	{"fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.5426)"},

};

TCut get_cut(TString cut, TString run="xwtt", Double_t weight=1, TString ds="", bool pre=true) {
	// Check if the cut name is valid:
	if (cut_info.find(cut) == cut_info.end()) {
		cout << "[!!] Cut " << cut << " not found!" << endl;
		return TCut(cut, "0");
	}
	
	// Construct cut:
	TCut tcut = TCut(cut, cut_info[cut]);
	
	/// Run range:
	if (run == "15") {
		TCut tcut_range = TCut("15", "run<260628");
		tcut = tcut + tcut_range;
		tcut.SetName(TString(tcut.GetName()) + "15");
	}
	else if (run == "16") {
		TCut tcut_range = TCut("16", "run>273157");
		tcut = tcut + tcut_range;
		tcut.SetName(TString(tcut.GetName()) + "16");
	}
	
	/// Add preselection if asked (default):
	if (pre && cut != "fjp_pre" && cut != "fjp_prehtjec" && cut != "fjp_prehtxjec" && cut != "fjp_sigprehtjec" && cut != "fjp_prehtjec900" && cut != "fjp_sigprehtjec900") {
		TCut tcut_pre = TCut("pre", cut_info["fjp_pre"]);
		tcut = tcut + tcut_pre;
//		cout << tcut_pre.GetTitle() << endl;
//		cout << tcut.GetTitle() << endl;
	}
	
	/// Add weight:
	if (weight != 0) {
		TString weight_string;
		weight_string.Form("%f", weight);
		tcut = tcut * "W" * weight_string;
		if (run == "wtt") tcut = tcut * "W*wtt" * weight_string;
//		else if (run == "wtt") tcut = tcut * "abs(wpu)*w*wtt" * weight_string;
//		else tcut = tcut * "abs(W)" * weight_string;
		
	//	tcut = tcut * "w" * "wtt" * weight_string;		// Old way, can delete
	}
	
	return tcut;
}

TCut get_cut_modified(TString cut, TString add="") {
	// Check if the cut name is valid:
	if (cut_info.find(cut) == cut_info.end()) {
		cout << "[!!] Cut " << cut << " not found!" << endl;
		return TCut(cut, "0");
	}
	
	// Construct cut:
	TCut tcut = TCut(cut, cut_info[cut]);
	TCut tcut_add = TCut("add", add);
	tcut = tcut + tcut_add;
	
	/// Add preselection:
	TCut tcut_pre = TCut("pre", cut_info["fjp_pre"]);
	tcut = tcut + tcut_pre;
	
	return tcut;
}


