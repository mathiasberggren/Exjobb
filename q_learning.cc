/* Q-learning system for Bachelor thesis
 *
 * To compile just use make.
 * (Assumes wiringPi has been installed)
 *
 * Written by: mathiasberggren1@gmail.com
 */


#ifndef QLEARNING
#define QLEARNING

#include <cmath>
#include <random>
#include <unordered_map>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "system_functions.cc"



void read_from_file(std::ifstream &, std::unordered_map<std::string, double> &,
		std::unordered_map<std::string, int> & );
void write_to_file(std::ofstream &, std::unordered_map<std::string, double> const&,
		std::unordered_map<std::string,int> const&);
void perform_action(int);
int select_action(std::string const&, std::unordered_map<std::string, double> const&);
double getMaxActionQValue(std::string const&, std::unordered_map<std::string, double> const&);
std::string get_state(int, double, double, double);
double get_reward(std::string const&);

bool training {true};
double explore_chance		{0.5};  // During training phase

int run_qlearning(std::string const& file_name = "", bool train_mode = true)
{	
	training = train_mode;
	/* HARDWARE INITIATION */
	/* INIT */
	wiringPiSetup();
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
	std::unordered_map<std::string, int>    Ntable {}; // Statistics of how many times each combination of state/action has been done

	const double GAMMA_FACTOR	{0.95}; // Always < 1, small values = greedy
	const double LEARNING_RATE	{10};   // Lower values = Quick results but less reliable

	int iterations {0};
	int print_counter  {0};

	bool using_file {false};
	/* Q-Learning INITIATION */

	int		angle	{};
	int oldangle	{(int)adc.getMilliVolts()};
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
			std::ofstream create_file;
			create_file.open(file_name);
			create_file << "Tables with Q and N values from file: " << std::endl;
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
		angle	= adc.getMilliVolts();
		x			= dist.get_distance();

		//auto interval_time = t1.elapsed();
		//t1.reset();

		vangle   = oldangle - angle ;// / interval_time;
//		std::cout << "Vinkelhastigheten är: " <<  vangle << ". Oldangle - angle = " << oldangle - angle<< std::endl;
		vx		   = (oldx - x);// / interval_time;
		oldangle = angle;
		oldx	   = x;

		if(angle_limit(angle))//&& linear_limit(current_pos))
		{
			//action_counter++;
			std::string new_state  {get_state(angle, vangle, x, vx)};
			double reward {get_reward(new_state)};
			if(!previous_state.empty())
			{
				std::string prev_stateaction {previous_state + '/' + std::to_string(previous_action)};

				//Double check if working
				//if(Ntable.find(prev_stateaction) == Ntable.end())
				//	NTable[prev_stateaction] = 0;
				int num_tested {++Ntable[prev_stateaction]};
				//Double check if working

				//if(Qtable.find(prev_stateaction) == Qtable.end())
				//old_qval = Qtable[prev_stateaction];

				double qval = Qtable[prev_stateaction] + (LEARNING_RATE / (LEARNING_RATE / num_tested) *
						(previous_reward+GAMMA_FACTOR*getMaxActionQValue(new_state, Qtable) -
						 Qtable[prev_stateaction]));

				Qtable[prev_stateaction] = qval;

				int action = select_action(new_state, Qtable);
				perform_action(action);

				print_counter++;
				if(print_counter % 10 == 0)
				{
					std::cout << "Iteration: " << iterations << " Action: " << action << " Angle: " << angle << " vAngle : "
						<< vangle << " X: " << x << " vx: " << vx << " Prev State: " << prev_stateaction
						<< " Prev Reward: " << previous_reward << " Prev Q-value: " << qval
						<< " Tested: " << num_tested << " times." << std::endl;
				}
				previous_action = action;
				previous_reward = reward;
			}
			previous_state = new_state;
		}
		else
		{
			//serialClose(fd_arduino);
			digitalWrite(MOTOR_OUT1, 0);
			digitalWrite(MOTOR_OUT2, 0);
			std::cout << "Reached the end of the world!" << std::endl;
			if(using_file)
			{
				std::ofstream write_file;
				write_file.open(file_name);
				write_to_file(write_file, Qtable, Ntable);
				write_file.close();
			}
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
	ofs << "State" << std::setw(22) << "Qvalue" << std::setw(15) << "Nvalue" << std::endl;
	auto itNtable = Ntable.begin();
	for (auto itQtable : Qtable)
	{
		ofs << itQtable.first << std::setw(20) << itQtable.second << std::setw(20) << itNtable -> second << std::endl;
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
//	if (std::abs(v_angle) < 5)
//		v_anglestate = 4;
	if(v_angle > 15)
		v_anglestate = 0;
	else if(v_angle > 5)
		v_anglestate = 2;

	else if(v_angle < -15)
		v_anglestate = 1;
	else if(v_angle < -5)
		v_anglestate = 3;
	else
		v_anglestate = 4;
	
	int xstate {};
	if(x > 0.70)
		xstate = 0;
	else if(x < 0.30)
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

	if(anglestate == 6)
		reward += 20;
	else if(anglestate == 4 || anglestate == 5)
		reward += 10;
	else if(anglestate == 3 || anglestate == 2)
		reward -= 5;
	else
		reward -= 20;

	if(v_anglestate == 4)
		reward += 20;
	else if(v_anglestate == 3 || v_anglestate == 2)
		reward += 5;
	else
		reward -= 20;

	if(xstate == 2)
		reward += 10;

	if(v_xstate == 2)
		reward += 10;

	return reward;
}

//Get highest Qvalue in current state without considering the State
double getMaxActionQValue(std::string const& state, std::unordered_map<std::string, double> const& Qtable)
{
	double maxQval = std::numeric_limits<double>::lowest();
	for(int i{}; i < 3; i++)
	{
		auto table_value {Qtable.find(state + '/' + std::to_string(i))};
		if(table_value != Qtable.end() && table_value -> second > maxQval)
			maxQval = table_value -> second;
	}
	if(maxQval == std::numeric_limits<double>::lowest())
		maxQval = 0; //Uninitialized table value

	return maxQval;
}

int select_action(std::string const& state, std::unordered_map<std::string, double> const& Qtable)
{
	int action {};
	std::random_device rd;	
	std::uniform_int_distribution<int>     distr_action (0,2);
	std::uniform_real_distribution<double> distr_train  (0.0,1.0);

	//Train
	if (training && distr_train(rd) < explore_chance)
		action = distr_action(rd);
	else // Get highest possible Q-value in the given state
	{
		double maxQval = std::numeric_limits<double>::lowest(); // Lowest possible value
		for (int i {}; i < 3; i++)
		{
			std::string test_pair {state + '/' + std::to_string(i)}; //Test all actions
			double Qval {};
			auto table_value = Qtable.find(test_pair);
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


#endif
