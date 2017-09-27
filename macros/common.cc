#include <Deracination/Straphanger/test/decortication/macros/cuts.cc>
#include <Deracination/Straphanger/test/decortication/macros/info.cc>
#include <Deracination/Straphanger/test/decortication/macros/pileup.cc>
#include <Deracination/Straphanger/test/decortication/macros/statistical_tools.cc>
#include <Deracination/Straphanger/test/truculence/macros/styling_tools/styling_tools.cc>
#include <Deracination/Straphanger/test/truculence/macros/utilities.cc>
#include <Deracination/Straphanger/test/decortication/macros/background_tools/background_templates.cc>

void common() {return;}		// Stops a warning being printed when excuted by ROOT.

TCanvas* draw_pull(TString name, TH1* obs, TH1* exp, double xmin, double xmax, TString metric="pull", bool mc=false, int corner=1) {
	TH1* pull = (TH1*) obs->Clone("pull");
	pull->SetStats(0);
	pull->Sumw2();		// Why do I do this?
	for (int i=1; i <= pull->GetNbinsX(); ++ i) {
		double o = obs->GetBinContent(i);
		double oe = obs->GetBinError(i);
		double e = exp->GetBinContent(i);
		double ee = exp->GetBinError(i);
		
		double r = 0;
		if (o != 0 && e != 0) r = o/e;
		double re = 0;
		if (r != 0) r*sqrt(pow(oe/o, 2) + pow(ee/e, 2));
		double p = 0;
		if (oe != 0) p = (o - e)/oe;
		double pe = 0;
		if (oe != 0) pe = sqrt(pow(oe, 2) + pow(ee, 2))/oe;
		
		if (metric == "pull") {
			pull->SetBinContent(i, p);
			pull->SetBinError(i, pe);
		}
		else if (metric == "ratio") {
			pull->SetBinContent(i, r);
			pull->SetBinError(i, re);
		}
	}
	
	double yvalue = 0;
	if (metric == "ratio") yvalue = 1;
	TLine* line = new TLine(xmin, yvalue, xmax, yvalue);
	line->SetLineColorAlpha(kBlue, 0.3);
	line->SetLineWidth(2);
//	line->SetLineStyle(2);
	
	// Calculate chi2:
	Float_t chi2 = 0;
	Float_t ndf = 0;
	for (int i = 1; i <= pull->GetNbinsX(); ++i) {
//		cout << i << ", " << pull->GetBinContent(i) << ", " << pull->GetBinError(i) << endl;
		if (pull->GetBinError(i) != 0) {
			chi2 += pow(pull->GetBinContent(i) - yvalue, 2)/pow(pull->GetBinError(i), 2);
			ndf += 1;
		}
	}
	Float_t chi2perndf = chi2/ndf;
//	cout << "Pull chi2 = " << chi2 << endl;
//	cout << "Pull NDF = " << ndf << endl;
//	cout << "Pull chi2/NDF = " << chi2perndf << endl;
	
	TCanvas* canvas = new TCanvas(name, name);
//	canvas->SetCanvasSize(1250, 1250);
//	canvas->SetWindowSize(1250 + (1250 - canvas->GetWw()), 1250 + (1250 - canvas->GetWh()));
//	canvas->SetWindowSize(1250, 1250);
	TPad* upperPad = new TPad(name + "_upper", name + "_upper", 0.0, 0.25, 1.0, 1.0);
	upperPad->SetNumber(1);
	TPad* lowerPad = new TPad(name + "_lower", name + "_lower", 0.0, 0.0, 1.0, 0.25);
	lowerPad->SetNumber(2);
	upperPad->Draw();
	lowerPad->Draw();
	
	upperPad->SetBottomMargin(0.027);
//	upperPad->SetTopMargin(0.055);
//	upperPad->SetFillColorAlpha(42, 0.5);
//	lowerPad->SetFillColorAlpha(41, 0.5);
	lowerPad->SetTopMargin(0.00);
	lowerPad->SetBottomMargin(0.45);
	lowerPad->SetGridy();
	lowerPad->SetGridx();
	
	lowerPad->cd();
	pull->Draw("y+");
	line->Draw();
	pull->Draw("same e");
	
//	h1->SetTitle("");
//	h2->SetTitle("");
//	h1->GetXaxis()->SetLabelSize(0);
//	h2->GetXaxis()->SetLabelSize(0);
//	style_ylabel(h1);
//	h2->SetLineColor(kRed);
//	h2->SetMarkerColor(kRed);
	pull->SetTitle("");
//	h3->GetXaxis()->SetLabelFont(43);
//	h3->GetXaxis()->SetNdivisions(h1->GetXaxis()->GetNdivisions());
//	h3->GetXaxis()->SetTitle("Average jet mass [GeV]");
	pull->GetXaxis()->SetTitleOffset(pull->GetXaxis()->GetTitleOffset()*2.9);
	pull->GetYaxis()->SetTitleSize(pull->GetYaxis()->GetTitleSize()*0.5);
	pull->GetYaxis()->SetTitleOffset(pull->GetYaxis()->GetTitleOffset()*0.9);
	pull->GetYaxis()->SetLabelSize(pull->GetYaxis()->GetLabelSize()*0.6);
	pull->GetYaxis()->SetNdivisions(405);
	pull->GetYaxis()->CenterTitle();
	pull->GetYaxis()->SetTitle("Pull");
	if (pull->GetMinimum() < -10) pull->SetMinimum(-10);
//	h3->GetYaxis()->SetTitleFont(43);
//	h3->GetYaxis()->SetTitleSize(25);
//	h3->GetYaxis()->SetLabelFont(43);
//	h3->GetYaxis()->SetLabelSize(30);
	
	TFile* tf = new TFile(TString(name) + ".root", "recreate");
	TH1F* stats = new TH1F("stats", "", 10, 0, 10);
	stats->SetBinContent(1, chi2);
	stats->SetBinContent(2, ndf);
	stats->SetBinContent(3, chi2perndf);
	tf->WriteTObject(pull);
	tf->WriteTObject(stats);
	tf->Close();
	
	return canvas;
}

void show_template(TTree* tt, TString cut_name, bool mc=false) {
	TCanvas* tc = new TCanvas("tc", "tc");
	tc->cd();
	gStyle->SetOptStat(0);
	
	tt->Draw("mavg_p>>fjp(1000,0,1000)", get_cut("fjp_" + cut_name));
	TH1* fjp = (TH1*) gDirectory->Get("fjp");
	tt->Draw("m_p[0]>>fj(1000,0,1000)", get_cut("fj_" + cut_name));
	TH1* fj = (TH1*) gDirectory->Get("fj");
	TH1* conv = make_template(fj);
	
	fjp->Rebin(50);
	
	fj->Rebin(50);
	fj->SetTitle("");
	fj->GetXaxis()->SetNdivisions(405);
	fj->GetXaxis()->SetTitle("(Average) jet mass [GeV]");
	style_ylabel_th1(fj);
	fj->Scale(fjp->Integral(1, fjp->GetNbinsX())/fj->Integral(1, fj->GetNbinsX()));
	fj->SetFillColor(kRed-4);
	fj->SetFillStyle(3003);
	fj->SetMaximum(fjp->GetMaximum()*1.2);
	
	conv->Rebin(50);
	conv->Scale(fjp->Integral(1, fjp->GetNbinsX())/conv->Integral(1, conv->GetNbinsX()));
	conv->SetFillColorAlpha(kBlue-10, 0.5);
	conv->SetLineStyle(2);
	
	fj->Draw("hist");
	conv->Draw("same");
	fjp->Draw("same,e");
	
	TLegend* leg = new TLegend(0.53, 0.63, 0.80, 0.78);
	leg->AddEntry(fj, "Single jet selection", "lf");
	leg->AddEntry(conv, "Derived template", "lf");
	leg->AddEntry(fjp, "Jet pair selection", "pl");
//	leg->AddEntry(h_fit, "Post-fit template", "l");
	leg->Draw();
	
	style_info(mc, "?");
	
	gPad->RedrawAxis();
}

void show_template(TH1* fj, TH1* fjp, TH1* temp, bool mc=false, TString tc_name="tc") {
	TCanvas* tc = new TCanvas(tc_name, tc_name);
	tc->cd();
	gStyle->SetOptStat(0);
	
	fjp->Rebin(50);
	
	fj->Rebin(50);
	fj->SetTitle("");
	fj->GetXaxis()->SetNdivisions(405);
	fj->GetXaxis()->SetTitle("(Average) jet mass [GeV]");
	style_ylabel_th1(fj);
	fj->Scale(fjp->Integral(1, fjp->GetNbinsX())/fj->Integral(1, fj->GetNbinsX()));
	fj->SetFillColor(kRed-4);
	fj->SetFillStyle(3003);
	fj->SetMaximum(fjp->GetMaximum()*1.2);
	
	temp->Rebin(50);
	temp->Scale(fjp->Integral(1, fjp->GetNbinsX())/temp->Integral(1, temp->GetNbinsX()));
	temp->SetFillColorAlpha(kBlue-10, 0.5);
	temp->SetLineStyle(2);
	
	fj->Draw("hist");
	temp->Draw("hist,same");
	fjp->Draw("same,e");
	
	TLegend* leg = new TLegend(0.53, 0.63, 0.80, 0.78);
	leg->AddEntry(fj, "Single jet selection", "lf");
	leg->AddEntry(temp, "Derived template", "lf");
	leg->AddEntry(fjp, "Jet pair selection", "pl");
//	leg->AddEntry(h_fit, "Post-fit template", "l");
	leg->Draw();
	
	style_info(mc, "?");
	
	gPad->RedrawAxis();
	
	tc->SaveAs("template_" + tc_name + ".pdf");
}

//vector<int> sort_histograms(vector<TH1*> hs);

vector<TCanvas*> same_set(vector<TH1*> hs, TString name) {
	// Deal with plots:
	vector<TH1*> hs_norm;
	vector<TH1*> hs_logy;
	vector<TH1*> hs_norm_logy;
	double max, max_norm, min, min_norm;
	int imax, imax_norm, imin, imin_norm;
	min = 100000000;
	min_norm = 1;
	for (int i = 0; i < hs.size(); ++i) {
		TH1* h_norm = (TH1*) hs[i]->Clone();
		TH1* h_logy = (TH1*) hs[i]->Clone();
		// Make normalized histogram:
		double sf = 1/h_norm->Integral();
		for (int ibin = 0; ibin < h_norm->GetNbinsX() + 1; ++ibin){
			h_norm->SetBinContent(ibin, h_norm->GetBinContent(ibin)*sf);
			h_norm->SetBinError(ibin, h_norm->GetBinError(ibin)*sf);
		}
		TH1* h_norm_logy = (TH1*) h_norm->Clone();
		hs_norm.push_back(h_norm);
		hs_logy.push_back(h_logy);
		hs_norm_logy.push_back(h_norm_logy);
		if (hs[i]->GetMaximum() > max) {
			imax = i;
			max = hs[i]->GetMaximum();
		}
		if (h_norm->GetMaximum() > max_norm) {
			imax_norm = i;
			max_norm = h_norm->GetMaximum();
		}
		if (hs[i]->GetMinimum() < min) {
			imin = i;
			min = hs[i]->GetMinimum();
		}
		if (h_norm->GetMinimum() < min_norm) {
			imin_norm = i;
			min_norm = h_norm->GetMinimum();
		}
	}
	
	// Make canvases:
	vector<TCanvas*> canvases;
	TCanvas* nom = new TCanvas(name, name);
	TCanvas* norm = new TCanvas(name + "_norm", name + "_norm");
	TCanvas* logy = new TCanvas(name + "_logy", name + "_logy");
	TCanvas* norm_logy = new TCanvas(name + "_norm_logy", name + "_norm_logy");
	canvases.push_back(nom);
	canvases.push_back(norm);
	canvases.push_back(logy);
	canvases.push_back(norm_logy);
	
	//Draw:
	gStyle->SetOptStat(0);
	// Nominal:
	nom->cd();
	hs[imax]->SetMaximum(max*1.4);
	hs[imax]->SetMinimum(0.0);
	hs[imax]->SetTitle("");
	hs[imax]->GetYaxis()->SetTitle("Events");
	hs[imax]->Draw("e");
	for (int i = 0; i < hs.size(); ++i) hs[i]->Draw("e same");
	gPad->RedrawAxis();
	
	// Normalized:
	norm->cd();
	hs_norm[imax_norm]->SetMaximum(max_norm*1.4);
	hs_norm[imax_norm]->SetMinimum(0.0);
	hs_norm[imax_norm]->SetTitle("");
	hs_norm[imax_norm]->GetYaxis()->SetTitle("Normalized events");
	hs_norm[imax_norm]->Draw("e");
	for (int i = 0; i < hs_norm.size(); ++i) hs_norm[i]->Draw("e same");
	gPad->RedrawAxis();
	
	// Logy:
	logy->cd();
	logy->SetLogy();
	hs_logy[imax]->SetMaximum(max*10);
	hs_logy[imax]->SetMinimum(max*0.0005);
	hs_logy[imax]->SetTitle("");
	hs_logy[imax]->GetYaxis()->SetTitle("Events");
	hs_logy[imax]->Draw("e");
	for (int i = 0; i < hs_logy.size(); ++i) hs_logy[i]->Draw("e same");
	gPad->RedrawAxis();
	
	// Norm logy:
	norm_logy->cd();
	norm_logy->SetLogy();
	hs_norm_logy[imax_norm]->SetMaximum(max_norm*10);
	hs_norm_logy[imax_norm]->SetMinimum(max_norm*0.005);
	hs_norm_logy[imax_norm]->SetTitle("");
	hs_norm_logy[imax_norm]->GetYaxis()->SetTitle("Normalized events");
	hs_norm_logy[imax_norm]->Draw("e");
	for (int i = 0; i < hs_norm_logy.size(); ++i) hs_norm_logy[i]->Draw("e same");
	gPad->RedrawAxis();
	
	cout << imax << ", " << hs[imax]->GetMaximum() << ", " << hs[imax]->GetMinimum() << endl;
	cout << imax_norm << ", " << hs_norm[imax_norm]->GetMaximum() << ", " << hs_norm[imax_norm]->GetMinimum() << endl;
	cout << imax << ", " << hs_logy[imax]->GetMaximum() << ", " << gPad->GetUymin() << endl;
	
	return canvases;
}




TLatex* style_cut(TString cut) {
	return style_write(TString("Selection: #bf{") + cut_proper[cut] + "}",  0.18, 0.94, 0.020);
}
