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
	
	// (sig) Signal region:
//	{"fjp_sig", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_sig", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_sig_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_mc_sig", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)"},
	{"fjp_data_sig", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1"},
	{"fj_sig", "w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_mc_sig", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)"},
	{"fj_data_sig", "tau43[0]<0.80&&tau42[0]<0.45"},
	
	// (sig2) Loose signal region:
	{"fjp_sig2", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1)"},
	{"fjp_mc_sig2", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1)"},
	{"fjp_data_sig2", "Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1"},
	{"fj_sig2", "w*(tau43[0]<0.90&&tau42[0]<0.50)"},
	{"fj_mc_sig2", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.50)"},
	{"fj_data_sig2", "tau43[0]<0.90&&tau42[0]<0.50"},
	
	// (sb) Sideband:
	{"fjp_sb", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_sb_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_mc_sb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)"},
	{"fjp_data_sb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1"},
	{"fj_sb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))"},
	{"fj_mc_sb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))"},
	{"fj_data_sb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)"},
	
	// (sbb) b-tagged sideband:
	{"fjp_sbb", "w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_sbb_ttbar", "wtt*w*(htak8>900&&Max$(m_t)>50&&Min$(tau21)>0.5&&deta<1.0&&Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)"},
	{"fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46"},
	{"fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)"},
	{"fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)"},
	{"fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46"},
	
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

