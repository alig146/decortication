#include "background_tools.cc"

TH1 *theDATA, *theCDF, *thePDF;
TH1 *theDATA1, *theCDF1, *thePDF1, *theCDF2, *thePDF2, *theCDF3, *thePDF3;
vector<TString> param_names = {"amp", "shift", "stretch"};

int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

// Poisson log likelihood test function for the fitting routine:
void POISSONLL(int &, double *, double &f, double *par, int)
{
	double median = par[0];
	double amplitude = par[1];
	double shift = par[2];
	double stretch = par[3];

	// create thePDF from theCDF
	differentiate_cdf(theCDF, thePDF, median, amplitude, shift, stretch);
	
	double ll = 0.0;
	
	for(int i = 1; i <= theDATA->GetNbinsX(); i++) {
		double obs = theDATA->GetBinContent(i);
		double obse = theDATA->GetBinError(i);
		double exp = thePDF->GetBinContent(i);
//		if (exp <= 0.0){
//			cout << i << endl;
//			assert(exp > 0.0);
//		}
//		cout << "obs = " << obs << ", exp = " << exp << endl;
//		double ll_term = obs*log(exp) - exp - log((double) factorial(obs));
		
		if (exp > 0.0) {
			double ll_term = obs*log(exp) - exp - log((double) factorial(obs)); 		// I haven't been using this factorial term.
			
			ll += ll_term;
		}
	}
	f = -ll;
	
	if(false) std::cout << "median=" << median << "; amplitude=" << amplitude << "; shift=" << shift
		<< "; stretch=" << stretch << "; nll=" << f << std::endl;
	return;
}

void POISSONLL_stack2(int &, double *, double &f, double *par, int) {
	double median1 = par[0];
	double amplitude1 = par[1];
	double shift1 = par[2];
	double stretch1 = par[3];
	double median2 = par[4];
	double amplitude2 = par[5];
	double shift2 = par[6];
	double stretch2 = par[7];

	// create thePDF from theCDF
	differentiate_cdf(theCDF1, thePDF1, median1, amplitude1, shift1, stretch1);
	differentiate_cdf(theCDF2, thePDF2, median2, amplitude2, shift2, stretch2);
	
	double ll = 0.0;
	int nbins_flag = 0;
	TString flagged = "";
	for(int i = 1; i <= theDATA1->GetNbinsX(); i++) {
//		cout << i << endl;
		double m = theDATA1->GetXaxis()->GetBinUpEdge(i);
		if (m > 900) break;
		double obs = theDATA1->GetBinContent(i);
		double obse = theDATA1->GetBinError(i);
		double exp = thePDF1->GetBinContent(i) + thePDF2->GetBinContent(i);
//		if (exp <= 0.0){
//			cout << i << endl;
//			assert(exp > 0.0);
//		}

		if (exp <= 0 ) {
			exp = 0.000001;
			nbins_flag += 1;
			flagged += to_string(i) + ", ";
		}
		double ll_term = obs*log(exp) - exp - TMath::LnGamma(obs + 1);
//			double ll_term = obs*log(exp) - exp;
//		cout << "m = " << m << ", obs = " << obs << ", exp = " << exp << ", L = " << ll_term << endl;		// DEBUG
//		cout << "t1 = " << obs*log(exp) << ", t2 = " << exp << ", t3 = " << TMath::LnGamma(obs + 1) << endl;
//		cout << ll_term << endl;
		ll += ll_term;
	}
	f = -ll;
	if (nbins_flag > 0) cout << "nbins_flag = " << nbins_flag << " (" + flagged + ")" << endl;
//	cout << "nll = " << -ll << endl;
	
	return;
}

// chi-square test function for the fitting routine
void CHISQ(int &, double *, double &f, double *par, int)
{
	double median = par[0];
	double amplitude = par[1];
	double shift = par[2];
	double stretch = par[3];

	// create thePDF from theCDF
	differentiate_cdf(theCDF, thePDF, median, amplitude, shift, stretch);

	f = 0.0;
	for(int i = 1; i <= theDATA->GetNbinsX(); i++) {
		double obs = theDATA->GetBinContent(i);
		double obse = theDATA->GetBinError(i);
		double exp = thePDF->GetBinContent(i);
//		cout << i << "  " << obse << endl;
		assert(obse > 0.0);
		f += (obs - exp)*(obs - exp)/obse/obse;
	}
	if(DEBUG) std::cout << "median=" << median << "; amplitude=" << amplitude << "; shift=" << shift
		<< "; stretch=" << stretch << "; chi^2=" << f << std::endl;
	return;
}

void CHISQ_stack2(int &, double *, double &f, double *par, int) {
	double median1 = par[0];
	double amplitude1 = par[1];
	double shift1 = par[2];
	double stretch1 = par[3];
	double median2 = par[4];
	double amplitude2 = par[5];
	double shift2 = par[6];
	double stretch2 = par[7];

	// create thePDF from theCDF
	differentiate_cdf(theCDF1, thePDF1, median1, amplitude1, shift1, stretch1);
	differentiate_cdf(theCDF2, thePDF2, median2, amplitude2, shift2, stretch2);

	f = 0.0;
	for(int i = 1; i <= theDATA1->GetNbinsX(); i++) {
		double obs = theDATA1->GetBinContent(i);
		double obse = theDATA1->GetBinError(i);
		double exp = thePDF1->GetBinContent(i) + thePDF2->GetBinContent(i);
//		std::cout << "i=" << i << "; obs=" << obs << "; obse=" << obse << "; exp=" << exp << std::endl;
		assert(obse > 0.0);
		f += (obs - exp)*(obs - exp)/obse/obse;
	}
//	std::cout << "median1=" << median1 << "; amplitude1=" << amplitude1 << "; shift1=" << shift1
//		<< "; stretch1=" << stretch1 << "; "<< "median1=" << median2 << "; amplitude2=" << amplitude2 << "; shift2=" << shift2
//		<< "; stretch2=" << stretch2 << "; chi^2=" << f << std::endl;
	return;
}


void CHISQ_stack3(int &, double *, double &f, double *par, int) {
	double median1 = par[0];
	double amplitude1 = par[1];
	double shift1 = par[2];
	double stretch1 = par[3];
	double median2 = par[4];
	double amplitude2 = par[5];
	double shift2 = par[6];
	double stretch2 = par[7];
	double median3 = par[8];
	double amplitude3 = par[9];
	double shift3 = par[10];
	double stretch3 = par[11];

	// create thePDF from theCDF
	differentiate_cdf(theCDF1, thePDF1, median1, amplitude1, shift1, stretch1);
	differentiate_cdf(theCDF2, thePDF2, median2, amplitude2, shift2, stretch2);
	differentiate_cdf(theCDF3, thePDF3, median3, amplitude3, shift3, stretch3);

	f = 0.0;
	for(int i = 1; i <= theDATA1->GetNbinsX(); i++) {
		double obs = theDATA1->GetBinContent(i);
		double obse = theDATA1->GetBinError(i);
		double exp = thePDF1->GetBinContent(i) + thePDF2->GetBinContent(i) + thePDF3->GetBinContent(i);
//		std::cout << "i=" << i << "; obs=" << obs << "; obse=" << obse << "; exp=" << exp << std::endl;
		assert(obse > 0.0);
		f += (obs - exp)*(obs - exp)/obse/obse;
	}
//	std::cout << "median1=" << median1 << "; amplitude1=" << amplitude1 << "; shift1=" << shift1
//		<< "; stretch1=" << stretch1 << "; "<< "median1=" << median2 << "; amplitude2=" << amplitude2 << "; shift2=" << shift2
//		<< "; stretch2=" << stretch2 << "; chi^2=" << f << std::endl;
	return;
}

//// Perform a fit of the template to the data in the full selection using
//// the CDF, getting the new amplitude, shift and stretch for the template.
void perform_fit_chi2(TH1* hFullSel, TH1* hCDF, vector<double> binsx, TH1* params) {
	theDATA = hFullSel->Rebin(binsx.size() - 1, "theDATA", &binsx[0]);
	theCDF = hCDF;
	thePDF = (TH1*) theDATA->Clone("thePDF");       // use the same binning as theDATA
	
	double amp = params->GetBinContent(1);
	double shift = params->GetBinContent(2);
	double stretch = params->GetBinContent(3);
	double ampe, shifte, stretche;
	
	TMinuit minuit;
	minuit.SetErrorDef(1.0); // chi^2
//	minuit.SetErrorDef(0.5); // nll
	minuit.SetPrintLevel(3);
	minuit.Command("SET STR 2");  // precision (slow) mode
	
	// define parameter 0 (median), and fix it
	double median = median_from_cdf(theCDF);
	minuit.DefineParameter(0, "MEDIAN", median, 0.0, 0.0, 0.0);
	
	// define parameter 1 (amplitude) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP", amp, amp*0.1, 0.0, amp*100);
	
	// set parameter 2 (shift) and do not bound
	minuit.DefineParameter(2, "SHIFT", shift, 1, -200, 200);
	
	// set parameter 3 (stretch) and bound the stretch by 0 from below
	minuit.DefineParameter(3, "STRETCH", stretch, stretch*0.1, .01, stretch*100);
	
	minuit.SetFCN(CHISQ); // set the function
//	minuit.SetFCN(POISSONLL); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
	
	// get the parameters
	minuit.GetParameter(1, amp, ampe);
	minuit.GetParameter(2, shift, shifte);
	minuit.GetParameter(3, stretch, stretche);
	
	// Write parameters to histogram:
	params->SetBinContent(1, amp);
	params->SetBinError(1, ampe);
	params->SetBinContent(2, shift);
	params->SetBinError(2, shifte);
	params->SetBinContent(3, stretch);
	params->SetBinError(3, stretche);
	
	return;
}

void perform_fit(TH1* hFullSel, TH1* hCDF, vector<double> binsx, double &amp, double &ampe, double &shift, double &shifte, double &stretch, double &stretche) {
	theDATA = hFullSel->Rebin(binsx.size() - 1, "theDATA", &binsx[0]);
	theCDF = hCDF;
	thePDF = (TH1*) theDATA->Clone("thePDF");       // use the same binning as theDATA
	
	TMinuit minuit;
//	minuit.SetErrorDef(1.0); // chi^2
	minuit.SetErrorDef(0.5); // nll
	minuit.SetPrintLevel(3);
	minuit.Command("SET STR 2");  // precision (slow) mode
	
	// define parameter 0 (median), and fix it
	double median = median_from_cdf(theCDF);
	minuit.DefineParameter(0, "MEDIAN", median, 0.0, 0.0, 0.0);
	
	// define parameter 1 (amplitude) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP", amp, amp*0.1, 0.0, amp*100);
	
	// set parameter 2 (shift) and do not bound
	minuit.DefineParameter(2, "SHIFT", shift, 1, -200, 200);
	
	// set parameter 3 (stretch) and bound the stretch by 0 from below
	minuit.DefineParameter(3, "STRETCH", stretch, stretch*0.1, .01, stretch*100);
	
//	minuit.SetFCN(CHISQ); // set the function
	minuit.SetFCN(POISSONLL); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
	
	// get the parameters
	minuit.GetParameter(1, amp, ampe);
	minuit.GetParameter(2, shift, shifte);
	minuit.GetParameter(3, stretch, stretche);
	
	return;
}

//// Perform a fit of the template to the data in the full selection using
//// the CDF, getting the new amplitude, shift and stretch for the template.
//void perform_stacked_fit(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx1, vector<double> binsx2, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
//{
//	perform_fit(hFullSel1, hCDF1, binsx1, newAmp1, newAmpe1, newShift1, newShifte1, newStretch1, newStretche1);
//	
//	
//	std::cout << "Amp1=" << newAmp1 << " +/- " << newAmpe1 << std::endl;
//	std::cout << "Shift1=" << newShift1 << " +/- " << newShifte1 << std::endl;
//	std::cout << "Stretch1=" << newStretch1 << " +/- " << newStretche1 << std::endl;
//	
//	theDATA1 = hFullSel1->Rebin(binsx2.size() - 1, "theDATA1", &binsx2[0]);
//	theCDF1 = hCDF1;
//	theCDF2 = hCDF2;
//	thePDF1 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA
//	differentiate_cdf(hCDF1, thePDF1, median_from_cdf(hCDF1), newAmp1, newShift1, newStretch1);
//	thePDF2 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA

//	TMinuit minuit;
//	minuit.SetErrorDef(1.0); // chi^2
//	minuit.SetPrintLevel(DEBUG ? 3 : 1);
//	minuit.Command("SET STR 2");  // precision (slow) mode

//	// define parameter 0 (median1), and fix it
//	double median1 = median_from_cdf(theCDF1);
//	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

//	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
//	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

//	// set parameter 2 (shift1), and fix it
//	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);

//	// set parameter 3 (stretch1), and fix it
//	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);

//	// define parameter 4 (median2), and fix it
//	double median2 = median_from_cdf(theCDF2);
//	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

//	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
//	minuit.DefineParameter(5, "AMP2", newAmp2, newAmp2*0.1, 0.0, newAmp2*100);

//	// set parameter 6 (shift2) and do not bound
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 1, -200, 200);

//	// set parameter 7 (stretch2) and bound the stretch by 0 from below
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.1, .01, newStretch2*100);

////	minuit.SetFCN(CHISQ_stack2); // set the function
//	minuit.SetFCN(POISSONLL_stack2); // set the function
//	double tmp[1] = { 5000. }; int err;
//	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD

//	// get the parameters
//	minuit.GetParameter(1, newAmp1, newAmpe1);
////	minuit.GetParameter(2, newShift1, newShifte1);
////	minuit.GetParameter(3, newStretch1, newStretche1);  
//	minuit.GetParameter(5, newAmp2, newAmpe2);
//	minuit.GetParameter(6, newShift2, newShifte2);
//	minuit.GetParameter(7, newStretch2, newStretche2);

//	return;
//}


//void perform_stacked_fit_amp(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx1, vector<double> binsx2, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
//{
//	perform_fit(hFullSel1, hCDF1, binsx1, newAmp1, newAmpe1, newShift1, newShifte1, newStretch1, newStretche1);
//	
//	
//	std::cout << "Amp1=" << newAmp1 << " +/- " << newAmpe1 << std::endl;
//	std::cout << "Shift1=" << newShift1 << " +/- " << newShifte1 << std::endl;
//	std::cout << "Stretch1=" << newStretch1 << " +/- " << newStretche1 << std::endl;
//	
//	theDATA1 = hFullSel1->Rebin(binsx2.size() - 1, "theDATA1", &binsx2[0]);
//	theCDF1 = hCDF1;
//	theCDF2 = hCDF2;
//	thePDF1 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA
//	differentiate_cdf(hCDF1, thePDF1, median_from_cdf(hCDF1), newAmp1, newShift1, newStretch1);
//	thePDF2 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA

//	TMinuit minuit;
//	minuit.SetErrorDef(1.0); // chi^2
//	minuit.SetPrintLevel(DEBUG ? 3 : 1);
//	minuit.Command("SET STR 2");  // precision (slow) mode

//	// define parameter 0 (median1), and fix it
//	double median1 = median_from_cdf(theCDF1);
//	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

//	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
//	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

//	// set parameter 2 (shift1), and fix it
//	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);

//	// set parameter 3 (stretch1), and fix it
//	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);

//	// define parameter 4 (median2), and fix it
//	double median2 = median_from_cdf(theCDF2);
//	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

//	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
//	minuit.DefineParameter(5, "AMP2", newAmp2, newAmp2*0.1, 0.0, newAmp2*100);

//	// set parameter 6 (shift2), and fix it.
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 0.0, 0.0, 0.0);

//	// set parameter 7 (stretch2), and fix it.
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.0, .01, 0.0);

//	minuit.SetFCN(CHISQ_stack2); // set the function
//	double tmp[1] = { 5000. }; int err;
//	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD

//	// get the parameters:
//	minuit.GetParameter(1, newAmp1, newAmpe1);
//	minuit.GetParameter(2, newShift1, newShifte1);
//	minuit.GetParameter(3, newStretch1, newStretche1);  
//	minuit.GetParameter(5, newAmp2, newAmpe2);
//	minuit.GetParameter(6, newShift2, newShifte2);
//	minuit.GetParameter(7, newStretch2, newStretche2);

//	return;
//}

void perform_stacked_fit(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
{
	theDATA1 = hFullSel1->Rebin(binsx.size() - 1, "theDATA1", &binsx[0]);
	theCDF1 = hCDF1;
	theCDF2 = hCDF2;
	thePDF1 = (TH1*) theDATA1->Clone("thePDF1");       // use the same binning as theDATA
	thePDF2 = (TH1*) theDATA1->Clone("thePDF2");       // use the same binning as theDATA

	TMinuit minuit;
//	minuit.SetErrorDef(1); // chi^2
	minuit.SetErrorDef(0.5); // nll
	minuit.SetPrintLevel(1);
	minuit.Command("SET STR 2");  // precision (slow) mode

	// define parameter 0 (median1), and fix it
	double median1 = median_from_cdf(theCDF1);
	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

	// set parameter 2 (shift1), and fix it
//	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);
	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.1, -100, 100);

	// set parameter 3 (stretch1), and fix it
//	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);
	minuit.DefineParameter(3, "STRETCH1", newStretch1, newStretch1*0.01, 0.001, newStretch1*100);

	// define parameter 4 (median2), and fix it
	double median2 = median_from_cdf(theCDF2);
	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
	minuit.DefineParameter(5, "AMP2", newAmp2, newAmp2*0.1, 0.0, newAmp2*100);
//	minuit.DefineParameter(5, "AMP2", newAmp2, 0.01, 0.0, newAmp2*1000);

	// set parameter 6 (shift2), and fix it.
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 10, -5000, 5000);
	minuit.DefineParameter(6, "SHIFT2", newShift2, 0.1, -100, 100);

	// set parameter 7 (stretch2), and fix it.
	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.01, .001, newStretch2*100);
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.1, 0.00001, 10000);
//	minuit.DefineParameter(7, "STRETCH2", 1.0, 0.0, 0.0, 0.0);

//	minuit.SetFCN(CHISQ_stack2); // set the function
	minuit.SetFCN(POISSONLL_stack2); // set the function
	double tmp[1] = { 20000. }; int err;		// was 5000.
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();


	// get the parameters:
	minuit.GetParameter(1, newAmp1, newAmpe1);
	minuit.GetParameter(2, newShift1, newShifte1);
	minuit.GetParameter(3, newStretch1, newStretche1);  
	minuit.GetParameter(5, newAmp2, newAmpe2);
	minuit.GetParameter(6, newShift2, newShifte2);
	minuit.GetParameter(7, newStretch2, newStretche2);

	return;
}

void perform_stacked_fit_chi(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
{
	theDATA1 = hFullSel1->Rebin(binsx.size() - 1, "theDATA1", &binsx[0]);
	theCDF1 = hCDF1;
	theCDF2 = hCDF2;
	thePDF1 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA
	thePDF2 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA

	TMinuit minuit;
	minuit.SetErrorDef(1); // chi^2
//	minuit.SetErrorDef(0.5); // nll
	minuit.SetPrintLevel(1);
	minuit.Command("SET STR 2");  // precision (slow) mode

	// define parameter 0 (median1), and fix it
	double median1 = median_from_cdf(theCDF1);
	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

	// set parameter 2 (shift1), and fix it
//	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);
	minuit.DefineParameter(2, "SHIFT1", newShift1, 1,-100, 100);

	// set parameter 3 (stretch1), and fix it
//	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);
	minuit.DefineParameter(3, "STRETCH1", newStretch1, newStretch1*0.01, 0.001, newStretch1*100);

	// define parameter 4 (median2), and fix it
	double median2 = median_from_cdf(theCDF2);
	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
//	minuit.DefineParameter(5, "AMP2", newAmp2, newAmp2*0.1, 0.0, newAmp2*100);
	minuit.DefineParameter(5, "AMP2", newAmp2, 0.01, 0.0, newAmp2*1000);

	// set parameter 6 (shift2), and fix it.
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 0.0, 0.0, 0.0);
	minuit.DefineParameter(6, "SHIFT2", newShift2, 10, -5000, 5000);

	// set parameter 7 (stretch2), and fix it.
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.001, .01, newStretch2*10);
	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.1, .00001, 10000);
//	minuit.DefineParameter(7, "STRETCH2", 1.0, 0.0, 0.0, 0.0);

	minuit.SetFCN(CHISQ_stack2); // set the function
//	minuit.SetFCN(POISSONLL_stack2); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();


	// get the parameters:
	minuit.GetParameter(1, newAmp1, newAmpe1);
	minuit.GetParameter(2, newShift1, newShifte1);
	minuit.GetParameter(3, newStretch1, newStretche1);  
	minuit.GetParameter(5, newAmp2, newAmpe2);
	minuit.GetParameter(6, newShift2, newShifte2);
	minuit.GetParameter(7, newStretch2, newStretche2);

	return;
}

void perform_stacked_fit_step1(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
{
	theDATA1 = hFullSel1->Rebin(binsx.size() - 1, "theDATA1", &binsx[0]);
	theCDF1 = hCDF1;
	theCDF2 = hCDF2;
	thePDF1 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA
	thePDF2 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA

	TMinuit minuit;
//	minuit.SetErrorDef(1); // chi^2
	minuit.SetErrorDef(0.5); // nll
	minuit.SetPrintLevel(3);
	minuit.Command("SET STR 2");  // precision (slow) mode

	// define parameter 0 (median1), and fix it
	double median1 = median_from_cdf(theCDF1);
	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

	// set parameter 2 (shift1), and fix it
	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(2, "SHIFT1", newShift1, 1,-100, 100);

	// set parameter 3 (stretch1), and fix it
	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(3, "STRETCH1", newStretch1, newStretch1*0.01, 0.001, newStretch1*100);

	// define parameter 4 (median2), and fix it
	double median2 = median_from_cdf(theCDF2);
	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
//	minuit.DefineParameter(5, "AMP2", newAmp2, newAmp2*0.1, 0.0, newAmp2*100);
	minuit.DefineParameter(5, "AMP2", newAmp2, 0.01, 0.0, newAmp2*1000);

	// set parameter 6 (shift2), and fix it.
	minuit.DefineParameter(6, "SHIFT2", newShift2, 10, -5000, 5000);

	// set parameter 7 (stretch2), and fix it.
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.001, .01, newStretch2*10);
	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.1, .00001, 10000);
//	minuit.DefineParameter(7, "STRETCH2", 1.0, 0.0, 0.0, 0.0);

//	minuit.SetFCN(CHISQ_stack2); // set the function
	minuit.SetFCN(POISSONLL_stack2); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();
//	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();


	// get the parameters:
	minuit.GetParameter(1, newAmp1, newAmpe1);
	minuit.GetParameter(2, newShift1, newShifte1);
	minuit.GetParameter(3, newStretch1, newStretche1);  
	minuit.GetParameter(5, newAmp2, newAmpe2);
	minuit.GetParameter(6, newShift2, newShifte2);
	minuit.GetParameter(7, newStretch2, newStretche2);

	return;
}


void perform_stacked_fit_step2(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
{
	theDATA1 = hFullSel1->Rebin(binsx.size() - 1, "theDATA1", &binsx[0]);
	theCDF1 = hCDF1;
	theCDF2 = hCDF2;
	thePDF1 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA
	thePDF2 = (TH1*) theDATA1->Clone("thePDF");       // use the same binning as theDATA

	TMinuit minuit;
//	minuit.SetErrorDef(1); // chi^2
	minuit.SetErrorDef(0.5); // nll
	minuit.SetPrintLevel(3);
	minuit.Command("SET STR 2");  // precision (slow) mode

	// define parameter 0 (median1), and fix it
	double median1 = median_from_cdf(theCDF1);
	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

	// set parameter 2 (shift1), and fix it
	minuit.DefineParameter(2, "SHIFT1", newShift1, 1, -200, 200);
//	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);

	// set parameter 3 (stretch1), and fix it
	minuit.DefineParameter(3, "STRETCH1", newStretch1, newStretch1*0.01, 0.001, newStretch1*100);

	// define parameter 4 (median2), and fix it
	double median2 = median_from_cdf(theCDF2);
	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
	minuit.DefineParameter(5, "AMP2", newAmp2, 0.0, 0.0, 0.0);

	// set parameter 6 (shift2), and fix it.
	minuit.DefineParameter(6, "SHIFT2", newShift2, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 10, -5000, 5000);

	// set parameter 7 (stretch2), and fix it.
	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.1, 0.01, newStretch2*100);

//	minuit.SetFCN(CHISQ_stack2); // set the function
	minuit.SetFCN(POISSONLL_stack2); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();


	// get the parameters:
	minuit.GetParameter(1, newAmp1, newAmpe1);
	minuit.GetParameter(2, newShift1, newShifte1);
	minuit.GetParameter(3, newStretch1, newStretche1);  
	minuit.GetParameter(5, newAmp2, newAmpe2);
	minuit.GetParameter(6, newShift2, newShifte2);
	minuit.GetParameter(7, newStretch2, newStretche2);

	return;
}


void perform_stacked_fit_step3(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, TH1* hCDF3, vector<double> binsx, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2, double &newAmp3, double &newAmpe3, double &newShift3, double &newShifte3, double &newStretch3, double &newStretche3)
{
	theDATA1 = hFullSel1->Rebin(binsx.size() - 1, "theDATA1", &binsx[0]);
	theCDF1 = hCDF1;
	theCDF2 = hCDF2;
	theCDF3 = hCDF3;
	thePDF1 = (TH1*) theDATA1->Clone("thePDF1");
	thePDF2 = (TH1*) theDATA1->Clone("thePDF2");
	thePDF3 = (TH1*) theDATA1->Clone("thePDF3");

	TMinuit minuit;
	minuit.SetErrorDef(1); // chi^2
	minuit.SetPrintLevel(3);
	minuit.Command("SET STR 2");  // precision (slow) mode

	// define parameter 0 (median1), and fix it
	double median1 = median_from_cdf(theCDF1);
	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

	// set parameter 2 (shift1), and fix it
	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);

	// set parameter 3 (stretch1), and fix it
	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);

	// define parameter 4 (median2), and fix it
	double median2 = median_from_cdf(theCDF2);
	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
	minuit.DefineParameter(5, "AMP2", newAmp2, 0.0, 0.0, 0.0);

	// set parameter 6 (shift2), and fix it.
	minuit.DefineParameter(6, "SHIFT2", newShift2, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 10, -5000, 5000);

	// set parameter 7 (stretch2), and fix it.
	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.1, 0.01, newStretch2*100);

	// define parameter 8 (median3), and fix it
	double median3 = median_from_cdf(theCDF3);
	minuit.DefineParameter(8, "MEDIAN3", median3, 0.0, 0.0, 0.0);

	// define parameter 9 (amplitude3) and bound the amplitude by 0 from below
	minuit.DefineParameter(9, "AMP3", newAmp3, newAmp3*0.1, 0.0, newAmp3*100);

	// set parameter 10 (shift3), and fix it.
	minuit.DefineParameter(10, "SHIFT3", newShift3, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(10, "SHIFT3", newShift3, 10, -5000, 5000);

	// set parameter 11 (stretch3), and fix it.
	minuit.DefineParameter(11, "STRETCH3", newStretch3, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(11, "STRETCH3", newStretch3, newStretch3*0.1, 0.01, newStretch3*100);

	minuit.SetFCN(CHISQ_stack3); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();
//	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();


	// get the parameters:
	minuit.GetParameter(1, newAmp1, newAmpe1);
	minuit.GetParameter(2, newShift1, newShifte1);
	minuit.GetParameter(3, newStretch1, newStretche1);
	minuit.GetParameter(5, newAmp2, newAmpe2);
	minuit.GetParameter(6, newShift2, newShifte2);
	minuit.GetParameter(7, newStretch2, newStretche2);
	minuit.GetParameter(9, newAmp3, newAmpe3);
	minuit.GetParameter(10, newShift3, newShifte3);
	minuit.GetParameter(11, newStretch3, newStretche3);

	return;
}


void perform_stacked_fit_step3_null(TH1* hFullSel1, TH1* hCDF1, TH1* hCDF2, vector<double> binsx, double &newAmp1, double &newAmpe1, double &newShift1, double &newShifte1, double &newStretch1, double &newStretche1, double &newAmp2, double &newAmpe2, double &newShift2, double &newShifte2, double &newStretch2, double &newStretche2)
{
	theDATA1 = hFullSel1->Rebin(binsx.size() - 1, "theDATA1", &binsx[0]);
	theCDF1 = hCDF1;
	theCDF2 = hCDF2;
	thePDF1 = (TH1*) theDATA1->Clone("thePDF1");
	thePDF2 = (TH1*) theDATA1->Clone("thePDF2");

	TMinuit minuit;
	minuit.SetErrorDef(1); // chi^2
	minuit.SetPrintLevel(3);
	minuit.Command("SET STR 2");  // precision (slow) mode

	// define parameter 0 (median1), and fix it
	double median1 = median_from_cdf(theCDF1);
	minuit.DefineParameter(0, "MEDIAN1", median1, 0.0, 0.0, 0.0);

	// define parameter 1 (amplitude1) and bound the amplitude by 0 from below
	minuit.DefineParameter(1, "AMP1", newAmp1, newAmp1*0.1, 0.0, newAmp1*100);

	// set parameter 2 (shift1), and fix it
	minuit.DefineParameter(2, "SHIFT1", newShift1, 0.0, 0.0, 0.0);

	// set parameter 3 (stretch1), and fix it
	minuit.DefineParameter(3, "STRETCH1", newStretch1, 0.0, 0.0, 0.0);

	// define parameter 4 (median2), and fix it
	double median2 = median_from_cdf(theCDF2);
	minuit.DefineParameter(4, "MEDIAN2", median2, 0.0, 0.0, 0.0);

	// define parameter 5 (amplitude2) and bound the amplitude by 0 from below
	minuit.DefineParameter(5, "AMP2", newAmp2, 0.0, 0.0, 0.0);

	// set parameter 6 (shift2), and fix it.
	minuit.DefineParameter(6, "SHIFT2", newShift2, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(6, "SHIFT2", newShift2, 10, -5000, 5000);

	// set parameter 7 (stretch2), and fix it.
	minuit.DefineParameter(7, "STRETCH2", newStretch2, 0.0, 0.0, 0.0);
//	minuit.DefineParameter(7, "STRETCH2", newStretch2, newStretch2*0.1, 0.01, newStretch2*100);

	minuit.SetFCN(CHISQ_stack2); // set the function
	double tmp[1] = { 5000. }; int err;
	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();
//	minuit.mnexcm("MIGRAD", tmp, 1, err); // execute Minuit with MIGRAD
//	minuit.mnmnos();


	// get the parameters:
	minuit.GetParameter(1, newAmp1, newAmpe1);
	minuit.GetParameter(2, newShift1, newShifte1);
	minuit.GetParameter(3, newStretch1, newStretche1);
	minuit.GetParameter(5, newAmp2, newAmpe2);
	minuit.GetParameter(6, newShift2, newShifte2);
	minuit.GetParameter(7, newStretch2, newStretche2);

	return;
}

void print_params(TH1* params) {
	nparams = params->GetNbinsX();
	for (int i=1; i <= nparams; ++i) {
		int group = (i-1)/3 + 1;
		cout << param_names[(i-1)%3] << group << " = " << params->GetBinContent(i) << " +/- " << params->GetBinError(i) << endl;
	}
	
}
