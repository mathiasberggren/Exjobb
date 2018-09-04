/* PID Control system for Bachelor thesis
 *  
 * To compile just use make.  
 * (Assumes wiringPi has been installed)
 *  
 * Written by: mathiasberggren1@gmail.com
 */


#include <stdio.h>
#include <iostream>
//#include <vector>
#include <wiringPi.h>
//#include <wiringSerial.h> 
#include <softPwm.h>
#include "include/PID.h"
#include "include/timer.h"
#include "include/distance_sensor.h"
#include "include/ADS1115.h"
/* Arduino serial transfers */
#define DEVICE "/dev/ttyACM0"
#define BAUDRATE 115200
/* Arduino serial transer */

/* PID controllers */
#define ANGLE_MAX 3200
#define ANGLE_MIN 1800
#define LIN_MAX 0.9
#define LIN_MIN 0.2

#define ANGLE_SETPOINT 2550 //2550
#define LIN_SETPOINT 0.55
/* PID controllers */

/* Raspberry I/O Pins */
#define MOTOR_PWM 1
#define MOTOR_OUT1 15
#define MOTOR_OUT2 16
#define DIST_ECHO 26
#define DIST_TRIG 27
/* Raspberry I/O Pins */

int get_angle(int const&);
bool angle_limit(int const&);
bool linear_limit(double const&);
void motor_throughput(double const&);

int main()
{
	bool both_pids	{false};
	bool PWM		{false};
	/* INIT */
	wiringPiSetup();
    if(PWM)
    {
        softPwmCreate(MOTOR_PWM, 0, 100);
	    //pinMode(MOTOR_PWM, PWM_OUTPUT);
    }
    else
        pinMode(MOTOR_PWM, OUTPUT);	
    pinMode(MOTOR_OUT1, OUTPUT);
	pinMode(MOTOR_OUT2, OUTPUT);

    digitalWrite(MOTOR_OUT1, 0);   
    digitalWrite(MOTOR_OUT2, 0);

    Distance_sensor dist {}; //Default parameters pin 26, pin 27, 1ms dela* P, I, D, Min, Max */
    ADS1115 adc {};
    adc.setMode(ADS1115_MODE_SINGLESHOT);
    adc.setRate(ADS1115_RATE_860);
        
	PID lin { 0.1, 0.01, 0.05, -100, 100};
	PID rot {5 , 0.0, 0.0, -100, 100};
        //2.7

	//int fd_arduino {serialOpen(DEVICE, BAUDRATE)};
	//if(fd_arduino < 0)
    //    std::cout << "Could not open serial transfer :( " << std::endl;
    int		current_rot {};
	double	current_pos {};
	double	output		{};
	Timer t1 {};
    double sampling_time {0.0001};
	/* INIT*/ 

	/* MAIN LOOP */
	while(1)
	{
        while(t1.elapsed() < sampling_time) {continue;}
		t1.reset();
        current_rot = get_angle(adc.getMilliVolts());
		current_pos = dist.get_distance();	

		if(angle_limit(current_rot))//&& linear_limit(current_pos))
		{
			/* Probably not needed
			   double linear_velocity 	{ current_pos / dt };
			   double rot_velocity		{ current_rot / dt };
			 */
			if(both_pids)
			{
				double res {lin.calculate(LIN_SETPOINT   - current_pos, sampling_time)};
				output = {rot.calculate(res - current_rot, sampling_time)};
			}
			else
				output  = rot.calculate(ANGLE_SETPOINT - current_rot, sampling_time);
		    std::cout << "Return value from PID: " << output << std::endl;
            /* Needed? 
			   MOTOR_PWM, output)
			   Needed? */
			//pwmWrite(MOTOR_PWM, output);
			if(PWM)
                softPwmWrite(MOTOR_PWM, abs(output));
				//pwmWrite(MOTOR_PWM, abs(output));
			else
                digitalWrite(MOTOR_PWM, 1);
			
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
            else
            {
                digitalWrite(MOTOR_OUT1, 0);
                digitalWrite(MOTOR_OUT2, 0);
            }
		}
		else
		{
			//serialClose(fd_arduino);
	        digitalWrite(MOTOR_OUT1, 0);   
            digitalWrite(MOTOR_OUT2, 0);
		    throw std::domain_error("Reached the end of the world!");
		}
		//std::cout << "Current sampling time: " << std::fixed << t1.elapsed() << std::endl;
	}	
	/* MAIN LOOP */

	return 0;
}

bool angle_limit(int const& a)
{
	return (a > ANGLE_MIN && a < ANGLE_MAX);
}

bool linear_limit(double const& l)
{
	return (l > LIN_MIN && l < LIN_MAX);
}

int get_angle(int const& a)
{
    return a;
    //return a / 10;
 //   return a % 100;
}
/*
int get_angle(int const& fd)
{
	int angle{};
    std::string s{};
	while(1)
	{
		try
		{
            char c {static_cast<char>(serialGetchar(fd))};
            while(c != '\r')
            {
                s += c;
                c = static_cast<char>(serialGetchar(fd));
            }
   			angle = std::stoi(s);
            break;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return angle;
}*/


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
