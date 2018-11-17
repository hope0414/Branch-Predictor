#include <math.h>
#include <iostream>
#include <iomanip> 
#include "sim_bp.h"
using namespace std;

Bimodal::Bimodal(unsigned long int m) {
	tableNmb = pow(2, m);
	mask = (1 << m) - 1;
	Prediction_table = new int[tableNmb];
	prediction = 0;
	misprediction = 0;
	for (int i = 0; i < tableNmb; i++) {
		Prediction_table[i] = 2;
	}

}

void Bimodal::function(unsigned long int address, char result){
	unsigned long int index;
	int preResult;
	index = (address >> 2) & mask;
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
	}
	else {
		if(Prediction_table[index] != 0)
			Prediction_table[index]--;
		if(preResult)
			misprediction++;	

	}
}


void Bimodal::print() {
	rate = double (misprediction) / prediction * 100;
	cout << "OUTPUT" << endl;
	cout << " number of predictions:    " << prediction << endl;
	cout << " number of mispredictions: " << misprediction << endl;
	cout << " misprediction rate:       " << fixed << setprecision(2) << rate << "%" << endl;
	cout << "FINAL BIMODAL CONTENTS" << endl;
	for (int i = 0; i < tableNmb; i++) {
		cout << " " << i << "\t" << Prediction_table[i] << endl;
	}

}


