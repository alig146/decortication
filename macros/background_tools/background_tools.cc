bool DEBUG = false;

TH1 *make_self_convolution(TH1 *h, TString name="", double masy_cut=0.1) {
	// Convolute the input histogram with itself.
	
	// Prepare the output histogram and define some basic variables:
	/// If a new name isn't supplied, append "_conv" to the histogram's name:
	if (!name[0]) name = h->GetName() + TString("_conv");
	/// Basic variables:
	int nbins = h->GetNbinsX();
	/// Make output histogram:
	TH1 *conv = (TH1*) h->Clone(name);
	
	// Do the convolution:
	for (int ibin = 1; ibin <= nbins; ibin++) {
		for (int jbin = ibin; jbin <= nbins; jbin++) {
			double m0 = h->GetXaxis()->GetBinCenter(ibin);
			double m1 = h->GetXaxis()->GetBinCenter(jbin);
			double masy = fabs((m0 - m1)/(m0 + m1));
			double mavg = (m0 + m1)/2;
			if (masy < masy_cut) conv->Fill(mavg, h->GetBinContent(ibin)*h->GetBinContent(jbin));
		}
	}
	
	// Get rid of errors:
	for(int ibin = 0; ibin <= conv->GetNbinsX() + 1; ibin++) conv->SetBinError(ibin, 0);
	
	// Normalize the convolution to the original histogram:
//	conv->Scale(h->Integral()/conv->Integral());
	
	return conv;
}



TH1* make_cdf(TH1 *h, TString name="") {
	if (!name[0]) name = h->GetName() + TString("_cdf");
	TH1 *cdf = (TH1*) h->Clone(name);
	
	for (int ibin = 0; ibin <= h->GetNbinsX() + 1; ibin++) {
		double integral = 0;
		for (int jbin = 0; jbin < ibin; jbin ++) integral += h->GetBinContent(jbin);
		cdf->SetBinContent(ibin, integral);
		cdf->SetBinError(ibin, 0);
	}
	
	return cdf;
}


double evaluate_cdf(TH1* cdf, double x)
{
	int bin = cdf->GetXaxis()->FindBin(x);
	double edge_low = cdf->GetXaxis()->GetBinLowEdge(bin);
	double edge_high = cdf->GetXaxis()->GetBinUpEdge(bin);
	double bin_value = cdf->GetBinContent(bin);
	double nextbin_value = cdf->GetBinContent(bin + 1);
	
	double evaluation = (nextbin_value - bin_value)/(edge_high - edge_low)*(x - edge_low) + bin_value;
	if(DEBUG) std::cout << "x=" << x << "; bin=" << bin << "; edge_low=" << edge_low
		<< "; edge_high=" << edge_high << "; bin_value=" << bin_value
		<< "; nextbin_value=" << nextbin_value << "; evaluation=" << evaluation << std::endl;
	
	return evaluation;
}


void differentiate_cdf(TH1* cdf, TH1* out, double peak, double amplitude=1.0, double shift=0.0, double stretch=1.0)
{
//	cout << peak << "  " << amplitude << "  " << shift << "  " << stretch << endl;
	assert(stretch > 0.0);
	for(int i = 0; i <= out->GetNbinsX() + 1; i++) {
		double lo=out->GetXaxis()->GetBinLowEdge(i);
		double hi=out->GetXaxis()->GetBinUpEdge(i);
		
		double loprime=1./stretch*(lo-peak-shift)+peak;
		double hiprime=1./stretch*(hi-peak-shift)+peak;
		
		double y1=evaluate_cdf(cdf, loprime);
		double y2=evaluate_cdf(cdf, hiprime);
		
		double val=amplitude*(y2-y1);

		if(DEBUG) cout << "lo=" << lo << "; hi=" << hi << "; loprime=" << loprime << "; hiprime=" << hiprime
			<< "; y1=" << y1 << "; y2=" << y2 << "; val=" << val << endl;
		
		out->SetBinContent(i, val);
		out->SetBinError(i, 0.);
	}
	
	return;
}



// Finds the median of a distribution based on half-max point of a
// CDF.  Caveat emptor if the distribution is not monotonically
// increasing!
double median_from_cdf(TH1* cdf)
{
	double max=cdf->GetMaximum();
	double curval, preval=cdf->GetBinContent(0);
	int nbins=cdf->GetNbinsX()+1;
	for(int i=0; i<=nbins+1; i++) {
		curval=cdf->GetBinContent(i);
		if(curval>=max/2.0 && preval<max/2.0) {
			return cdf->GetXaxis()->GetBinLowEdge(i);
		}
	}
	std::cerr << "Could not find the median!!!" << std::endl;
	return cdf->GetXaxis()->GetBinUpEdge(nbins);
}
