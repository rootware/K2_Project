#include "stdafx.h"
#include "boost/math/special_functions/pow.hpp"
#include "dipoleformulaeSItwo.h"

using namespace std;

void setval() {
	c = 2.99792458e10;
	R = 6375e5;
	m0 = 9.10938356e-28;
	mu = 0.311*R;
	E0 = m0*c*c;
	sec = 1;
	MeV = 1.6021766208e-6;
}



double p2(double E) {
	double convE = E *MeV;
	return (pow(convE + E0, 2) - pow(E0, 2)) / (c*c);
}

double M(double E, double y, double L) {
	return (p2(E)*pow(y, 2)*pow(L, 3)*pow(R, 3)) / (2 * m0*mu);
	;
}
/*
double Y(double y) {
return 2.760346 + 2.357194*y - 5.117540*pow(y, 3.0 / 4.0);
}


double K(double y, double L) {

return sqrt(mu / (L*R))*Y(y) / y;
}

double y(double K, double L) {
double kappa = sqrt(L*R / mu)*K;
return 1.0 / sqrt(1.0 + 1.35048*kappa - 0.030425*pow(kappa, 4.0 / 3.0) + 0.10066*pow(kappa, 5.0 / 3.0) + pow(kappa / 2.760346, 2.0));
}

double E(double M, double K, double L) {
return sqrt(2 * m0*mu*M / (pow(y(K, L), 2)*pow(L, 3)*pow(R, 3)) + E0*E0) - E0;
}*/

double T(double y) {
	/*
	http://www.ann-geophys.net/30/733/2012/angeo-30-733-2012.pdf
	*/

	return 1.380173 - 0.639693*pow(y, 4.0 / 3.0);
}
double G_pa(double psq, double alpha0) {

	return  psq*T(sin(alpha0))*sin(alpha0)*cos(alpha0);
}

/*
double G_py(double psq, double y) {
return psq*T(y)* y* sqrt(1 - y*y);

}*/
