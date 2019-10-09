/* PID Control system for Bachelor thesis
 *
 * To compile just use make.
 * (Assumes wiringPi has been installed)
 *
 * Written by: mathiasberggren1@gmail.com
 */

#ifndef PIDCONTROLLER_CC
#define PIDCONTROLLER_CC


#include <stdio.h>
#include <iostream>
//#include <vector>
#include "system_functions.cc"

#include <softPwm.h>
//#include <wiringSerial.h>
/* Arduino serial transfers */
//#define DEVICE "/dev/ttyACM0"
//#define BAUDRATE 115200

int run_PID()
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
	Timer total_runtime {};
    double sampling_time {0.0001};
	/* INIT*/

	/* MAIN LOOP */
	while(1)
	{
        while(t1.elapsed() < sampling_time) {continue;}
		t1.reset();
        current_rot = adc.getMilliVolts();
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

	return total_runtime.elapsed();
}

#endif
