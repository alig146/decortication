void cuts() {return;}

//// Loose signal region:

//// Signal region:
//TCut* cut_fjp_sig() {return new TCut("cut_fjp_sig", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)");}
//TCut* cut_fjp_mc_sig() {return new TCut("cut_fjp_mc_sig", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)");}
//TCut* cut_fjp_data_sig() {return new TCut("cut_fjp_data_sig", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1");}
//TCut* cut_fj_sig() {return new TCut("cut_fj_sig", "w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_mc_sig() {return new TCut("cut_fj_mc_sig", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_data_sig() {return new TCut("cut_fj_data_sig", "tau43[0]<0.80&&tau42[0]<0.45");}

//// Sideband (inclusive):
////TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1)");}
////TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1)");}
////TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1");}
////TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58)");}
////TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58)");}
////TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58");}

////TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1)");}
////TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1)");}
////TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1");}
////TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60)");}
////TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60)");}
////TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60");}

////TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1)");}
////TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1)");}
////TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1");}
////TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60)");}
////TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60)");}
////TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60");}

////TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
////TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
////TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1");}
////TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80))");}
////TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80))");}
////TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)");}

//TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
//TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
//TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1");}
//TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))");}
//TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))");}
//TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)");}


//// Sideband (b-tagged):
////TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1&&Min$(bd)>0.46");}
////TCut* cut_fj_sbb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58&&bd[0]>0.46)");}
////TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58&&bd[0]>0.46)");}
////TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58&&bd[0]>0.46");}

////TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46");}
////TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60&&bd[0]>0.46)");}
////TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60&&bd[0]>0.46)");}
////TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60&&bd[0]>0.46");}

////TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46");}
////TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
////TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
////TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46");}

////TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46");}
////TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
////TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
////TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46");}

//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46");}

////// NEW tuples:
////TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.43||Min$(tau43)>0.75)&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.43||Min$(tau43)>0.75)&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.43||Min$(tau43)>0.75)&&masy_p<0.1&&Min$(bd)>0.46");}
////TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.43||tau43[0]>0.75)&&bd[0]>0.46)");}
////TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.43||tau43[0]>0.75)&&bd[0]>0.46)");}
////TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.43||tau43[0]>0.75)&&bd[0]>0.46");}




////TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
////TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46");}
////TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
////TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
////TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46");}






//TCut* cut_fjp_sb2() {return new TCut("cut_fjp_sb2", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0)");}
//TCut* cut_fjp_mc_sb2() {return new TCut("cut_fjp_mc_sb2", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0)");}
//TCut* cut_fjp_data_sb2() {return new TCut("cut_fjp_data_sb2", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0");}
//TCut* cut_fj_sb2() {return new TCut("cut_fj_sb2", "w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_mc_sb2() {return new TCut("cut_fj_mc_sb2", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_data_sb2() {return new TCut("cut_fj_data_sb2", "tau43[0]<0.80&&tau42[0]<0.45");}

//TCut* cut_fjp_sb2b() {return new TCut("cut_fjp_sb2b", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sb2b() {return new TCut("cut_fjp_mc_sb2b", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sb2b() {return new TCut("cut_fjp_data_sb2b", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0&&Min$(bd)>0.46");}
//TCut* cut_fj_sb2b() {return new TCut("cut_fj_sb2b", "w*(tau43[0]<0.80&&tau42[0]<0.45&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sb2b() {return new TCut("cut_fj_mc_sb2b", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45&&bd[0]>0.46)");}
//TCut* cut_fj_data_sb2b() {return new TCut("cut_fj_data_sb2b", "tau43[0]<0.80&&tau42[0]<0.45&&bd[0]>0.46");}

//TCut* cut_fjp_sb22() {return new TCut("cut_fjp_sb22", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&deta>1.0)");}
//TCut* cut_fjp_mc_sb22() {return new TCut("cut_fjp_mc_sb22", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&deta>1.0)");}
//TCut* cut_fjp_data_sb22() {return new TCut("cut_fjp_data_sb22", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&deta>1.0");}
//TCut* cut_fj_sb22() {return new TCut("cut_fj_sb22", "w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_mc_sb22() {return new TCut("cut_fj_mc_sb22", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_data_sb22() {return new TCut("cut_fj_data_sb22", "tau43[0]<0.80&&tau42[0]<0.45");}

//TCut* cut_fjp_sb3() {return new TCut("cut_fjp_sb3", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p>0.12)");}
//TCut* cut_fjp_mc_sb3() {return new TCut("cut_fjp_mc_sb3", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p>0.12)");}
//TCut* cut_fjp_data_sb3() {return new TCut("cut_fjp_data_sb3", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p>0.12");}
//TCut* cut_fj_sb3() {return new TCut("cut_fj_sb3", "w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_mc_sb3() {return new TCut("cut_fj_mc_sb3", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)");}
//TCut* cut_fj_data_sb3() {return new TCut("cut_fj_data_sb3", "tau43[0]<0.80&&tau42[0]<0.45");}

//TCut* cut_tuple_fjp_sig() {return new TCut("cut_tuple_fjp_sig", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.8&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.45&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1])");}




map<TString, TString> cut_info{
	// (pre) Preselection:
	{"fjp_pre", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5)"},
	
	// (deta Mass asymmetry cut:
	{"fjp_deta", "w*(deta<1.0)"},
	{"fjp_deta_ttbar", "wtt*w*(deta<1.0)"},
	
	// (masy) Mass asymmetry cut:
	{"fjp_masy", "w*(masy_p<0.1)"},
	
	// (sigxtau) Signal region without tau cuts:
//	{"fjp_sigxtau", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&masy_p<0.1)"},
	{"fjp_sigxtau", "wtt*w*(deta<1.0&&masy_p<0.1)"},
	
	{"fjp_sigxmasyp", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45)"},
	
	// (sig) Signal region:
//	{"fjp_sig", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_sig", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_sig_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_mc_sig", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_data_sig", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1"},
	{"fj_sig", "w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_mc_sig", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_data_sig", "tau43[0]<0.80&&tau42[0]<0.45"},
	
	// (sigl) Loose signal region:
	
	{"fjp_sigl", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1)"},
	{"fjp_sigl_ttbar", "wtt*w*(Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1)"},
	{"fjp_siglxmasyp", "wtt*w*(Max$(tau43)<0.90&&Max$(tau42)<0.50)"},
	{"fj_sigl", "w*(tau43[0]<0.90&&tau42[0]<0.50)"},
	
	{"fjp_sigs", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&Max$(sd)<0.15)"},
	{"fj_sigs", "w*(tau43[0]<0.80&&tau42[0]<0.45&&sd[0]<0.15)"},
	
	// (sigp)
	{"fjp_sigp", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43_p)<0.80&&Max$(tau42_p)<0.45&&masy_p<0.1)"},
	{"fjp_sigp_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43_p)<0.80&&Max$(tau42_p)<0.45&&masy_p<0.1)"},
	{"fj_sigp", "w*(tau43_p[0]<0.80&&tau42_p[0]<0.45)"},
	
	// (sb) Sideband:
	{"fjp_sb", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_sbm", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&mavg_p<150&&mavg_p>100)"},
	{"fjp_sb_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_sb_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_sb_t", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_t<0.1)"},
	{"fjp_mc_sb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
//	{"fjp_data_sb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1"},
	{"fj_sb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))"},
	{"fj_mc_sb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))"},
//	{"fj_data_sb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)"},
	
	{"fjp_sbs", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Max$(sd)<0.15)"},
	{"fjp_sbs_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Max$(sd)<0.15)"},
	{"fj_sbs", "wtt*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&sd[0]<0.15)"},
	
	{"fjp_sbp", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43_p)<0.90&&Max$(tau42_p)<0.55&&(Min$(tau42_p)>0.45||Min$(tau43_p)>0.80)&&masy_p<0.1)"},
	{"fjp_sbp_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43_p)<0.90&&Max$(tau42_p)<0.55&&(Min$(tau42_p)>0.45||Min$(tau43_p)>0.80)&&masy_p<0.1)"},
	{"fj_sbp", "w*(tau43_p[0]<0.90&&tau42_p[0]<0.55&&(tau42_p[0]>0.45||tau43_p[0]>0.80))"},
	
	// (sbb) b-tagged sideband:
	{"fjp_sbb", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbb_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbb_f", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_f<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbb_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbb_s", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_s<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbb_t", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_t<0.1&&Min$(bd)>0.46)"},
//	{"fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
//	{"fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46"},
	{"fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)"},
//	{"fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)"},
//	{"fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46"},
	
	{"fjp_sbsb", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46&&Max$(sd)<0.15)"},
	{"fjp_sbsb_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46&&Max$(sd)<0.15)"},
	{"fj_sbsb", "wtt*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46&&sd[0]<0.15)"},
	
	{"fjp_sblsb_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46&&Max$(sd)<0.28)"},
	{"fj_sblsb", "wtt*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46&&sd[0]<0.28)"},
	
	// (sbl) Looser sideband:
	{"fjp_sbl", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_sbl_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
//	{"fjp_mc_sbl", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
//	{"fjp_data_sbl", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1"},
	{"fj_sbl", "w*(tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80))"},
//	{"fj_mc_sbl", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))"},
//	{"fj_data_sbl", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)"},
	
	{"fjp_sblp", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43_p)<0.95&&Max$(tau42_p)<0.60&&(Min$(tau42_p)>0.45||Min$(tau4_p3)>0.80)&&masy_p<0.1)"},
	{"fjp_sblp_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43_p)<0.95&&Max$(tau42_p)<0.60&&(Min$(tau42_p)>0.45||Min$(tau43_p)>0.80)&&masy_p<0.1)"},
	{"fj_sblp", "w*(tau43_p[0]<0.95&&tau42_p[0]<0.60&&(tau42_p[0]>0.45||tau43_p[0]>0.80))"},
	
	// (sblb) Looser sideband, b-tagged:
	{"fjp_sblb", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_sblb_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.95&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fj_sblb", "w*(tau43[0]<0.95&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)"},
	
	// (sbt) Tighter sideband:
	{"fjp_sbt", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_sbt_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fj_sbt", "w*(tau43[0]<0.85&&tau42[0]<0.50&&(tau42[0]>0.45||tau43[0]>0.80))"},
	
	// (sbtb) Tighter sideband, b-tagged:
	{"fjp_sbtb", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbtb_p", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.85&&Max$(tau42)<0.50&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fj_sbtb", "w*(tau43[0]<0.85&&tau42[0]<0.50&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)"},
	
	// (sb2) Sideband in eta and masy:
	{"fjp_sb2", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0)"},
	{"fjp_mc_sb2", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0)"},
	{"fjp_data_sb2", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0"},
	{"fj_sb2", "w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_mc_sb2", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_data_sb2", "tau43[0]<0.80&&tau42[0]<0.45"},
	
	// (sb2b) b-tagged sideband in eta and masy:
	{"fjp_sb2b", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0&&Min$(bd)>0.46)"},
	{"fjp_mc_sb2b", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0&&Min$(bd)>0.46)"},
	{"fjp_data_sb2b", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&deta>1.0&&Min$(bd)>0.46"},
	{"fj_sb2b", "w*(tau43[0]<0.80&&tau42[0]<0.45&&bd[0]>0.46)"},
	{"fj_mc_sb2b", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45&&bd[0]>0.46)"},
	{"fj_data_sb2b", "tau43[0]<0.80&&tau42[0]<0.45&&bd[0]>0.46"},
	
	// (sb22) Sideband in eta:
	{"fjp_sb22", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&deta>1.0)"},
	{"fjp_mc_sb22", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&deta>1.0)"},
	{"fjp_data_sb22", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1&&deta>1.0"},
	{"fj_sb22", "w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_mc_sb22", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_data_sb22", "tau43[0]<0.80&&tau42[0]<0.45"},
	
	// (sb3) Sideband in masy:
	{"fjp_sb3", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p>0.12)"},
	{"fjp_mc_sb3", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p>0.12)"},
	{"fjp_data_sb3", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p>0.12"},
	{"fj_sb3", "w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_mc_sb3", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_data_sb3", "tau43[0]<0.80&&tau42[0]<0.45"},
	
	// Tuple cuts:
	{"tuple_presel", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5)"},
	{"tuple_fjp_sig", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.8&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.45&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1])"},
	{"tuple_fjp_sbb", "w*(ak8_pf_ht>900&&(ca12_pft_m[0]>50||ca12_pft_m[1]>50)&&(ca12_pf_tau2[0]/ca12_pf_tau1[0])>0.5&&(ca12_pf_tau2[1]/ca12_pf_tau1[1])>0.5&&abs(ca12_pf_eta[0]-ca12_pf_eta[1])<1.0&&(ca12_pf_tau4[0]/ca12_pf_tau3[0])<0.9&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])<0.9&&(ca12_pf_tau4[0]/ca12_pf_tau2[0])<0.55&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])<0.55&&(((ca12_pf_tau4[0]/ca12_pf_tau3[0])>0.8&&(ca12_pf_tau4[1]/ca12_pf_tau3[1])>0.8)||((ca12_pf_tau4[0]/ca12_pf_tau2[0])>0.45&&(ca12_pf_tau4[1]/ca12_pf_tau2[1])>0.45))&&(abs(ca12_pfp_m[0]-ca12_pfp_m[1])/(ca12_pfp_m[0]+ca12_pfp_m[1]))<0.1&&ca12_pf_jetid_l[0]&&ca12_pf_jetid_l[1]&&ca12_pf_bd_csv[0]>0.46&&ca12_pf_bd_csv[1]>0.46)"}
//	{"fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
};

TCut* get_cut(TString cut, Double_t weight=1) {
	if (weight == 1) {return new TCut(cut, cut_info[cut]);}
	else if (weight > 0) {
		TString modified;
		modified.Form("%f", weight);
		modified = modified + "*" + cut_info[cut];
		return new TCut(cut, modified);
	}
//	else {
//		cout << "[!!] Cut not found: " << cut << endl;
//	}
}


// Specific cut functions:
/// sig:
TCut* cut_fjp_sig() {return get_cut("fjp_sig");}
TCut* cut_fjp_mc_sig() {return get_cut("fjp_mc_sig");}
TCut* cut_fjp_data_sig() {return get_cut("fjp_data_sig");}
TCut* cut_fj_sig() {return get_cut("fj_sig");}
TCut* cut_fj_mc_sig() {return get_cut("fj_mc_sig");}
TCut* cut_fj_data_sig() {return get_cut("fj_data_sig");}
/// sig2:
TCut* cut_fjp_sig2() {return get_cut("fjp_sig2");}
TCut* cut_fjp_mc_sig2() {return get_cut("fjp_mc_sig2");}
TCut* cut_fjp_data_sig2() {return get_cut("fjp_data_sig2");}
TCut* cut_fj_sig2() {return get_cut("fj_sig2");}
TCut* cut_fj_mc_sig2() {return get_cut("fj_mc_sig2");}
TCut* cut_fj_data_sig2() {return get_cut("fj_data_sig2");}

