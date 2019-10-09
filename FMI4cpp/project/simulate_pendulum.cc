
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>

#include <fmi4cpp/fmi4cpp.hpp>

#include "matplotlibcpp.h"
#include "PID.h"
#include "net.h"

// using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::setw;
using std::string;
using std::pair;
using namespace fmi4cpp;
using namespace fmi4cpp::solver;
namespace plt = matplotlibcpp;

const double PI {3.14159265359};
const double stop	   {10};
const double stepSize {1E-3};
const string fmuPath = "/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum/InvertedPendulum.fmu";

double variance(std::vector<double> const&);
void read_from_file(vector<std::ifstream & ifs> const& files, std::unordered_map<double, double> & training_data);


int main()
{
    // vector<vector<double>> simulations {};
	// double loop {1.26};
	// while(loop < 2)
	// {
		/* Model initialization */ 

		fmi2::fmu fmu(fmuPath);
		auto cs_fmu = fmu.as_cs_fmu();
		auto md = cs_fmu->get_model_description();

		auto slave = cs_fmu->new_instance();

		slave->setup_experiment();
		slave->enter_initialization_mode();
		slave->exit_initialization_mode();


		vector<fmi2Real> ref(5);
		vector<fmi2ValueReference> vr = {md->get_variable_by_name("theta").value_reference,
										 md->get_variable_by_name("theta_velo").value_reference,
										 md->get_variable_by_name("x_pos").value_reference,
										 md->get_variable_by_name("x_vel").value_reference,
										 md->get_variable_by_name("Y").value_reference};

		// auto speed = md->get_variable_by_name("x_vel").value_reference;
		auto input_force = md->get_variable_by_name("F").value_reference;
		/* ***************** */

		/* PID Controll init */
		// P = 6.4 :: 4.5 OLD: ~11.6 ( Testar med 8)  
		// D = 0.628
        // P == 11.9 
        //
        // 1.19
        // 1.26
		PID pid {11.9, 0, 1.26, std::numeric_limits<int>::max()}; 

		/* ***************** */
		vector<double> angle_value	   {};
        vector<double> pid_input_value {}; 
        vector<double> pid_output_value {};
		// vector<double> set_point_value {};
		// vector<double> x_pos_value     {};
		// vector<double> x_velo_value    {};
		vector<double> plot_time       {};
		double t = 0;
		double force {};
		while ( ( t = slave->get_simulation_time()) <= stop) 
		{
			/* Read variables from simulation */ 
			if (!slave->step(stepSize)) { break; }
			if (!slave->read_real(vr, ref)) { break; }

            // Avoid spike for D-term in PID when old_error does not exist
			int rounded_t = t * 1000;
			if(rounded_t == 0) 
			{ 
                pid.set_old_error(PI-ref[4]);
			}

            double pid_output {pid.calculate(PI-ref[4])};
			slave -> read_real(input_force, force);
			slave -> write_real(input_force, pid_output);
			angle_value.push_back(ref[4]);
            pid_output_value.push_back(pid_output);
		    pid_input_value.push_back(PI - ref[4]);
            
		    // set_point_value.push_back(PI - ref[4]);
			plot_time.push_back(double {t});

			cout << std::setprecision(2) << std::fixed << std::left << setw(5) << "Time: " << setw(10) << t << "Theta = " 
					<< setw(10) << (float)ref[0] * 180 / PI << "Theta velo: " << setw(10) << (float)ref[1]  
					<< "x_pos: " << setw(10) << (float)ref[2] <<  "x_vel: " << setw(10) 
					<< (float)ref[3] << "Y: " << setw(10) << (float)ref[4] << "F: " << setw(10) 
					<< (float)force << "Setpoint - Y: " << setw(10) << PI - ref[4] << endl;

			/* ****************************** */
			// else if(rounded_t == 101)
			// {
				// // slave -> write_real(speed, 0); 
				// slave -> write_real(input_force, -100); 
			// }
			// else if(rounded_t > 101)
			// Degrees 	
			// angle_value.push_back(double {ref[4]} *180 / PI);
			// Radians 
			// x_pos_value.push_back(ref[2]);
			// x_velo_value.push_back(ref[3]);

			
		}
         
        std::ofstream myfile {"./neural_training_data23.txt"};

        for(int i {}; i < pid_input_value.size(); i++)
        {
            myfile << plot_time[i] << " " << angle_value[i] << " " <<  pid_input_value[i] \
                    << " " << pid_output_value[i] << endl;
        } 
         
        myfile.close();
         
		plt::figure_size(1200, 780);
		plt::plot(plot_time, angle_value);
		plt::ylim(1, 5);
		plt::title("Value of angle (rad)");	
		string filename = "./PID_IMG/pid23.png";	
		cout << "Saving result to " << filename << endl;
		plt::save(filename);

        slave->terminate();

		// plt::plot(plot_time, x_pos_value);
		// plt::plot(plot_time, x_velo_value);
		// string filename = "./PID_I/pid" + std::to_string(loop) + ".png";	
		
        // for (double i{1.0}; i < 2.0; i += 0.1)
        // {
            // if (i == 1.0) 
                // simulations.push_back(vector<double> {PI-angle_value[1000]}); 
            // else
                // simulations.back().push_back(PI-angle_value[i * 1000]);
        // }
		// cout << "FMU '" << fmu.model_name() << "' terminated with success: " 
				// << (slave->terminate() == 1 ? "true" : "false") << endl;
		// loop += 0.01;
	// }

    // static const auto abssum = [] (auto x, auto y) {return x + std::abs(y);};
    // for(auto it {simulations.begin()}; it != simulations.end(); it++)
     // {
        // cout << "The size is: " << simulations.size() << "; ";
        // cout << "the index is: " << it - simulations.begin() << "; ";
        // cout << "the size of the inner container is: " << it->size() << "; ";
        // cout << "the total sum: " << std::accumulate(it->begin(), it->end(), 0.0, abssum) << endl;
     // }
	return 0;
}

double variance(std::vector<double> const& samples)
{
	size_t n {samples.size()};
	double mean = std::accumulate(samples.begin(), samples.end(), 0.0)/samples.size();

	auto variance_func = [&mean, &n](double accumulator,const double& val)
	{
        return accumulator + ((val - mean)*(val - mean) / (n - 1));
    };


	return std::accumulate(samples.begin(), samples.end(), 0.0, variance_func);
}
