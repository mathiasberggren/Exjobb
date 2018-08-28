#include <iostream>
#include <vector>

#include "include/PID.h"

#define ANGLE_MAX 800
#define ANGLE_MIN 300
#define LIN_MAX 0.9
#define LIN_MIN 0.2

#define ANGLE_SETPOINT 505
#define LIN_SETPOINT 0.55

void retrieve_values(int &, double &);
int get_angle();
double get_dist();
bool angle_limit(int const&);
bool linear_limit(double const&);

int main()
{
	/* INIT */
    /* dt, P, I, D, Min, Max */
	PID rot { 0.1, 0.1, 0.01, 0.05, 0, 100};
	PID lin { 0.1, 0.1, 0.01, 0.05, 0, 100};
		
	//std::vector<double> angle_decoder {};
	//std::vector<double> dist_decoder  {};
	int	current_rot {};
	double 	current_pos {};
	/* INIT*/ 

	/* MAIN LOOP */
	retrieve_values(current_rot, current_pos);
	
	//current_pos = angle_decoder.at(0);
	//current_rot = dist_decoder.at(0);

	if(angle_limit(current_rot) && linear_limit(current_pos))
	{
		/* Probably not needed
		double linear_velocity 	{ current_pos / dt };
		double rot_velocity		{ current_rot / dt };
		*/

		double res {lin.calculate(LIN_SETPOINT   - current_pos)};
		double output {rot.calculate(res - current_rot)};
	}
	else
		throw std::domain_error("Reached the end of the world!");
	/* MAIN LOOP */
	
		
	double val {20};
    for(int i {}; i < 100; i++) 
    {
        double inc = rot.calculate(100 - val); 
        std::cout << "Value: " << val << " Inc: " << inc <<  
            " to goal: " << 100 - val << std::endl;
        val += inc;
       
    }
    return 0;
}

void retrieve_values(int & angle ,double & dist)
{
	angle = get_angle();
	dist  = get_dist();
}

bool angle_limit(int const& a)
{
	return (a >= ANGLE_MIN && a <= ANGLE_MAX);
}

bool linear_limit(double const& l)
{
	return (l >= LIN_MIN && l <= LIN_MAX);
}

int get_angle()
{
	return 1;
}

double get_dist()
{
	return 1.2;
}
/*
double dist_pid(double target_lin)
{  
    double error_linear=lin - target_lin;  
    double pTerm_linear=Kp_lin *  error_lin;  
    iTerm_lin += Ki_lin * error_lin;  

    double dTerm_lin = Kd_lin * (lin - lastlin);  
    lastlin = lin;  
    targetAngle = pTerm_lin + iTerm_lin + dTerm_lin; 
} 

void rotation(double targetAngle)
{  
    double error = targetAngle - rot;  
    double pTerm = Kp * error;  
    iTerm += Ki * error;  
    double dTerm = Kd * (lastrot - rot);   
    lastrot = rot;  
    out= pTerm + iTerm + dTerm; 

} 
*/
