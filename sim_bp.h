#ifndef SIM_BP_H
#define SIM_BP_H

typedef struct bp_params{
    unsigned long int K;
    unsigned long int M1;
    unsigned long int M2;
    unsigned long int N;
    char*             bp_name;
}bp_params;

// Put additional data structures here as per your requirement


class Bimodal {
public:
	int tableNmb;
	unsigned long int mask;
	int *Prediction_table;
	int prediction;	
	int misprediction;
	double rate;

	Bimodal(unsigned long int);

	void function(unsigned long int, char);

	void print();
};

class Gshare {

public:
	int tableNmb;
	unsigned long int maskM;
	unsigned long int maskN;
	int *Prediction_table;
	int prediction;	
	int misprediction;
	double rate;
	unsigned long int table;

	Gshare (unsigned long int, unsigned long int);

	void function(unsigned long int, char, unsigned long int, unsigned long int);

	void print();


};

class Hybrid{

public:
	int tableNmbH;
	int tableNmbB;
	int tableNmbG;
	unsigned long int maskH;
	unsigned long int maskM;
	unsigned long int maskN;
	unsigned long int maskB;
	int *Prediction_tableB;
	int *Prediction_tableH;
	int *Prediction_tableG;
	int prediction;
	int misprediction;
	double rate;
	unsigned long int table;
	Hybrid(unsigned long int, unsigned long int, unsigned long int, unsigned long int);

	void function(unsigned long int, char, unsigned long int, unsigned long int);

	void print();


};

#endif
