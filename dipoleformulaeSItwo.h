#ifndef DIPOLEFORMULAESItwo_H
#define DIPOLEFORMULAESItwo_H

static double c;
static  double R;
static  double m0;
static double mu;
static double E0;
static double TIME;
static double sec;
static double MeV;

void setval();

double M(double E, double y, double L);

double Y(double y);

double p2(double E);
double K(double y, double L);

double y(double K, double L);

double E(double M, double K, double L);


double T(double alpha0);
double G_pa(double psq, double alpha0);

double G_py(double psq, double y);



#endif


