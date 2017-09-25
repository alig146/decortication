TH1D* GarwoodErrorBands_68CL(TH1D* h){
	unsigned int Bins = h->GetNbinsX();
	const double a = 1.0 - 0.6827; //<-- CL
	for(unsigned int i = 0; i <= Bins + 1; i++){
		double yield = h->GetBinContent(i);
		double low   = 0.5*TMath::ChisquareQuantile(     a/2 , 2* yield   );   //(Double_t p, Double_t ndf)
		double high  = 0.5*TMath::ChisquareQuantile( 1 - a/2 , 2*(yield+1));    //double dm    = h->GetBinWidth(i);
		h->SetBinContent(i, yield);
		h->SetBinError(i, (high-low)/2. );
		}
	return h;
}

TH1D* make_qcd_garwood(TFile* tf_in, TString ds, TString cut, int nrebin=30) {
	TFile* tf_out = new TFile("garwood_plots_" + ds + "_" + cut + ".root", "recreate");
	
	TTree *tt = (TTree*) tf_in->Get(ds);
//	tt->Draw("w>>h(1000,0,20)", get_cut("w_" + cut_name));

	vector<TCut> cuts_weight;
	if (ds == "qcdmg") {
		cuts_weight.push_back(TCut("qcdmg", "1"));
		cuts_weight.push_back(TCut("qcdmg2000", "sigma<30"));
		cuts_weight.push_back(TCut("qcdmg1500", "sigma>100&&sigma<200"));
		cuts_weight.push_back(TCut("qcdmg1000", "sigma>1000&&sigma<2000"));
		cuts_weight.push_back(TCut("qcdmg700", "sigma>6000&&sigma<7000"));
//		cuts_weight.push_back(TCut("qcdmg500", "sigma>30000"));
	}
	else if (ds == "qcdp") {
		cuts_weight.push_back(TCut("qcdp", "1"));
		cuts_weight.push_back(TCut("qcdp3200", "sigma<0.0002"));
		cuts_weight.push_back(TCut("qcdp2400", "sigma>0.005&&sigma<0.01"));
		cuts_weight.push_back(TCut("qcdp1800", "sigma>0.1&&sigma<0.2"));
		cuts_weight.push_back(TCut("qcdp1400", "sigma>0.8&&sigma<0.9"));
		cuts_weight.push_back(TCut("qcdp1000", "sigma>9&&sigma<10"));
		cuts_weight.push_back(TCut("qcdp800", "sigma>30&&sigma<40"));
		cuts_weight.push_back(TCut("qcdp600", "sigma>180&&sigma<200"));
		cuts_weight.push_back(TCut("qcdp470", "sigma>600&&sigma<800"));
		cuts_weight.push_back(TCut("qcdp300", "sigma>7800"));
	}
////	if (ds == "qcdmg") {
////		cuts_weight.push_back(TCut("qcdmg", "1"));
////		cuts_weight.push_back(TCut("qcdmg2000", "w<0.8"));
////		cuts_weight.push_back(TCut("qcdmg1500", "w>0.8&&w<4.0"));
////		cuts_weight.push_back(TCut("qcdmg1000", "w>6.0&&w<12.0"));
////		cuts_weight.push_back(TCut("qcdmg700", "w>12.0"));
////	}
////	else if (ds == "qcdp") {
////		cuts_weight.push_back(TCut("qcdp", "1"));
////		cuts_weight.push_back(TCut("qcdp3200", "w<0.0005"));
////		cuts_weight.push_back(TCut("qcdp2400", "w>0.0005&&w<0.005"));
////		cuts_weight.push_back(TCut("qcdp1800", "w>0.005&&w<0.04"));
////		cuts_weight.push_back(TCut("qcdp1400", "w>0.04&&w<0.1"));
////		cuts_weight.push_back(TCut("qcdp1000", "w>0.1&&w<0.2"));
////		cuts_weight.push_back(TCut("qcdp800", "w>0.2&&w<1.0"));
////		cuts_weight.push_back(TCut("qcdp600", "w>1.0&&w<3.0"));
////		cuts_weight.push_back(TCut("qcdp470", "w>3.0&&w<10.0"));
////		cuts_weight.push_back(TCut("qcdp300", "w>10.0"));
////	}
	
	TH1D* gar = new TH1D("gar", "", 1200/nrebin, 0, 1200);
	
	vector<TH1*> hists;
	for (unsigned i = 0; i < cuts_weight.size(); ++i) {
		TString name = "bin" + to_string(i);
		if (i == 0) name = "nom";
		
//		TCanvas* tc = new TCanvas(name, name);
		tt->Draw(TString("mavg_p>>h(") + to_string(1200/nrebin) + ",0,1200)", (get_cut("fjp_" + cut, "", 0) + cuts_weight[i])*"abs(W)");
		TH1* h = (TH1*) gDirectory->Get("h");
		h->SetName(name);
		h->SetTitle("");
		hists.push_back(h);
		tf_out->WriteTObject(h);
		
		tt->Draw("w>>w", (get_cut("fjp_" + cut, "", 0) + cuts_weight[i])*"abs(W)");
		TH1* w = (TH1*) gDirectory->Get("w");
		w->SetName("w_" + name);
		if (i > 0) cout << i << " " << cuts_weight[i].GetName() << " " << w->GetMean() << " (" << w->GetEntries() << ")" << endl;
		
		if (i > 0) {
			TH1* h_gar = (TH1*) h->Clone(name + "_gar");
			h_gar->Scale(1.0/w->GetMean());
			h_gar = GarwoodErrorBands_68CL((TH1D*) h_gar);
			h_gar->Scale(w->GetMean());
			gar->Add(h_gar);
			tf_out->WriteTObject(h_gar);
		}
	}
	
	tf_out->WriteTObject(gar);
	return gar;
}
