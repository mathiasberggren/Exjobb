#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <chrono>

class PID
{

    public:
        // Input parameters is:, kp, ki, kd.
        PID( double, double, double, double max = 100, double min = -100);

        void setOutputLimits(double, double); // Send in range for clamping
      //  void setSampleTime(double t) { dt = t; }; // Unit is milliseconds 
        double calculate(double, double);

        double getKp()const { return kp; };
        double getKi()const { return ki; };
        double getKd()const { return kd; };
        void setKp(double p) { kp = p; };
        void setKi(double i) { ki = i; };
        void setKd(double d) { kd = d; };
        
    private:
       
//        double dt; // Loop interval time 
        double kp;
        double ki;
        double kd;
       
        double old_error; 
        double ITerm;
        double outMin;
        double outMax;          // Output ranges
};

#endif 
