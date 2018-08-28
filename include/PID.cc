#include "PID.h"
#include <iostream>
#include <stdexcept>

using namespace std;

PID::PID(double dt, double kp, double ki, double kd, double min, double max) 
    : dt{dt}, kp{kp}, ki{ki}, kd{kd}, old_error{0}, ITerm {0}, outMin{min}, outMax {max}   
{}

void PID::setOutputLimits(double min, double max)
{
    if (min >= max || min < 0)
        throw invalid_argument("Invalid output limits");
    
    outMin = min;
    outMax = max;        
}

double PID::calculate(double error)
{
    // P Term
    //double Pout = kp * error;
    //cout << "The p term is: " << Pout << endl;  
    // I Term
    ITerm += error * dt;
    //double Iout = ki * ITerm;
    //cout << "The i term is: " << Iout << endl;  
       
      
    // D Term
    //double derivative {(error - old_error) / dt};
    //double Dout = kd * derivative;
    //cout << "The d term is: " << Dout << endl;  
       
	//Possible change on derivative (error - olderror) / dt 
	//Could do derivative on measurement instead to avoid spikes
    double output = kp * error + ki * ITerm + kd * ((error - old_error) / dt);
        
    if (output > outMax) 
        output = outMax; 
    else if (output < outMin)  
        output = outMin;
        
    old_error = error;

    return output;
} 
