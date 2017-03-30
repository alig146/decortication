double correction_function(double x, TString ds, TString cut) {
	if (cut == "sig" || cut == "sigp") {
		if (ds == "qcdmg") return 1.1e16*pow(x, -4.7);
		else if (ds == "qcdp") return 1.3e18*pow(x, -5.5);
		else if (ds == "jetht" || ds == "jetht16") return 1.1e16*pow(x, -4.7);
	}
	if (cut == "sigl") {
		if (ds == "qcdmg") return 1.1e16*pow(x, -4.7);
		else if (ds == "qcdp") return 1.3e18*pow(x, -5.5);
		else if (ds == "jetht" || ds == "jetht16") return 1.1e16*pow(x, -4.7);
	}
	else if (cut == "sb" || cut == "sbp" || cut == "sbb") {
//		if (ds == "qcdmg") return 4.2e18*pow(x, -5.5);		// 2015
		if (ds == "qcdmg") return 6.3e19*pow(x, -5.5);		// 2016
//		else if (ds == "qcdp") return 1.3e19*pow(x, -5.7);		// 2015
		else if (ds == "jetht" || ds == "jetht16") return 1.1e19*pow(x, -5.3);		// 2016
	}
	else if (cut == "sbl" || cut == "sblb") {
		if (ds == "qcdmg") return 6.3e20*pow(x, -5.6);		// 2016
//		else if (ds == "qcdp") return 1.3e19*pow(x, -5.7);
		else if (ds == "jetht" || ds == "jetht16") return 9.6e19*pow(x, -5.4);
	}
	else if (cut == "sbt" || cut == "sbtb") {
		if (ds == "qcdmg") return 5.1e18*pow(x, -5.5);		// 2016
		else if (ds == "jetht" || ds == "jetht16") return 1.6e17*pow(x, -5.1);		// 2016
	}
	else if (cut == "sb2") {
		if (ds == "qcdmg") return 1.6e15*pow(x, -4.6);
		else if (ds == "qcdp") return 5.5e15*pow(x, -4.8);
		else if (ds == "jetht" || ds == "jetht16") return 1.1e13*pow(x, -3.9);
	}
	else if (cut == "sb2b") {		// Due to statistics, these are the same as "sb2" above. (?)
		if (ds == "qcdmg") return 1.6e15*pow(x, -4.6);
		else if (ds == "qcdp") return 5.5e15*pow(x, -4.8);
		else if (ds == "jetht" || ds == "jetht16") return 1.1e13*pow(x, -3.9);
	}
	else if (cut == "sb22") {
		if (ds == "qcdmg") return 2.7e13*pow(x, -4.3);
		else if (ds == "qcdp") return 2.2e19*pow(x, -6.2);
	}
	else if (cut == "sb3") {
		if (ds == "qcdmg") return 1.0e13*pow(x, -3.9);
		else if (ds == "qcdp") return 8.7e11*pow(x, -3.6);
	}
	cout << "[!!] Correction function error: " << ds << ", " << cut << endl;
	return 0;
}
