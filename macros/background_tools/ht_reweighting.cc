//bool check_reweight(TString cut) {;

TString reweight_path = "background_tools/ht_reweighting_functions/";

double correction_function(double x, TString ds, TString cut, TString dir="", int f=1) {
//	if (ds == "jetht") ds = "qcdmg";		// Use qcdmg corrections for data.
	if (cut == "sbb") cut = "sb";
	if (cut == "sblb") cut = "sbl";
	if (cut == "pretsblb") cut = "pretsbl";
	if (cut == "sbl42b") cut = "sbl42";
	if (cut == "sbl43b") cut = "sbl43";
	if (cut == "sbtb") cut = "sbt";
	if (cut == "sbsb") cut = "sbs";
	if (cut == "sbideb") cut = "sbide";
	if (cut == "sig15") cut = "sig";
	TString fname = "reweight_functions_" + cut + ".root";
	TFile* tf_in = TFile::Open(TString(getenv("CMSSW_BASE")) + "/src/Deracination/Straphanger/test/decortication/macros/" + reweight_path + fname);
//	TFile* tf_in = TFile::Open("/home/tote/decortication/macros/background_tools/ht_reweighting_functions/reweight_functions_" + cut + ".root");		// FIND LOCATION BETTER
	TString name = "f_" + ds + "_" + cut + "_f" + to_string(f);
	TF1* f1 = (TF1*) tf_in->Get(name);
	tf_in->Close();
	double value = f1->Eval(x);
	if (cut == "sig15") value = value/(35.923/2.258);
	return value;
}
