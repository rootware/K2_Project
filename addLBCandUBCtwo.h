#include "stdafx.h"
#include <fstream>

#ifndef ADDLBCANDUBCtwo_H
#define ADDLBCANDUBCtwo_H
using namespace std;

extern double L_list[];
extern vector<int> range(int, int, int);

void getridofHeader(ifstream * myfilex);

void add_LBC_and_UBC();

void readCoordinates();
#endif
