/* PID Control system for Bachelor thesis
 *
 * To compile just use make.
 * (Assumes wiringPi has been installed)
 *
 * Written by: mathiasberggren1@gmail.com
 */
#include <cmath>
#include <random>
#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
//#include <vector>
#include <wiringPi.h>
//#include <wiringSerial.h>
//#include <softPwm.h>
#include "include/timer.h"
#include "include/distance_sensor.h"
#include "include/ADS1115.h"
/* Arduino serial transfers */
//#define DEVICE "/dev/ttyACM0"
//#define BAUDRATE 115200
/* Arduino serial transer */

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

int get_angle(int const&);
bool angle_limit(int const&);
bool linear_limit(double const&);
void motor_throughput(double const&);

void read_from_file(std::ifstream &, std::unordered_map<std::string, double> &,
					 std::unordered_map<std::string, int> & );
void write_to_file(std::ofstream &, std::unordered_map<std::string, double> const&,
					std::unordered_map<std::string,int> const&);
std::string get_state(int, double, double, double);
double get_reward(std::string const&);
int run_qlearning(std::string file = "")
{
	/* HARDWARE INITIATION */
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

    Distance_sensor dist {}; //Default parameters pin 26, pin 27 */
    ADS1115 adc {};
    adc.setMode(ADS1115_MODE_SINGLESHOT);
    adc.setRate(ADS1115_RATE_860);
    /* HARDWARE INITIATION */

	/* Q-Learning INITIATION */
	std::unordered_map<std::string, double> Qtable {}; // Contains all Q-values
	std::unordered_map<std::string, int>    NTable {}; // Statistics of how many times each combination of state/action has been done

	const double GAMMA_FACTOR	{0.95}; // Always < 1, small values = greedy
    const double LEARNING_RATE	{10};   // Lower values = Quick results but less reliable
	double explore_chance		{0.5};  // During training phase

	int iterations {0};
	int print_counter  {0};

	bool paused {true};
	bool train  {true};
	bool using_file {false};
	/* Q-Learning INITIATION */

    int		angle	{};
	int oldangle	{get_angle(adc.getMillivolts()};
	double vangle	{};
	double x		{};
	double oldx		{dist.get_distance()};
	double vx		{};
	Timer t1		{};
	Timer total		{};
	//	double sampling_time {0.0001};

	double previous_reward		{};
	int previous_action			{};
	std::string previous_state  {};
	/* INIT*/

	// Read saved values from file:
	if(!file_name.empty())
	{
		using_file = true;
		std::ifstream file;
		file.open(file_name);
		if(!file.is_open())
		{
			std::ofstream create_file {file_name};
			create_file << "Tables with Q and N values from file: " << endl;
			create_file.close();
		}
		else
			read_from_file(file, Qtable, Ntable);
	}



	/* MAIN LOOP */
	while(1)
	{
		iterations++;
		//while(t1.elapsed() < sampling_time) {continue;}
    angle	= get_angle(adc.getMilliVolts());
		x			= dist.get_distance();

		auto interval_time = t1.elapsed();
		t1.reset();

		vangle   = static_cast<double>(oldangle - angle) / interval_time;
		vx		   = (oldx - x) / interval_time;
		oldangle = angle;
		oldx	   = x;

		if(angle_limit(current_rot))//&& linear_limit(current_pos))
		{
			action_counter++;
			std::string new_state  {get_state(angle, vangle, x, vx)};
			double reward {get_reward(new_state)};
			if(!previous_state.empty())
			{
				std::string prev_stateaction {previous_state + std::to_string(previous_action)};

				//Double check if working
				//if(Ntable.find(prev_stateaction) == Ntable.end())
				//	NTable[prev_stateaction] = 0;
				int num_tested {++Ntable[prev_stateaction]};
				//Double check if working

				//if(Qtable.find(prev_stateaction) == Qtable.end())
				//old_qval = Qtable[prev_stateaction];

				double qval = Qtable[prev_stateaction] + (LEARNING_RATE / (LEARNING_RATE / num_tested) *
							(previous_reward+GAMMA_FACTOR*getMaxActionQValue(new_state) -
							Qtable[prev_stateaction]));

				Qtable[prev_stateaction] = qval;

				perform_action(select_action(new_state));

				print_counter++;
				if(print_counter % 10 == 0)
				{
					cout << "Iteration: " << iterations << " Angle: " << angle << " vAngle : "
						<< vangle << " X: " << x << " vx: " << vx << " Prev State: " << previous_state
						<< " Prev Reward: " << previous_reward << " Prev Q-value: " << qval
						<< " Tested: " << num_tested << " times." << endl;
				}
			}
			previous_reward = reward;
			previous_state = new_state;
		}
		else
		{
			//serialClose(fd_arduino);
			digitalWrite(MOTOR_OUT1, 0);
			digitalWrite(MOTOR_OUT2, 0);
			std::cout << "Reached the end of the world!" << std::endl;
			if(using_file)
				write_to_file( , Qtable, Ntable);
			break;
		}
		//std::cout << "Current sampling time: " << std::fixed << t1.elapsed() << std::endl;
	}
	/* MAIN LOOP */

	return total.elapsed();
}


void read_from_file(std::ifstream & ifs, std::unordered_map<std::string, double> & Qtable,
		std::unordered_map<std::string, int> & Ntable)
{
	std::string qstate {};
	int		nval {};
	double	qval {};

	std::string input {};
	std::getline(ifs, input); // Read away first string since it's garbage
	while(getline(ifs, input))
			{
				std::stringstream ss {input};
				ss >> qstate >> qval >> nval;
				Qtable[qstate] = qval;
				Ntable[qstate] = nval;
			}
}

void write_to_file(std::ofstream & ofs, std::unordered_map<std::string, double> const& Qtable,
			std::unordered_map<std::string, int> const& Ntable)
{
			ofs << "State" << std::setw(22) << "Qvalue" << std::setw(15) << "Nvalue" << endl;
			auto itNtable = Ntable.begin();
			for (auto itQtable : Qtable)
			{
				ofs << itQtable.first << std::setw(13) << itQtable.second << std::setw(13) << itNtable -> second << endl;
				++itNtable;
			}
}


std::string get_state(int angle, double v_angle, double x, double vx)
{
	std::stringstream ss {};
	int anglestate {};
	if(angle > 2800)
		anglestate = 1;
	else if(angle > 2600)
		anglestate = 2;
	else if(angle < 2300)
		anglestate = 0;
	else if(angle < 2500)
		anglestate = 3;
	else if(angle < 2570)
		anglestate = 4;
	else if(angle > 2530)
		anglestate = 5;
	else
		anglestate = 6;

	int v_anglestate {};
	if (std::abs(v_angle) < 0.3)
		v_anglestate = 2;
	else if(v_angle > 0)
		v_anglestate = 1;
	else 
		v_anglestate = 0;

	int xstate {};
	if(x > 70)
		xstate = 0;
	else if(x < 30)
		xstate = 1;
	else
		xstate = 2;

	int vxstate {};
	if(std::abs(vx) < 0.3)
		vxstate = 2;
	else if(vxstate > 0)
		vxstate = 1; 
	else
		vxstate = 0;

	ss << anglestate << "/" << v_anglestate << "/" << xstate << "/" << vxstate;
	return ss.str();	
}


double get_reward(std::string const& state)
{
	double reward {};
	
	std::stringstream ss {};
	int anglestate		{};
	double v_anglestate	{};
	double xstate		{};
	double v_xstate		{};
	char trash		{};
	ss << state;
	ss >> anglestate >> trash >> v_anglestate >> trash >> xstate >> trash >> v_xstate;

	if(anglestate = 6)
		reward += 40;
	else if(anglestate == 4 || anglestate == 5)
		reward += 15;
	else if(anglestate == 3 || anglestate == 2)
		reward -= 10;
	else 
		reward -= 30;

	if(v_anglestate == 2)
		reward += 20;
	else
		reward -= 10;
	
	if(xstate == 2)
		reward += 10;

	if(v_xstate == 2)
		reward += 10;

	return reward;
}

//Get highest Qvalue in current state without considering the State
double getMaxActionQValue(std::string state)
{
	double maxQval = std::numeric_limits<double>::lowest();
	for(int i{}; i < 3; i++)
	{
		auto table_value {Qtable.find(state + std::to_string(i))};
		if(table_value != Qtable.end() && table_value -> second > maxQval)
			maxQval = table_value -> second;
	}
	if(Qval == std::numeric_limits<double>::lowest())
		maxQval = 0; //Uninitialized table value

	return maxQval;
}

int select_action(std::string state)
{
	int action {};

	std::random_device rd;				//For training
	std::uniform_real_distribution<double> distr_train  (0.0,1.0);
	std::uniform_int_distribution<int>     distr_action (0,2);

	//Train
	if (training && distr_train(rd) < explore_chance)
		action = distr_action(rd);
	else // Get highest possible Q-value in the given state
	{
		double maxQval = std::numeric_limits<double>::lowest(); // Lowest possible value
		for (int i {}; i < 3; i++)
		{
			std::string test_pair {state + std::to_string(i)}; //Test all actions
			double Qval {};
			auto table_value = Qtable.find(test_pair)
			if(table_value != Qtable.end())
				Qval = table_value -> second;
			if(Qval > maxQval)
			{
				maxQval = Qval;
				action = i;
			}
		}

	}

	return action;
}

void perform_action(int action)
{
	switch(action)
	{
		case 0:
			digitalWrite(MOTOR_OUT1, 0);
            digitalWrite(MOTOR_OUT2, 0);
			break;
		case 1:
			digitalWrite(MOTOR_OUT1, 0);
			digitalWrite(MOTOR_OUT2, 1);
			break;
		case 2:
			digitalWrite(MOTOR_OUT1, 1);
			digitalWrite(MOTOR_OUT2, 0);
			break;
	}
}

bool angle_limit(int const& a)
{
	return (a > ANGLE_MIN && a < ANGLE_MAX);
}

bool linear_limit(double const& l)
{
	return (l > LIN_MIN && l < LIN_MAX);
}
