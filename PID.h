#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <chrono>

class PID
{

    public:
        // Input parameters is:, kp, ki, kd.
        PID( double, double, double, int print_frequency = std::numeric_limits<int>::max());

        void setOutputLimits(double, double); // Send in range for clamping
      //  void setSampleTime(double t) { dt = t; }; // Unit is milliseconds 
        double calculate(double);

        double getKp()const { return kp; };
        double getKi()const { return ki; };
        double getKd()const { return kd; };
        void setKp(double p) { kp = p; };
        void setKi(double i) { ki = i; };
        void setKd(double d) { kd = d; };
        void set_old_error(double e) { old_error = e; };
        
    private:
       
        double kp;
        double ki;
        double kd;
       
		int print_frequency;
		int print_counter;

        double old_error; 
        double outMin;
        double outMax;          // Output ranges
        double ITerm;
	    double dt; // Loop interval time 
};

#endif 
