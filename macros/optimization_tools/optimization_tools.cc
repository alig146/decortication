#include "zbi.cc"

double significance_1(double s, double b, double se=0, double be=0) {
	return s/sqrt(b);
}
double significance_2(double s, double b, double se=0, double be=0) {
	return s/sqrt(s + b);
}
double significance_3(double s, double b, double se=0, double be=0) {
	return sqrt(s + b) - sqrt(b);
}
double significance_4(double s, double b, double se=0, double be=0) {
	double value = expectedZbi(s, b, b*0.1);
	if (value < 0) value = 0;
	return value;
}

double significance(int kind, double s, double b, double se=0, double be=0) {
	if (kind == 1) return s/sqrt(b);
	if (kind == 2) return s/sqrt(s + b);
	if (kind == 3) return sqrt(s + b) - sqrt(b);
	if (kind == 4) return significance_4(s, b, 0, b*0.1);
	return 0;
}
