#pragma once

# include <algorithm>   // std::min
# include <string>		// compare
# include <numeric> 
# include "netxpto_20180118.h"
# include <vector>
# include <array>

using namespace std;

class entropy_estimator : public Block {


public:

	// Vars
	long int numberOfSamples{ -1 };
	int nBits;											// Total number of bits
	int minWindow;										// Minimum window size
	int p;
	double m, var;										// Mean and var

	//Methods
	entropy_estimator() {};
	entropy_estimator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);

	void setNumbBits(int N) { nBits = N; }				// Number of bits for analysis
	int getNumbBits() { return nBits; }

	void setMinWindowSize(int w) { minWindow = w; }		// Defines minimum window size	
	int getMinWindowSize() { return minWindow; }

	bool runBlock(void);

private:

	// Vars
	int count = 0;
	int n, window_size;
	int count_est = 0;
	int flag = 0;

	// Methods
	double compute_entropy(vector<int> h_store, int window);
	void print_to_file(vector<double> &h);
	void compute_mean_var(vector<double> &h);

};

