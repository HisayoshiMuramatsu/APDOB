/**
	Test for the APDOB - Adaptive Periodic-Disturbance Observer.
	@author: Hisayoshi Muramatsu
	@date: 2018.12.13
*/

#include <iostream>

#include "APDOB.cpp"

// Plant example: a motor system
double Motor(double u, double d, double M, double Kt, double Ts);
// Inverse model of the motor system used by the APDOB
double InverseModel(double u, double y, double Mn, double Ktn, double gpd, double Tk);
// Proportional and derivative controller
double PDctr(double xcmd, double y, double Kp, double Kv, double gpd, double Tk);
// Acceleration feedfoward controller
double ACCff(double xcmd, double gpd, double Tk);

int main(){
	// Simulation time [s]
	const double tEND = 30;

	/*
	* Motor parameters
	*/
	 // Cutoff frequency for the pseudo derivatives [rad/s]
	const double gpd = 500;
	// Thrust constant [N/A]
	const double Kt = 0.24;
	// Nominal thrust constant [N/A]
	const double Ktn = 0.24;
	// Mass [kg]
	const double M = 0.3;
	// Nominal mass [kg]
	const double Mn = 0.3;

	/*
	* PD control parameters
	*/
	// Proportional gain
	const double Kp = 2500;
	// Derivative gain
	const double Kv = 100;

	/*
	* APDOB parameters
	*/
	// Sampling time [s]
	const double Tk = 0.0001;
	// Cutoff frequency for the Q-filter [rad/s]
	const double gp = 1000;
	// Design parameter for the Q-filter
	const double gam = 0.5;
	// Design frequency for the frequency estimation [rad/s]
	const double ga = 10;
	// Design frequency for the band-pass filter [rad/s]
	const double gb = 20;
	// Notch parameter
	const double r = 0.7;
	// Multi-rate ratio
	const double kappa = 10;
	// Forgetting factor
	const double lambda = 0.999;
	// Regularization parameter
	const double delata = 1000;
	// Maximum delay time [s]
	const double MaxDelayTime = 10;
	// Initial fundamental frequency [rad/s]
	const double HatOmega0 = 100;

	/*
	* Variables
	*/
	 // Time, input, output, periodic disturbance, command, acceleration reference, and fundamental freq.
	double t(0.0), u(0.0), y(0.0), Dp(0.0), xcmd(0.0), ddxref(0.0), Omega(0.0);
	// Error, estimated fundamental frequency, and estimated periodic disturbance
	double E(0.0), HatOmega(0.0), HatDp(0.0);

	// Construct the APDOB
	APDOB ap(Tk, gp, gam, ga, gb, r, kappa, lambda, delata, MaxDelayTime, HatOmega0);

	std::cout << "================" << std::endl;
	std::cout << "APDOB SIMULATION" << std::endl;

	/**
	* Real-time control simulation
	*/
	do{
		/**
		* Control computation
		*/
		// ---------- APDOB ----------
		// Error computation: Difference between reference force and actual force due to disturbances
		E = InverseModel(u, y, Mn, Ktn, gpd, Tk);
		// ANF: Fundamental frequency estimation
		HatOmega = ap.ANF(E);
		// Q-filter: Periodic-disturbance estimation
		HatDp = ap.Qfilter(E, HatOmega);
		// ---------- APDOB ----------

		// Position command
		xcmd = 0.001*sin(2*3.1416*t);
		// Proportional and derivative control with acceleration feedforward
		ddxref = PDctr(xcmd, y, Kp, Kv, gpd, Tk) + ACCff(xcmd, gpd, Tk);
		// Input current using the periodic-disturbance compensation
		u = (1/Ktn) * (Mn*ddxref + HatDp);

		for(int i(0); i<100; i++){
			/**
			* Plant simulation
			* Fast sampling for simulating continuous plant
			*/
			if(t<10){ // Fundamental frequency for the periodic disturbance
				Omega = 100;
			}else{
				Omega = 110;
			}
			Dp = 0.0;
			for(int i(1); i<11; i++){
				Dp += sin(i*Omega*t); // Periodic disturbance
			}
			y  = Motor(u, Dp, M, Kt, 0.01*Tk); // Motor system (Input: current, output: position)
			t += 0.01*Tk;
		}

		if((int)(t/Tk)%(int)(1/Tk) == 0) {
			std::cout << "---------------- " << (int) t << " s" << " ----------------" << std::endl;
			std::cout << "Fundamental Frequency: " << Omega << " rad/s" << std::endl;
			std::cout << "Estimated Frequency  : " << HatOmega << " rad/s" << std::endl;
			std::cout << "Control Error        : " << 1000000*(xcmd - y) << " micron" << std::endl;
		}

	}while(t<=tEND);

	return 0;
}

double Motor(double u, double d, double M, double Kt, double Ts) {
	double x(0.0), dx(0.0), ddx(0.0), F(0.0);
	static double xZ1 (0.0), dxZ1 (0.0), ddxZ1(0.0);
	F     = Kt*u - d;
	ddx   = F/M; // Acceleration
	x     = xZ1 + Ts*0.5*(dx + dxZ1); // Position
	dx    = dxZ1 + Ts*0.5*(ddx + ddxZ1); // Velocity
	xZ1   = x;
	dxZ1  = dx;
	ddxZ1 = ddx;
	return x;
}

double InverseModel(double u, double y, double Mn, double Ktn, double gpd, double Tk) {
	double Fref(0.0), Fact(0.0), E(0.0), dy(0.0), ddy(0.0);
	double a(0.0), b(0.0), c(0.0), d(0.0);
	double In1(0.0), Out1(0.0), In2(0.0), Out2(0.0);
	static double In1Z1(0.0), Out1Z1(0.0), In2Z1(0.0), Out2Z1(0.0);
	/**
	* Left side plant model
	*/
	Fref = Ktn*u; // Force output = Thrust constant * Current input
	/**
	* Right side inverse plant model
	*/
	// Coefficients for the pseudo derivative
	a = 2 + gpd*Tk;
	b = 2 - gpd*Tk;
	c = 2*gpd;
	d = - 2*gpd;
	// Pseudo derivative 1
	In1    = y; // Position input
	Out1   = (b/a)*Out1Z1 + (c/a)*In1 + (d/a)*In1Z1;
	In1Z1  = In1;
	Out1Z1 = Out1;
	dy     = Out1; // Velocity output
	// Pseudo derivative 2
	In2    = dy; // Velocity input
	Out2   = (b/a)*Out2Z1 + (c/a)*In2 + (d/a)*In2Z1;
	In2Z1  = In2;
	Out2Z1 = Out2;
	ddy    = Out2; // Acceleration output
	// Actual force = mass * acceleration
	Fact = Mn*ddy;
	/**
	* Disturbance error calculation
	*/
	E = Fref - Fact;
	// Disturbance error
	return E;
}

double PDctr(double xcmd, double y, double Kp, double Kv, double gpd, double Tk) {
	double e(0.0), de(0.0);
	double a(0.0), b(0.0), c(0.0), d(0.0);
	double In1(0.0), Out1(0.0);
	static double In1Z1(0.0), Out1Z1(0.0);
	// Error
	e = xcmd - y;
	// Coefficients for the pseudo derivatives
	a = 2 + gpd*Tk;
	b = 2 - gpd*Tk;
	c = 2*gpd;
	d = - 2*gpd;
	// Pseudo derivative 1
	In1    = e; // Error input
	Out1   = (b/a)*Out1Z1 + (c/a)*In1 + (d/a)*In1Z1;
	In1Z1  = In1;
	Out1Z1 = Out1;
	de     = Out1; // Differential error
	// Output of the PD controller
	return Kp*e + Kv*de;
}

double ACCff(double xcmd, double gpd, double Tk) {
	double dxcmd(0.0), ddxcmd(0.0);
	double a(0.0), b(0.0), c(0.0), d(0.0);
	double In1(0.0), Out1(0.0), In2(0.0), Out2(0.0);
	static double In1Z1(0.0), Out1Z1(0.0), In2Z1(0.0), Out2Z1(0.0);
	// Coefficients for the pseudo derivatives
	a = 2 + gpd*Tk;
	b = 2 - gpd*Tk;
	c = 2*gpd;
	d = - 2*gpd;
	// Pseudo derivative 1
	In1    = xcmd; // Position command input
	Out1   = (b/a)*Out1Z1 + (c/a)*In1 + (d/a)*In1Z1;
	In1Z1  = In1;
	Out1Z1 = Out1;
	dxcmd  = Out1; // Velocity output
	// Pseudo derivative 2
	In2    = dxcmd; // Velocity input
	Out2   = (b/a)*Out2Z1 + (c/a)*In2 + (d/a)*In2Z1;
	In2Z1  = In2;
	Out2Z1 = Out2;
	ddxcmd = Out2; // Acceleration command output
	// Acceleration command
	return ddxcmd;
}
