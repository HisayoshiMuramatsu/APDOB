/*
	Implementation of APDOB - Adaptive Periodic-Disturbance Observer.
	@author: Hisayoshi Muramatku
	@date: 2019.01.08
*/

#include <vector>
#include <math.h>

#include "APDOB.hpp"

APDOB::APDOB(
		double IN_Tk,
		double IN_gp,
		double IN_gam,
		double IN_ga,
		double IN_gb,
		double IN_r,
		double IN_kappa,
		double IN_lambda,
		double IN_delata,
		double IN_MaxDelayTime,
		double IN_HatOmega0
	):Tk(IN_Tk), gp(IN_gp), gam(IN_gam), ga(IN_ga), gb(IN_gb),
	r(IN_r), kappa(IN_kappa), lambda(IN_lambda), delata(IN_delata),
	MaxDelayTime(IN_MaxDelayTime)
{
	g = 0.0; e = 0.0; count = 0;
	xi = -2*cos(IN_HatOmega0*Tk); P = 1/delata; HatOmega = IN_HatOmega0;

	TildeDZ1 = 0.0; TildeDZ2 = 0.0; HatEtaZ1 = 0.0; HatEtaZ2 = 0.0;
	BPF1_InZ1 = 0.0; BPF1_InZ2 = 0.0; BPF1_OutZ1 = 0.0; BPF1_OutZ2 = 0.0;
	BPF2_InZ1 = 0.0; BPF2_InZ2 = 0.0; BPF2_OutZ1 = 0.0; BPF2_OutZ2 = 0.0;
	LPFqa_InZ1 = 0.0; LPFqa_OutZ1 = IN_HatOmega0; LPFQ_InZ1 = 0.0; LPFQ_OutZ1 = 0.0;

	DelayCount = 0; DelayNum = 0; DelayCountReset = (int)(MaxDelayTime/Tk);
	std::vector<double> IN_DelayMemory((int)((MaxDelayTime+0.1)/Tk));
	DelayMemory = IN_DelayMemory;
}

double APDOB::ANF(double E){
	double alpha(0.0), beta(0.0), TildeD(0.0), HatEta(0.0), TildeOmega(0.0);
	// Extraction of a fundamental wave
	TildeD = APDOB::FourthOrderBPF(E, HatOmega);
	// Notch filter
	alpha    = -r*HatEtaZ1 + TildeDZ1;
	beta     = -r*r*HatEtaZ2 + TildeD + TildeDZ2;
	HatEta   = alpha*xi + beta;
	TildeDZ2 = TildeDZ1;
	TildeDZ1 = TildeD;
	HatEtaZ2 = HatEtaZ1;
	HatEtaZ1 = HatEta;
	// Adaptive algorithm (Sampling time: Th = kappa * Tk)
	if(count>(kappa-1)) {
		g     = (P*alpha)/(lambda+P*alpha*alpha);
		e     = 0.0 - HatEta;
		xi    = xi + g*e;
		P     = (1/lambda)*(P-g*alpha*P);
		count = 0;
	}
	count++;
	// Frequency computation
	if(xi<-2) { // Under limit for acos()
		TildeOmega = (1/Tk)*acos(-0.5*-2);
	} else if(2<xi) { // Upper limit for acos()
		TildeOmega = (1/Tk)*acos(-0.5*2);
	} else {
		TildeOmega = (1/Tk)*acos(-0.5*xi);
	}
	// Oscillation attenuation
	HatOmega = APDOB::FirstOrderLPFqa(TildeOmega);
	// Estimated fundamental frequency
	return HatOmega;
}

double APDOB::Qfilter(double E, double HatOmega) {
	double HatD(0.0), HatDp(0.0);
	int N = 0;
	// LPF for disturbance estimation
	HatD = APDOB::FirstOrderLPFQ(E);
	// Discrete delay
	N = (int)((2*M_PI*gp*gam-HatOmega)/(Tk*gp*HatOmega*gam));
	// Periodic-disturbance estimation
	HatDp = HatD - gam*(HatD - Delay(HatD, N));
	// Estimated periodic disturbance
	return HatDp;
}

double APDOB::FourthOrderBPF(double E, double HatOmega) {
	double BPF1_In(0.0), BPF1_Out(0.0);
	double BPF2_In(0.0), BPF2_Out(0.0);
	double a(0.0), b(0.0), c(0.0), d(0.0), e(0.0);
	// BPF Coefficients
	a = 4 + 2*gb*Tk + HatOmega*HatOmega*Tk*Tk;
	b = 8 - 2*HatOmega*HatOmega*Tk*Tk;
	c = -4 + 2*gb*Tk - HatOmega*HatOmega*Tk*Tk;
	d = 2*gb*Tk;
	e = - 2*gb*Tk;
	// Disturbance error
	BPF1_In = E;
	/**
	* SecondOrderBPF1
	*/
	// BPF computation
	BPF1_Out = (b/a)*BPF1_OutZ1 + (c/a)*BPF1_OutZ2 + (d/a)*BPF1_In + (e/a)*BPF1_InZ2;
	BPF1_InZ2  = BPF1_InZ1;
	BPF1_InZ1  = BPF1_In;
	BPF1_OutZ2 = BPF1_OutZ1;
	BPF1_OutZ1 = BPF1_Out;
	/**
	* SecondOrderBPF2
	*/
	BPF2_In = BPF1_Out;
	// BPF computation
	BPF2_Out = (b/a)*BPF2_OutZ1 + (c/a)*BPF2_OutZ2 + (d/a)*BPF2_In + (e/a)*BPF2_InZ2;
	BPF2_InZ2  = BPF2_InZ1;
	BPF2_InZ1  = BPF2_In;
	BPF2_OutZ2 = BPF2_OutZ1;
	BPF2_OutZ1 = BPF2_Out;
	// Fundamental wave of the disturbance error
	return BPF2_Out;
}

double APDOB::FirstOrderLPFqa(double TildeOmega) {
	double LPFqa_In(0.0), LPFqa_Out(0.0);
	double a(0.0), b(0.0), c(0.0), d(0.0);
	// LPF Coefficients
	a = 2 + ga*Tk;
	b = 2 - ga*Tk;
	c = ga*Tk;
	d = ga*Tk;
	// Fundamental frequency from the ANF
	LPFqa_In = TildeOmega;
	// LPF computation
	LPFqa_Out = (b/a)*LPFqa_OutZ1 + (c/a)*LPFqa_In + (d/a)*LPFqa_InZ1;
	LPFqa_InZ1  = LPFqa_In;
	LPFqa_OutZ1 = LPFqa_Out;
	// Estimated fundamental frequency
	return LPFqa_Out;
}

double APDOB::FirstOrderLPFQ(double E) {
	double LPFQ_In(0.0), LPFQ_Out(0.0);
	double a(0.0), b(0.0), c(0.0), d(0.0);
	// LPF Coefficients
	a = 2 + gp*Tk;
	b = 2 - gp*Tk;
	c = gp*Tk;
	d = gp*Tk;
	// Disturbance error
	LPFQ_In = E;
	// LPF computation
	LPFQ_Out = (b/a)*LPFQ_OutZ1 + (c/a)*LPFQ_In + (d/a)*LPFQ_InZ1;
	LPFQ_InZ1  = LPFQ_In;
	LPFQ_OutZ1 = LPFQ_Out;
	// Estimated disturbance
	return LPFQ_Out;
}

double APDOB::Delay(double HatD, int N) {
	// Storage of estimated disturbance
	DelayMemory[DelayCount] = HatD;
	// Delayed count computation
	DelayNum = DelayCount - N;
	if(DelayNum<0) DelayNum = DelayNum + DelayCountReset + 1;
	DelayCount++;
	if(DelayCount > DelayCountReset) DelayCount = 0;
	// Delayed estimated disturbance
	return DelayMemory[DelayNum];
}















