#include "cuts.cc"
#include "info.cc"
#include "/home/tote/truculence/macros/styling_tools/styling_tools.cc"
#include "/home/tote/decortication/macros/background_tools/background_templates.cc"

void common() {return;}		// Stops a warning being printed when excuted by ROOT.

void show_template(TTree* tt, TString cut_name, bool mc=false) {
	TCanvas* tc = new TCanvas("tc", "tc");
	tc->cd();
	gStyle->SetOptStat(0);
	
	tt->Draw("mavg_p>>fjp(1000,0,1000)", *get_cut("fjp_" + cut_name));
	TH1* fjp = (TH1*) gDirectory->Get("fjp");
	tt->Draw("m_p[0]>>fj(1000,0,1000)", *get_cut("fj_" + cut_name));
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
