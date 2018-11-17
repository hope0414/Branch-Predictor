#include <math.h>
#include <iostream>
#include <iomanip> 
#include "sim_bp.h"
using namespace std;

Hybrid::Hybrid(unsigned long int k, unsigned long int m1, unsigned long int n, unsigned long int m2) {
	tableNmbH = pow(2, k);
	tableNmbB = pow(2, m2);
	tableNmbG = pow(2, m1);

	maskB = (1 << m2) - 1;
	maskH = (1 << k) - 1;
	//gshare mask
	maskM = (1 << (m1 - n)) - 1;
	maskN = (1 << n) - 1;
	//table
	Prediction_tableB = new int[tableNmbB];
	Prediction_tableG = new int[tableNmbG];
	Prediction_tableH = new int[tableNmbH];
	//counters
	prediction = 0;
	misprediction = 0;

	for (int i = 0; i < tableNmbB; i++) {
		Prediction_tableB[i] = 2;
	}
	for (int i = 0; i < tableNmbG; i++) {
		Prediction_tableG[i] = 2;
	}
	for (int i = 0; i < tableNmbH; i++) {
		Prediction_tableH[i] = 1;
	}
	table = 0;
}


void Hybrid::function(unsigned long int address, char result, unsigned long int m1, unsigned long int n) {
	unsigned long int indexA;
	unsigned long int indexB;
	unsigned long int index1; //gshare

	unsigned long int index2; //bimodal

	unsigned long int index3; //hybrid
	int preResultB;
	int preResultG;
	//int preResult;

	int select; // select = 0 -> bimodal; select = 1 -> gshare

	indexA = (table & maskN) ^ (address >> (2 + m1 - n) & maskN);
	indexB = (address >> 2) & maskM;
	index1 = (indexA << (m1 - n)) | indexB; //gshare

	index2 = (address >> 2) & maskB; //bimodal

	index3 = (address >> 2) & maskH;

	prediction++;

	if (Prediction_tableH[index3] >= 2) {
		select = 1;
		
	}
	else {
		select = 0;

	}

	if (Prediction_tableG[index1] >= 2) {
		preResultG = 1;
	}
	else
		preResultG = 0;

	if (Prediction_tableB[index2] >= 2) {
		preResultB = 1;
	}
	else
		preResultB = 0;


	//update predictor and register table
	if (result == 't') {
		if (select) {
			if (Prediction_tableG[index1] != 3) {
				Prediction_tableG[index1]++;
			}
			if (!preResultG)
				misprediction++;

		}
		else {
			if (Prediction_tableB[index2] != 3) {
				Prediction_tableB[index2]++;
			}
			if (!preResultB)
				misprediction++;
		}
		table = (1 << (n - 1)) | (table >> 1);

		if (preResultG && !preResultB) {
			if (Prediction_tableH[index3] != 3) {
				Prediction_tableH[index3]++;
			}
		}
		else if (!preResultG && preResultB) {
			if (Prediction_tableH[index3] != 0) {
				Prediction_tableH[index3]--;
			}
		}

		
	}
	else {
		if (select) {
			if (Prediction_tableG[index1] != 0) {
				Prediction_tableG[index1]--;
			}
			if (preResultG)
				misprediction++;
		}
		else {
			if (Prediction_tableB[index2] != 0) {
				Prediction_tableB[index2]--;
			}
			if (preResultB)
				misprediction++;
		}
		table = ((1 << n) - 1) & (table >> 1);
		
		if (!preResultG && preResultB) {
			if (Prediction_tableH[index3] != 3) {
				Prediction_tableH[index3]++;
			}
		}
		else if (preResultG && !preResultB) {
			if (Prediction_tableH[index3] != 0) {
				Prediction_tableH[index3]--;
			}
		}

	}

}


void Hybrid::print() {
	rate = double(misprediction) / prediction * 100;
	cout << "OUTPUT" << endl;
	cout << " number of predictions:    " << prediction << endl;
	cout << " number of mispredictions: " << misprediction << endl;
	cout << " misprediction rate:       " << fixed << setprecision(2) << rate << "%" << endl;
	cout << "FINAL CHOOSER CONTENTS" << endl;
	for (int i = 0; i < tableNmbH; i++) {
		cout << " " << i << "\t" << Prediction_tableH[i] << endl;
	}
	cout << "FINAL GSHARE CONTENTS" << endl;
	for (int i = 0; i < tableNmbG; i++) {
		cout << " " << i << "\t" << Prediction_tableG[i] << endl;
	}
	cout << "FINAL BIMODAL CONTENTS" << endl;
	for (int i = 0; i < tableNmbB; i++) {
		cout << " " << i << "\t" << Prediction_tableB[i] << endl;
	}



}



