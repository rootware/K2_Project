// Hello_World.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include "dipoleformulaeSItwo.h"
#include "addLBCandUBCtwo.h"
#include <boost/math/constants/constants.hpp>


using namespace std;


string OVERALL_ADD = "C:/Users/Saad/Desktop/ChorusMatrix_20130317_20130319/ChorusMatrix_20130317_20130319/";
double L_list[] = { 3.0,3.5,4.0,4.5,5.0,5.5,6.0,6.5,7.0 };
double Energy_List[71];
double pitchangle_List[46];

vector<int> range(int start, int end, int step) {
	vector<int> list;
	list.reserve((int)((end - start + 1) / ((float)step)) + 1);

	for (int i = start; i <= end; i += step)
		list.push_back(i);

	list.shrink_to_fit();
	return list;



}

int main()
{
	readCoordinates(); //needed
	add_LBC_and_UBC(); // toggle these on and off if needed

	cout << "Program completed";


	cin.get();

}


