#include "PID.h"
#include <iostream>
#include <stdexcept>

using namespace std;

PID::PID(double kp, double ki, double kd, int print_frequency) 
    : kp{kp}, ki{ki}, kd{kd},  print_frequency{print_frequency}, print_counter {1}, old_error{0}, outMin{-100}, outMax{100}, ITerm {0},dt{1E-3}
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
	ITerm += error * dt;
	if(print_counter % print_frequency == 0)
	{	
		// P Term
		double Pout = kp * error;
		cout << "The p term is: " << Pout;  
		// I Term
		// ITerm += error * dt;
		double Iout = ki * ITerm;
		cout << ", the i term is: " << Iout;  
		   
		 
		// D Term
		double derivative {(error - old_error) / dt};
		double Dout = kd * derivative;
		cout << ", d term is: " << Dout << " the output is: " << Pout + Dout<< endl;  
		print_counter = 1;
    } 
	else print_counter++;
	//Possible change on derivative (error - olderror) / dt 
	//Could do derivative on measurement instead to avoid spikes
    // double Dout {kd * ((error-old_error) / dt)};
    // if(old_error == 0)
       // Dout = 1; 
    double output = kp * error + ki * ITerm - kd * ((error - old_error) / dt);
	// cout << "This is the output from the PID: " << output << " output max is: " << outMax << " and output min is: " << outMin << endl;         

    if (output > outMax) 
        output = outMax; 
    else if (output < outMin)  
        output = outMin;
        
    old_error = error;

    return output;
} 
