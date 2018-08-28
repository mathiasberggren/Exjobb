/* PID Control system for Bachelor thesis
 *  
 * Link to wiringPi library when compiling by using flag -lwiringPi 
 * (This assumes that wiringPi has been installed).
 * 
 * Written by: mathiasberggren1@gmail.com
 */


#include <stdio.h>
#include <iostream>
//#include <vector>
#include <wiringPi.h>
#include <wiringSerial.h> 

#include "include/PID.h"
#include "include/timer.h"
#include "include/distance_sensor.cc"

/* Arduino serial transfers */
#define DEVICE "ttyAMA0"
#define BAUDRATE 36000
/* Arduino serial transer */

/* PID controllers */
#define ANGLE_MAX 800
#define ANGLE_MIN 300
#define LIN_MAX 0.9
#define LIN_MIN 0.2

#define ANGLE_SETPOINT 505
#define LIN_SETPOINT 0.55
/* PID controllers */

/* Raspberry I/O Pins */
#define MOTOR_PWM 1
#define MOTOR_OUT1 15
#define MOTOR_OUT2 16
#define DIST_ECHO 27
#define DIST_TRIG 26
/* Raspberry I/O Pins */

int get_angle(const&);
bool angle_limit(int const&);
bool linear_limit(double const&);
void motor_throughput(double const&);

int main()
{
	bool both_pids	{false};
	bool PWM		{false};
	/* INIT */
	wiringPiSetup();

	pinMode(MOTORPWM, PWM_OUTPUT);
	pinMode(MOTOROUT1, OUTPUT);
	pinMode(MOTOROUT2, OUTPUT);
	pinMode(DIST_ECHO, INPUT);
	pinMode(DIST_TRIG, OUTPUT);

	/* dt, P, I, D, Min, Max */
	if(both_pids)
		PID lin { 0.1, 0.1, 0.01, 0.05, 0, 100};

	PID rot { 0.1, 0.1, 0.01, 0.05, 0, 100};


	int fd_arduino {serialOpen(DEVICE, BAUDRATE)};
	int		current_rot {};
	double	current_pos {};
	double	output		{};
	Timer t1 {};
	/* INIT*/ 

	/* MAIN LOOP */
	while(1)
	{
		t1.reset();
		current_rot = get_angle(fd_arduino);
		current_pos = get_distance();	

		if(angle_limit(current_rot) && linear_limit(current_pos))
		{
			/* Probably not needed
			   double linear_velocity 	{ current_pos / dt };
			   double rot_velocity		{ current_rot / dt };
			 */
			if(both_pids)
			{
				double res {lin.calculate(LIN_SETPOINT   - current_pos)};
				output = {rot.calculate(res - current_rot)};
			}
			else
				output  = rot.calculate(ROT_SETPOINT - current_rot);
			/* Needed? 
			   MOTOR_PWM, output)
			   Needed? */
			//pwmWrite(MOTOR_PWM, output);
			if(PWM)
				pwmWrite(MOTOR_PWM, output);
			else
			{
				if(output > 0)
				{
					digitalWrite(MOTOR_OUT1, 1);
					digitalWrite(MOTOR_OUT2, 0);
				}
				else if(output < 0)
				{
					digitalWrite(MOTOR_OUT1, 0);
					digitalWrite(MOTOR_OUT2, 1);
				}

			}

		}
		else
		{
			serialClose(fd_arduino);
			throw std::domain_error("Reached the end of the world!");
		}
		std::cout << "Current sampling time: " << std::fixed << t1.elapsed() << std::endl;
	}	
	/* MAIN LOOP */

	return 0;
}

bool angle_limit(int const& a)
{
	return (a >= ANGLE_MIN && a <= ANGLE_MAX);
}

bool linear_limit(double const& l)
{
	return (l >= LIN_MIN && l <= LIN_MAX);
}

int get_angle(int const& fd)
{
	int angle{};
	while(1)
	{
		try
		{
			angle = static_cast<int>(serialGetChar(fd));
			break;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return angle;
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
