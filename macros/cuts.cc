void cuts() {return;}

// Loose signal region:
TCut* cut_fjp_loose() {return new TCut("cut_fjp_loose", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1)");}
TCut* cut_fjp_mc_loose() {return new TCut("cut_fjp_mc_loose", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1)");}
TCut* cut_fjp_data_loose() {return new TCut("cut_fjp_data_loose", "Max$(tau43)<0.90&&Max$(tau42)<0.50&&masy_p<0.1");}
TCut* cut_fj_loose() {return new TCut("cut_fj_loose", "w*(tau43[0]<0.90&&tau42[0]<0.50)");}
TCut* cut_fj_mc_loose() {return new TCut("cut_fj_mc_loose", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.50)");}
TCut* cut_fj_data_loose() {return new TCut("cut_fj_data_loose", "tau43[0]<0.90&&tau42[0]<0.50");}

// Signal region:
TCut* cut_fjp_sig() {return new TCut("cut_fjp_sig", "w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)");}
TCut* cut_fjp_mc_sig() {return new TCut("cut_fjp_mc_sig", "2.3/10*w*(Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1)");}
TCut* cut_fjp_data_sig() {return new TCut("cut_fjp_data_sig", "Max$(tau43)<0.80&&Max$(tau42)<0.45&&masy_p<0.1");}
TCut* cut_fj_sig() {return new TCut("cut_fj_sig", "w*(tau43[0]<0.80&&tau42[0]<0.45)");}
TCut* cut_fj_mc_sig() {return new TCut("cut_fj_mc_sig", "2.3/10*w*(tau43[0]<0.80&&tau42[0]<0.45)");}
TCut* cut_fj_data_sig() {return new TCut("cut_fj_data_sig", "tau43[0]<0.80&&tau42[0]<0.45");}

// Sideband (inclusive):
//TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1)");}
//TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1)");}
//TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1");}
//TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58)");}
//TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58)");}
//TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58");}

//TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1)");}
//TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1)");}
//TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1");}
//TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60)");}
//TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60)");}
//TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60");}

//TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1)");}
//TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1)");}
//TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1");}
//TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60)");}
//TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60)");}
//TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60");}

//TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
//TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
//TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1");}
//TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80))");}
//TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80))");}
//TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)");}

TCut* cut_fjp_sb() {return new TCut("cut_fjp_sb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
TCut* cut_fjp_mc_sb() {return new TCut("cut_fjp_mc_sb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1)");}
TCut* cut_fjp_data_sb() {return new TCut("cut_fjp_data_sb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1");}
TCut* cut_fj_sb() {return new TCut("cut_fj_sb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))");}
TCut* cut_fj_mc_sb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80))");}
TCut* cut_fj_data_sb() {return new TCut("cut_fj_data_sb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)");}


// Sideband (b-tagged):
//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.58&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.58&&bd[0]>0.46");}

//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]<0.60&&bd[0]>0.46");}

//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46");}

//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.60&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.60&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46");}

TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46)");}
TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.45||Min$(tau43)>0.80)&&masy_p<0.1&&Min$(bd)>0.46");}
TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46)");}
TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.45||tau43[0]>0.80)&&bd[0]>0.46");}

//// NEW tuples:
//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.43||Min$(tau43)>0.75)&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.43||Min$(tau43)>0.75)&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Max$(tau43)<0.90&&Max$(tau42)<0.55&&(Min$(tau42)>0.43||Min$(tau43)>0.75)&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.43||tau43[0]>0.75)&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.43||tau43[0]>0.75)&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]<0.90&&tau42[0]<0.55&&(tau42[0]>0.43||tau43[0]>0.75)&&bd[0]>0.46");}




//TCut* cut_fjp_sbb() {return new TCut("cut_fjp_sbb", "w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_mc_sbb() {return new TCut("cut_fjp_mc_sbb", "2.3/10*w*(Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46)");}
//TCut* cut_fjp_data_sbb() {return new TCut("cut_fjp_data_sbb", "Min$(tau43)>0.80&&Max$(tau43)<0.90&&Min$(tau42)>0.45&&Max$(tau42)<0.60&&masy_p<0.1&&Min$(bd)>0.46");}
//TCut* cut_fj_sbb() {return new TCut("cut_fj_sbb", "w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
//TCut* cut_fj_mc_sbb() {return new TCut("cut_fj_mc_sbb", "2.3/10*w*(tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46)");}
//TCut* cut_fj_data_sbb() {return new TCut("cut_fj_data_sbb", "tau43[0]>0.80&&tau43[0]<0.90&&tau42[0]>0.45&&tau42[0]<0.60&&bd[0]>0.46");}

