#include <math.h>
#include <iostream>
#include <iomanip> 
#include "sim_bp.h"
using namespace std;

Gshare::Gshare(unsigned long int m, unsigned long int n) {
	tableNmb = pow(2, m);
	maskM = (1 << (m - n)) - 1;
	maskN = (1 << n) - 1;
	Prediction_table = new int[tableNmb];
	prediction = 0;
	misprediction = 0;
	for (int i = 0; i < tableNmb; i++) {
		Prediction_table[i] = 2;
	}
	table = 0;
}


void Gshare::function(unsigned long int address, char result, unsigned long int m, unsigned long int n){
	unsigned long int indexA;
	unsigned long int indexB;

	unsigned long int index;
	int preResult;
	
	indexA = (table & maskN) ^ (address >> (2 + m - n) & maskN);
	indexB = (address >> 2) & maskM;
	index = (indexA << (m - n)) | indexB;
	prediction++;

	if (Prediction_table[index] >= 2) {
		preResult = 1; //Taken


	}
	else {
		preResult = 0; //Not taken

	}

	if (result == 't') {
		if (Prediction_table[index] != 3) {
			Prediction_table[index]++;
			}
		if(!preResult)
			misprediction++;
		table = (1 << (n - 1)) | (table >> 1);
	}
	else {
		if(Prediction_table[index] != 0)
			Prediction_table[index]--;
		if(preResult)
			misprediction++;
		table = ((1 << n) - 1) & (table >> 1);
	
	}
	
}


void Gshare::print() {
	rate = double (misprediction) / prediction * 100;
	cout << "OUTPUT" << endl;
	cout << " number of predictions:    " << prediction << endl;
	cout << " number of mispredictions: " << misprediction << endl;
	cout << " misprediction rate:       " << fixed << setprecision(2) << rate << "%" << endl;
	cout << "FINAL GSHARE CONTENTS" << endl;
	for (int i = 0; i < tableNmb; i++) {
		cout << " " << i << "\t" << Prediction_table[i] << endl;
	}

}



