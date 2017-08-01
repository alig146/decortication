#include "cuts.cc"
#include "info.cc"
#include "pileup.cc"
#include "/home/tote/truculence/macros/styling_tools/styling_tools.cc"
#include "/home/tote/truculence/macros/utilities.cc"
#include "/home/tote/decortication/macros/background_tools/background_templates.cc"

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
	
	upperPad->SetBottomMargin(0.023);
//	upperPad->SetTopMargin(0.055);
//	upperPad->SetFillColorAlpha(42, 0.5);
//	lowerPad->SetFillColorAlpha(41, 0.5);
	lowerPad->SetTopMargin(0.025);
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
	pull->GetYaxis()->SetTitle("Pull");
//	h3->GetYaxis()->SetTitleFont(43);
//	h3->GetYaxis()->SetTitleSize(25);
//	h3->GetYaxis()->SetLabelFont(43);
//	h3->GetYaxis()->SetLabelSize(30);
	
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
