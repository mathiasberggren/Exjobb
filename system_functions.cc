#ifndef SYSTEM_FUNCTIONS
#define SYSTEM_FUNCTIONS

/* Set values for environment */
#define ANGLE_MAX 3200
#define ANGLE_MIN 1800
#define LIN_MAX 0.9
#define LIN_MIN 0.2

#define ANGLE_SETPOINT 2550
#define LIN_SETPOINT 0.55
/* Set values for environment */

/* Raspberry I/O Pins */
#define MOTOR_PWM 1
#define MOTOR_OUT1 15
#define MOTOR_OUT2 16
#define DIST_ECHO 26
#define DIST_TRIG 27
/* Raspberry I/O Pins */

#include <wiringPi.h>
#include "include/PID.h"
#include "include/timer.h"
#include "include/distance_sensor.h"
#include "include/ADS1115.h"


bool angle_limit(int const& a)
{
	return (a > ANGLE_MIN && a < ANGLE_MAX);
}

bool linear_limit(double const& l)
{
	return (l > LIN_MIN && l < LIN_MAX);
}

#endif
