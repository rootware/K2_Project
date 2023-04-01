// generate files that add the LBC and UBC.
// One alternate would be to only read the files in, and not output them
// you lose a certain amount of formatting when printing files.
//
// test for what happens if the coordinates don't match in the two files.
//aka missing or just floating point error
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/math/constants/constants.hpp>
#include "addLBCandUBCtwo.h"
#include "dipoleformulaeSItwo.h"

using namespace std;

extern double L_list[];
extern string OVERALL_ADD;
extern double Energy_List[];
extern double pitchangle_List[];
void getridofHeader(ifstream * myfilex) {
	int line_counter = 1;
	string line;
	while (line_counter <= 10 && getline(*myfilex, line)) line_counter++;
}


void add_LBC_and_UBC() {

	extern string OVERALL_ADD;
	string UBCfolder = "UBC_BavD_t_l_mlt/";
	string LBCfolder = "LBC_BavD_t_l_mlt/";
	string DAY[] = { "UT20130317-","UT20130318-" };
	string file_prefix[] = { "LBC_BavD_", "UBC_BavD_" };

	string sL_list[10];
	boost::format fmt("%.1f");
	for (int i = 0; i < 10; i++) {
		fmt % L_list[i];
		sL_list[i] = fmt.str();
	};

	string HOUR[24];
	fmt = boost::format("%02d");
	vector<int> list = range(0, 23, 1);
	for (int i = 0; i < 24; i++) {
		fmt % list[i];
		HOUR[i] = fmt.str();
	};

	string MLT[] = { "00to04", "04to08", "08to12", "20to24" };


	double DaaA[71][46], DppA[71][46], DapA[71][46];// DaEA[71][46], DEEA[71][46];
	double sigma[3] = {};
	double bv[2] = {};
	string outfile = "C:/Users/Saad/Desktop/output/mastersi.txt";
	ofstream myfile(outfile);
	string errfilename = "C:/Users/Saad/Desktop/output/errfilemastersi.txt";
	ofstream errfile(errfilename);

	cout << c;

	for (int day = 0; day < 2; day++) {
		for (int hour = 0; hour < 24; hour++) {
			for (int l = 0; l < 9; l++) {
				for (int mlt = 0; mlt < 4; mlt++) {

					double L;
					double tothours = day * 24 + hour;
					int  defcon = 0;

					//Define variables for 1_LBC, 2_UBC, so that they can be then added together


					string filename1 = OVERALL_ADD + LBCfolder + DAY[day] + HOUR[hour] + "/" + file_prefix[0] + DAY[day] + HOUR[hour] + "_L" + sL_list[l] + "_MLT" + MLT[mlt] + ".txt";
					string filename2 = OVERALL_ADD + UBCfolder + DAY[day] + HOUR[hour] + "/" + file_prefix[1] + DAY[day] + HOUR[hour] + "_L" + sL_list[l] + "_MLT" + MLT[mlt] + ".txt";
					//string outfile = "C:/Users/Saad/Desktop/output/BavD_" + DAY[day] + HOUR[hour] + "_L" + sL_list[l] + "_MLT" + MLT[mlt] + ".txt";

					ifstream myfile1(filename1);
					ifstream myfile2(filename2);

					// read file
					if (myfile1.is_open() && myfile2.is_open()) {

						//read file
						getridofHeader(&myfile1);
						getridofHeader(&myfile2);
						double errorcounter = 0;

						for (int Eindex = 0; Eindex < 71; Eindex++) {
							for (int aindex = 0; aindex < 46; aindex++) {
								double L1, E1, alpha1, Daa1, Dpp1, Dap1, DaE1, DEE1;
								double L2, E2, alpha2, Daa2, Dpp2, Dap2, DaE2, DEE2;
								double E, alpha;

								if (myfile1.eof() || myfile2.eof()) cout << "God help us";
								myfile1 >> L1 >> E1 >> alpha1 >> Daa1 >> Dpp1 >> Dap1 >> DaE1 >> DEE1;
								myfile2 >> L2 >> E2 >> alpha2 >> Daa2 >> Dpp2 >> Dap2 >> DaE2 >> DEE2;

								if (L1 != L2 || alpha1 != alpha2 || E1 != E2) {
									defcon = 5;
									cout << "It's not just that it's zero";
									goto stop;

								}
								else {
									L = L_list[l];
									alpha = pitchangle_List[aindex];
									E = Energy_List[Eindex];
									DaaA[Eindex][aindex] = (Daa1 + Daa2)*p2(E);
									DppA[Eindex][aindex] = (Dpp1 + Dpp2) *p2(E);
									DapA[Eindex][aindex] = (Dap1 + Dap2) *p2(E);
									//DaEA[Eindex][aindex] = (DaE1 + DaE2) / TIME;
									//DEEA[Eindex][aindex] = (DEE1 + DEE2) / TIME;

								}

							}
						}
						//end read file

						myfile1.close();
						myfile2.close();
					}
					// all file reading done
					int counter = 0;
					// calculate variables from arrays

					for (int aindex = 0; aindex < 46; aindex++) {
						for (int Eindex = 0; Eindex < 71; Eindex++) {
							counter++;
							double E, alpha;
							E = Energy_List[Eindex];
							alpha = pitchangle_List[aindex];

							double Daa, Dpp, Dap;

							Daa = DaaA[Eindex][aindex];

							Dpp = DppA[Eindex][aindex];
							Dap = DapA[Eindex][aindex];
							//DaE = DaEA[Eindex][aindex];
							//DEE = DEEA[Eindex][aindex];
							//calculate sigma
							sigma[0] = sqrt(2 * Daa / p2(E));

							if (abs(Daa) <= 1e-100) {
								sigma[1] = 0;
							}
							else {
								sigma[1] = sqrt(2)*Dap / sqrt(Daa);
							}

							double temp = 2 * Dpp - pow(sigma[1], 2);
							//check for whether this is zero, otherwise the sqrt term returns NaN
							if (abs(temp) <= 1e-35 && temp<0) {
								sigma[2] = 0;
							}
							else {
								//if (temp < 0) cout << temp << '\t' << sigma[0] << '\t' << sigma[1] << endl;
								sigma[2] = sqrt(temp);
							}


							//calculate the b coefficients
							double bv[2] = { 0.0,0.0 };
							double p = sqrt(p2(E));
							double PI = boost::math::constants::pi<double>();
							double G = G_pa(p2(E), alpha / 180.0 * PI);

							int a1 = -1; int a2 = -1; int e1 = -1; int e2 = -1;
							if (aindex != 0 && aindex != 45) {
								a1 = aindex - 1; a2 = aindex + 1;

							}
							else if (aindex == 0) {
								a1 = aindex; a2 = aindex + 1;
							}
							else {
								a1 = aindex - 1; a2 = aindex;

							};

							if (Eindex != 0 && Eindex != 70) {
								e1 = Eindex - 1; e2 = Eindex + 1;

							}
							else if (Eindex == 0) {
								e1 = Eindex; e2 = Eindex + 1;
							}
							else {
								e1 = Eindex - 1; e2 = Eindex;
								if (Eindex != 70) cout << "FUCK";
							};


							double da = (pitchangle_List[a2] - pitchangle_List[a1])*PI / 180.0;
							double ke = E*MeV;

							double dp1 = (log(Energy_List[e2]) - log(Energy_List[e1]))*(ke + E0)*ke / (c*c*p);
							double dp = (log(Energy_List[e2]) - log(Energy_List[e1]))*(sqrt(p*p*c*c + E0*E0) - E0)*sqrt(p*p*c*c + E0*E0) / (c*c*p);

							double dF1_a = 0.0, dF1_p = 0.0, dF2_a = 0.0, dF2_p = 0.0;


							//if (DaaA[Eindex][a2] != 0 || DaaA[Eindex][a1]!=0) 
							dF1_a = (G_pa(p2(E), pitchangle_List[a2] * PI / 180.0)*DaaA[Eindex][a2] - G_pa(p2(E), pitchangle_List[a1] * PI / 180.0)*DaaA[Eindex][a1]) / p;
							//if (DapA[e2][aindex] != 0 || DapA[e1][aindex] != 0) 
							dF1_p = (G_pa(p2(Energy_List[e2]), pitchangle_List[aindex] * PI / 180.0)*DapA[e2][aindex] / sqrt(p2(Energy_List[e2])) - G_pa(p2(Energy_List[e1]), pitchangle_List[aindex] * PI / 180.0)*DapA[e1][aindex] / sqrt(p2(Energy_List[e1])));

							//if (DapA[Eindex][a2] != 0 || DapA[Eindex][a1] != 0) 
							dF2_a = G_pa(p2(E), pitchangle_List[a2] * PI / 180.0)*DapA[Eindex][a2] - G_pa(p2(E), pitchangle_List[a1] * PI / 180.0)*DapA[Eindex][a1];
							//if (DppA[e2][aindex] != 0 || DppA[e1][aindex] != 0) 
							dF2_p = G_pa(p2(Energy_List[e2]), pitchangle_List[aindex] * PI / 180.0)*DppA[e2][aindex] - G_pa(p2(Energy_List[e1]), pitchangle_List[aindex] * PI / 180.0)*DppA[e1][aindex];



							bv[0] = 1 / (G*p)*dF1_a / da + 1 / G*dF1_p / dp;
							bv[1] = 1 / (G*p)*dF2_a / da + 1 / G*dF2_p / dp;


							/*	if (bv[0] > 1e4 || bv[1] > 1e4) {
							cout << "LARGE B\n E \t alpha \t G \t da \t dp\t dF1_a \t dF1_p" << endl;
							cout << E << '\t' << alpha <<'\t'<<G<<'\t'<<da<<'\t'<<dp<<'\t'<<dF1_a<<'\t'<<dF1_a <<endl;
							}*/



							//output to master file here
							ios::fmtflags f(myfile.flags());
							//myfile << tothours << '\t' << L << '\t' << mlt << '\t' << alpha << '\t' << std::setprecision(7) << std::scientific << E << '\t' << Daa << '\t' << Dpp << '\t' << Dap << '\t' << DaE << '\t' << DEE << '\t' << sigma[0] << '\t' << sigma[1] << '\t' << sigma[2] << '\t' << bv[0] << '\t' << bv[1] << endl;
							myfile << tothours << '\t' << L << '\t' << mlt << '\t' << alpha << '\t' << std::setprecision(7) << std::scientific << E << '\t' << sigma[0] << '\t' << sigma[1] << '\t' << sigma[2] << '\t' << bv[0] << '\t' << bv[1] << endl;
							//myfile <<  alpha << '\t' << std::setprecision(7) << std::scientific << E << '\t' << Daa<< '\t' << sigma[0] << endl;
							myfile.flags(f);
						}
					}
					// end calculating values for each file

					if (counter != 71 * 46) cout << "Doesn't match";
				stop:
					if (defcon == 5) errfile << filename1 << endl;

				}
			}
			cout << "Current number of total hours:\t" << 24 * day + hour << endl;
		}

	}
	myfile.close();
	errfile.close();


}

void readCoordinates() {




	string Energyfile = OVERALL_ADD + "Energy_71.txt";
	string Anglefile = OVERALL_ADD + "PitchAngle_46.txt";

	ifstream myfile(Energyfile);
	if (myfile.is_open()) {
		for (int i = 0; i < 71; i++)myfile >> Energy_List[i];


	}
	else cout << "Energyfile not open";

	ifstream myfile2(Anglefile);
	if (myfile2.is_open()) {
		for (int i = 0; i < 46; i++)myfile2 >> pitchangle_List[i];


	}
	else cout << "Pitch angle file not open";

	myfile.close();
	myfile2.close();


}

