//#include "/home/tote/decortication/macros/common.cc"

double correction_function(double x, TString ds, TString cut, TString dir="fix", int f=0) {
//	if (ds == "jetht") ds = "qcdmg";		// Use qcdmg corrections for data.
//	if (cut == "sbb") cut = "sb";
//	if (cut == "sbtb") cut = "sbt";
//	if (cut == "sbsb") cut = "sbs";
//	if (cut == "sbideb") cut = "sbide";
	TFile* tf_in = TFile::Open("/home/tote/decortication/macros/background_tools/reweight_functions.root");
	TString name = "f_" + ds + "_" + cut + "_f" + to_string(f);
	if (cut == "sig15") name = "f_" + ds + "_sig" + "_f" + to_string(f);
//	if (dir != "") name = name + "_";
//	if (cut != "sig15") name = name + ds + "_" + cut;
//	else name = name + ds + "_sig";
	TF1* f1 = (TF1*) tf_in->Get(name);
	tf_in->Close();
	double value = f1->Eval(x);
	if (cut == "sig15") value = value/((29.128 + 2.183)/2.183);
	return value;
}
