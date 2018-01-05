
#include "netxpto.h"
#include <stdio.h>

#include "binary_source.h"
#include "clock_20171219.h"
#include "alice_qkd.h"
#include "single_photon_source_20171218.h"
#include "polarizer.h"
#include "sink.h"
#include "bob_qkd.h"
#include "rotator_linear_polarizer.h"
#include "polarization_beam_splitter.h"
#include "single_photon_detector.h"
#include "optical_switch.h"
#include "eve_qkd.h"

int main()
{
	// #####################################################################################################
	// ################################# System Input Parameters #########################################
	// #####################################################################################################

	double RateOfPhotons{ 1e3 };
	vector<t_iqValues> iqAmplitudeValues = { {-45.0,0.0},{0.0,0.0},{45.0,0.0},{90.0,0.0} };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice Implementation
	Binary NUM_A{ "NUM_A.sgn" };
	Binary Bin_1{ "Bin_1.sgn" };
	Binary Bin_2{ "Bin_2.sgn" };
	Binary Bin_1out{ "out_teste.sgn" };
	Binary MI_A{ "MI_A.sgn" };
	TimeContinuousAmplitudeContinuous CLK_A{"CLK_A.sgn"};
	TimeContinuousAmplitudeContinuous CLK_A_1{ "CLKA_out.sgn" };
	PhotonStreamXY S2 {"S2.sgn"};
	TimeContinuousAmplitudeDiscreteReal S3{ "S3.sgn" };
	Messages C_C_1{ "C_C_1.sgn" };
	Messages C_C_6{ "C_C_1.sgn" };
	PhotonStreamXY Q_C_1{"Q_C_1.sgn"};

	// Bob Implementation
	Binary NUM_B{ "NUM_B.sgn" };
	Binary MI_B{ "MI_B.sgn" };
	TimeContinuousAmplitudeContinuous CLK_B{"CLK_B.sgn"};
	TimeContinuousAmplitudeContinuous CLK_B_out1{ "CLKB_out1.sgn" };
	TimeContinuousAmplitudeContinuous CLK_B_out2{ "CLKB_out2.sgn" };
	TimeContinuousAmplitudeContinuousReal S4{ "S4.sgn" };
	PhotonStreamXY S5{ "S5.sgn" };
	PhotonStreamXY S6{ "S6.sgn" };
	PhotonStreamXY S8{ "S8.sgn" };
	TimeContinuousAmplitudeContinuous S7{ "S7.sgn" };
	TimeContinuousAmplitudeContinuous S9{ "S9.sgn" };
	PhotonStreamXY Q_C_4{"Q_C_4.sgn"};
	Messages C_C_4{ "C_C_4.sgn" };
	Messages C_C_3{ "C_C_3.sgn" };

	
	
	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ##################################
	// #####################################################################################################

	// Alice implementation
	BinarySource B0{ vector <Signal*> {}, vector <Signal*> {&NUM_A, &Bin_1, &Bin_2} };
	B0.setBitPeriod(1/(2 * RateOfPhotons));
	B0.setMode( PseudoRandom );

	Clock B1{ vector<Signal*>{}, vector<Signal*>{&CLK_A} };
	B1.setClockPeriod(1 / RateOfPhotons);
	B1.setSamplingPeriod((1 / RateOfPhotons) / 16);
	B1.setClockPhase(3*PI/2);
	

	AliceQKD B2{ vector <Signal*> { &CLK_A, &NUM_A, &Bin_1, &Bin_2}, vector <Signal*> {&CLK_A_1, &S3, &Bin_1out, &MI_A} };
	B2.setIqAmplitudes(iqAmplitudeValues);
	B2.setNumberOfSamplesPerSymbol(16);
	B2.setPulseShaperFilter(Square);

	
	
	SinglePhotonSource B3{ vector <Signal*> {&CLK_A_1}, vector <Signal*> {&S2} };
	
	Polarizer B4{ vector<Signal*>{&S3,&S2}, vector <Signal*> {&Q_C_1} };
/*
	Sink BB1{ vector <Signal*> {&S3}, vector <Signal*> {} };
	BB1.setNumberOfSamples(1000);
	*/
	Sink BB2{ vector <Signal*> {&Bin_1out}, vector <Signal*> {} };
	BB2.setNumberOfSamples(1000);
	BB2.setDisplayNumberOfSamples(true);

	Sink BB4{ vector <Signal*> {&MI_A}, vector <Signal*> {} };
	BB4.setNumberOfSamples(1000);


	Sink BB3{ vector <Signal*> {&Q_C_1}, vector <Signal*> {} };
	BB3.setNumberOfSamples(1000);

	// ################################################################################


	//Bob Implementation
	/*BinarySource B9{ vector <Signal*> {}, vector <Signal*> {&NUM_B} };
	B9.setMode(PseudoRandom);

	Clock B10{ vector <Signal*> {}, vector <Signal*> {&CLK_B} };

	RotatorLinearPolarizer B11{ vector <Signal*> {&Q_C_4, &SB_3}, vector <Signal*> {&SB_5} };

	PolarizationBeamSplitter B12{ vector <Signal*> {&SB_5}, vector <Signal*> {&SB_4, &SB_6} };

	SinglePhotonDetector B13{ vector <Signal*> {&SB_4}, vector <Signal*> {&SB_1} };

	SinglePhotonDetector B14{ vector <Signal*> {&SB_6}, vector <Signal*> {&SB_2} };

	BobQKD B15{ vector <Signal*> {&NUM_B, &CLK_B, &C_C_3, &SB_1, &SB_2}, vector <Signal*> {&MI_B, &SB_3, &C_C_4} };

	Sink B16{ vector <Signal*> {&C_C_4}, vector <Signal*> {} };

	Sink B17{ vector <Signal*> {&MI_B}, vector <Signal*> {} };*/

	

	// ####################################################################################################
	// ########################### System Declaration and Inicialization ##################################
	// #####################################################################################################

	System MainSystem{ vector <Block*> {&B0, &B1, &B2, &B3, &B4, &BB3, &BB4} };
	// ####################################################################################################
	// ########################### Run ##################################
	// #####################################################################################################

	MainSystem.run();


    return 0;
}

