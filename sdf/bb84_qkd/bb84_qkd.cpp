
#include "netxpto.h"
#include "binary_source.h"
#include "clock.h"
#include "single_photon_source.h"
#include "discrete_to_continuous_time.h"


int main()
{
	// #####################################################################################################
	// ########################################## Input Parameters #########################################
	// #####################################################################################################

	int NumberofSamplesPerSymbol{ 10 };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice Implementation
	Binary NUM_A{ "NUM_A.sgn" };
	ElectricalSignal CLK_A{ "CLK_A.sgn" };
	ElectricalSignal S_A1{ "S_A1.sgn" };
	PhotonStream S_A3;
	PhotonStream Q_C_1;
	ElectricalSignal S_A2{ "S_A2.sgn" };
	Messages C_C_1{ "C_C_1.sgn" };
	Messages C_C_6{ "C_C_1.sgn" };
	Binary Data_A{ "Data_A.sgn" };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	BinarySource BS1{ vector <Signal*> {}, vector <Signal*> {&NUM_A} };
	BS1.setMode( PseudoRandom );

	Clock clk1{ vector <Signal*> {}, vector <Signal*> {&CLK_A} };

	DiscreteToContinuousTime BS2{ vector <Signal*> {&CLK_A}, vector <Signal*> {&S_A1} };
	BS2.setNumberOfSamplesPerSymbol(NumberofSamplesPerSymbol);
	
	DiscreteToContinuousTime BS3{ vector <Signal*> {&NUM_A}, vector <Signal*> {&S_A2} };
	BS3.setNumberOfSamplesPerSymbol(NumberofSamplesPerSymbol);

	SinglePhotonSource BS4{ vector <Signal*> {&S_A1}, vector <Signal*> {&S_A3} };
	//BS4.setPolarization(S_A2);


	System MainSystem{ vector <Block*> {&BS1, &clk1, &BS2, &BS3, &BS4} };
	MainSystem.run();


    return 0;
}

