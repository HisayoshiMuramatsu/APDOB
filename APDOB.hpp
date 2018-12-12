/*
	Implementation of APDOB - Adaptive Periodic-Disturbance Observer.
	@author: Hisayoshi Muramatsu
	@date: 2018.12.13
*/

#ifndef DEF_APDOB
#define DEF_APDOB

class APDOB{
public:
	APDOB(
		// Sampling time [s]
	    double IN_Tk,
	    // Cutoff frequency for the Q-filter [rad/s]
	    double IN_gp,
	    // Design parameter for the Q-filter
	    double IN_gam,
	    // Cutoff frequency for the low-pass filter [rad/s]
	    double IN_ga,
	    // Design frequency for the band-pass filter [rad/s]
	    double IN_gb,
	    // Notch parameter
	    double IN_r,
	    // Multi-rate ratio
	    double IN_kappa,
	    // Forgetting factor
	    double IN_lambda,
	    // Regularization parameter
	    double IN_delata,
	    // Maximum delay time [s]
	    double IN_MaxDelayTime,
	    // Initial fundamental frequency [rad/s]
	    double IN_HatOmega0
	);
	// Adaptive notch filter (ANF) for fundamental Frequency Estimation
	double ANF(double E);
	// Q-filter for periodic disturbance estimation
	double Qfilter(double E, double HatOmega);

private:
	/*
	* Design parameters
	*/
	// Sampling time [s]
	const double Tk;
	// Cutoff frequency for the Q-filter [rad/s]
	const double gp;
	// Design parameter for the Q-filter
	const double gam;
	// Cutoff frequency for the low-pass filter [rad/s]
	const double ga;
	// Design frequency for the band-pass filter [rad/s]
	const double gb;
	// Notch parameter
	const double r;
	// Multi-rate ratio
	const double kappa;
	// Forgetting factor
	const double lambda;
	// Regularization parameter
	const double delata;
	// Maximum delay time [s]
	const double MaxDelayTime;

	/*
	* Variables
	*/
	// Variables for computation
	double TildeDZ1, TildeDZ2, HatEtaZ1, HatEtaZ2, BPF1_InZ1, BPF1_InZ2, BPF1_OutZ1, BPF1_OutZ2,
	BPF2_InZ1, BPF2_InZ2, BPF2_OutZ1, BPF2_OutZ2, LPFqa_InZ1, LPFqa_OutZ1, LPFQ_InZ1, LPFQ_OutZ1;
	// Variables for the ANF algorithm
	double g, e, xi, P, HatOmega;
	int count;
	// Variables for the delay
	int DelayCount, DelayNum, DelayCountReset;
	std::vector<double> DelayMemory;

	/*
	* Functions
	*/
	// Band-pass filter for extracting a fundamental wave
	double FourthOrderBPF(double E, double HatOmega);
	// Low-pass filter for suppressing oscillation of the estimated frequency
	double FirstOrderLPFqa(double TildeOmega);
	// Low-pass filter for the Q-filter
	double FirstOrderLPFQ(double E);
	//Delay
	double Delay(double HatD, int N);

};

#endif

