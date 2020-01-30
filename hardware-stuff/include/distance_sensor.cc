#include <wiringPi.h>
#include "timer.h"
#include "distance_sensor.h"
/* For testing purposes

#include "timer.h"
#include <iostream>
#include <iomanip>

int main()
{
	Timer t{};
	trigger_sensor();
	std::cout << "Tiden som har passerat är: " << std::fixed << t.elapsed() << std::endl;	

	return 0;
}

void trigger_sensor(int const& trig_pin)
{	
	digitalWrite(trig_pin, 0)
	digitalWrite(trig_pin, 1)
	delay(1); //Could decrease if necessary
	digitalWrite(trig_pin, 0)
}
*/

double Distance_sensor::get_distance()const
{
	digitalWrite(trig_pin, 0);
	digitalWrite(trig_pin, 1);
	delay(1); //Maybe decrease?
	digitalWrite(trig_pin, 0);
	while(digitalRead(echo_pin) == 0);
	Timer t1 {};
	while(digitalRead(echo_pin) == 1);
	return 340 * t1.elapsed() / 2;
}

