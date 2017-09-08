#include "background_fitting.cc"
#include "ht_reweighting.cc"

TH1* make_template(TH1* h, double masy_cut=0.1) {
	TString name = h->GetName() + TString("_temp");
	int xbins = h->GetNbinsX();
	/// Make output histogram:
	TH1D* temp = new TH1D(name, "", 1000, 0, 1000);
	
	// Do the convolution:
	for (int x0bin = 1; x0bin <= xbins; x0bin++) {
		for (int x1bin = x0bin; x1bin <= xbins; x1bin++) {
			double m0 = h->GetXaxis()->GetBinCenter(x0bin);
			double m1 = h->GetXaxis()->GetBinCenter(x1bin);
			double masy = fabs((m0 - m1)/(m0 + m1));
			double mavg = (m0 + m1)/2;
			double n0 = h->GetBinContent(x0bin);
			double n1 = h->GetBinContent(x1bin);
			double weight = n0*n1;
			if (masy < masy_cut) temp->Fill(mavg, weight);
		}
	}
	// Get rid of errors:
	for(int xbin = 0; xbin <= temp->GetNbinsX() + 1; xbin++) temp->SetBinError(xbin, 0);
	
	return temp;
}

TH1* make_template(TH2* h, TString ds, TString cut_name="sig", double masy_cut=0.1, double deta_cut=1.0) {
	TString name = h->GetName() + TString("_temp");
	int xbins = h->GetNbinsX();		// m
	int ybins = h->GetNbinsY();		// eta
	/// Make output histogram:
	TH1D* temp = new TH1D(name, "", 1000, 0, 1000);
	
	// Do the convolutions:
	for (int x0bin = 1; x0bin <= xbins; x0bin++) {
		for (int x1bin = x0bin; x1bin <= xbins; x1bin++) {
			for (int y0bin = 1; y0bin <= ybins; y0bin++) {
				for (int y1bin = y0bin; y1bin <= ybins; y1bin++) {
					double m0 = h->GetXaxis()->GetBinCenter(x0bin);
					double m1 = h->GetXaxis()->GetBinCenter(x1bin);
					double masy = fabs((m0 - m1)/(m0 + m1));
					double mavg = (m0 + m1)/2;
					double eta0 = h->GetYaxis()->GetBinCenter(y0bin);
					double eta1 = h->GetYaxis()->GetBinCenter(y1bin);
					double deta = abs(eta0 - eta1);
					double n0 = h->GetBinContent(x0bin, y0bin);
					double n1 = h->GetBinContent(x1bin, y1bin);
					double weight = n0*n1;
					if (cut_name == "sig"){
						if (masy < masy_cut && deta < deta_cut) temp->Fill(mavg, weight);
					}
					else{
						if (masy < masy_cut && deta < deta_cut) temp->Fill(mavg, weight);
					}
				}
			}
		}
	}
	
	return temp;
}

TH1* make_template(TH3* h, TString ds, TString cut_name, TString dir="", int f=1, double masy_cut=0.1, double deta_cut=1.0, bool htreweight=true) {
	TString name = h->GetName() + TString("_temp");
	int xbins = h->GetNbinsX();		// m
	int ybins = h->GetNbinsY();		// eta
	int zbins = h->GetNbinsZ();		// ht
	/// Make output histogram:
	TH1* hht_fj = (TH1*) h->ProjectionZ();
	TH2D* temp_proto = new TH2D(name + "proto", "", 1200, 0, 1200, hht_fj->GetNbinsX(), hht_fj->GetXaxis()->GetBinLowEdge(1), hht_fj->GetXaxis()->GetBinUpEdge(hht_fj->GetNbinsX()));
//	TH1D* temp = new TH1D(name, "", 1000, 0, 1000);
//	TH1* hht_fjp = (TH1*) hht_fjp->Clone("hht_fjp");
	
	// Do the convolutions:
//	double htnormfirst = hht_fj->GetBinContent(1);
	for (int zbin = 1; zbin <= zbins; zbin++) {
		double ht = h->GetZaxis()->GetBinCenter(zbin);
//		double htnormratio = htnormfirst/hht_fj->GetBinContent(zbin);
		double weight_factor = 1;
//		if (htreweight) weight_factor = correction_function(ht, ds, cut_name, dir)/correction_function(900, ds, cut_name, dir);
//		if (htreweight) weight_factor = correction_function(900, ds, cut_name, dir)/correction_function(ht, ds, cut_name, dir);
		cout << "htbin = " << zbin << " (" << ht << " GeV), reweight = " << weight_factor << endl;
		for (int x0bin = 1; x0bin <= xbins; x0bin++) {
			for (int x1bin = x0bin; x1bin <= xbins; x1bin++) {
				for (int y0bin = 1; y0bin <= ybins; y0bin++) {
					for (int y1bin = y0bin; y1bin <= ybins; y1bin++) {
						double m0 = h->GetXaxis()->GetBinCenter(x0bin);
						double m1 = h->GetXaxis()->GetBinCenter(x1bin);
						double masy = fabs((m0 - m1)/(m0 + m1));
						double mavg = (m0 + m1)/2;
						double eta0 = h->GetYaxis()->GetBinCenter(y0bin);
						double eta1 = h->GetYaxis()->GetBinCenter(y1bin);
						double deta = abs(eta0 - eta1);
						double n0 = h->GetBinContent(x0bin, y0bin, zbin);
						double n1 = h->GetBinContent(x1bin, y1bin, zbin);
						double weight = n0*n1;
						if (cut_name == "sbide" || cut_name == "sbideb"){
							if (deta > deta_cut) temp_proto->Fill(mavg, ht, weight);
						}
						else{
							if (masy < masy_cut && deta < deta_cut) {
								temp_proto->Fill(mavg, ht, weight);
							}
						}
					}
				}
			}
		}
	}
	
	if (!htreweight) return (TH1*) temp_proto->ProjectionX();
	// ht-reweight:
	TH2* temp_proto_htre = (TH2*) temp_proto->Clone(name + "protohtre");
	TH1* hht_proto = (TH1*) temp_proto->ProjectionY();
	double htnormfirst = hht_proto->GetBinContent(1);
	for (int htbin = 1; htbin <= temp_proto->GetNbinsY(); htbin++) {
		double ht = hht_proto->GetBinCenter(htbin);
		double w = htnormfirst/hht_proto->GetBinContent(htbin);		// make the ht distribution flat
		w = w*correction_function(ht, ds, cut_name, dir, f)/correction_function(900, ds, cut_name, dir, f);		// weight the ht distribution to the measured.
		for (int mbin = 1; mbin <= temp_proto->GetNbinsX(); mbin++) {
			temp_proto_htre->SetBinContent(mbin, htbin, temp_proto->GetBinContent(mbin, htbin)*w);
		}
	}
	
//	TF1* f1 = new TF1("f1", "[0]*x^[1]");
//	f1->SetLineColor(kRed);
//	f1->SetParameters(7e20, -5);
//	TH1* hht_proto_htre = (TH1*) temp_proto_htre->ProjectionY();
//	hht_proto_htre->Draw();
//	hht_proto_htre->Fit("f1", "", "", 900, 3200);
	return (TH1*) temp_proto_htre->ProjectionX();
}

TH1* fetch_template(TString ds, TString cut, TString dir="", int f=1, bool ht=true) {
	TString name = "temp_" + ds + "_" + cut + "_p" + "_f" + to_string(f);
	if (dir != "") name = name + "_" + dir;
	if (!ht) name = name + "_xht";
	
	TFile* tf_in = TFile::Open("/home/tote/decortication/macros/background_tools/template_plots.root");
	TH1* temp = (TH1*) tf_in->Get(name);
	return temp;
}


//void make_template(TH2* h, TString ds, TString cut_name, double masy_cut=0.1) {
//	TString name = h->GetName() + TString("_conv");
//	int xbins = h->GetNbinsX();		// m
//	int ybins = h->GetNbinsY();		// ht
//	/// Make output histogram:
//	TH1D* conv = new TH1D(name, "", 1000, 0, 1000);
//	
//	// Do the convolutions:
//	for (int ybin = 1; ybin <= ybins; ybin++) {
////		cout << ybin << endl;
//		double ht = h2_fj->GetYaxis()->GetBinCenter(ybin);
//		for (int x0bin = 1; x0bin <= xbins; x0bin++) {
//			for (int x1bin = x0bin; x1bin <= xbins; x1bin++) {
//				double m0 = h->GetXaxis()->GetBinCenter(x0bin);
//				double m1 = h->GetXaxis()->GetBinCenter(x1bin);
//				double masy = fabs((m0 - m1)/(m0 + m1));
//				double mavg = (m0 + m1)/2;
//				double n0 = h->GetBinContent(x0bin, ybin);
//				double n1 = h->GetBinContent(x1bin, ybin);
//				double weight_factor = correction_function(900, ds, cut_name)/correction_function(ht, ds, cut_name);
//				double weight = n0*n1*weight_factor;
//				if (cut_name == "sb3"){
//					if (masy > 0.12) conv->Fill(mavg, weight);
//				}
//				else{
//					if (masy < 0.1) conv->Fill(mavg, weight);
//				}
//			}
//		}
//	}
//	
//	return conv;
//}


