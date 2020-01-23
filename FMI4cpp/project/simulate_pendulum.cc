#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
#include <random>

#include <type_printing>
#include <fmi4cpp/fmi4cpp.hpp>

#include "matplotlibcpp.h"
#include "PID.h"
#include "./ML-models/net.h"
#include "./ML-models/linear_model.h"

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

/* Macros FILENAME and DIRECTORY is defined when doing make */ 
#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)
#define FILE_NAME (TO_STR(FILENAME))
#define PENDULUM_VERSION (TO_STR(DIRECTORY))

typedef vector< pair<vector<double>, double> > Training_data;

const double PI {3.14159265359};
const double stop	   {10};
const double stepSize {1E-3};
const string fmuPath = "/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum/InvertedPendulum.fmu";
const string xmlPath = "/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum.xml";

void read_from_file(vector<string> const& files, Training_data & training_data);
void write_to_files(vector<string> const& files, Training_data const& training_data);
double variance(std::vector<double> const&);

int main()
{
    cout << "\n\nThe Controller Mode is: " << CONTROLLER_MODE << " [Training mode: " << TRAINING_MODE << "]" << " and the filename is: " << FILE_NAME << " and the directory is: " << PENDULUM_VERSION << endl;


    fmi2::fmu fmu(fmuPath);
    auto cs_fmu = fmu.as_cs_fmu();
    auto md1 = cs_fmu->get_model_description();
    cout << "decltype(md1) is " << type_name<decltype(md1)>() << endl;

 
    // cout << "decltype(md2) is " << type_name<decltype(md2)>() << endl;
    // auto md_cs  = md2->as_cs_description();
    // auto slave  = md_cs->new_instance();
    return 0;
	/* Model initialization */ 
    // fmi2::fmu fmu(fmuPath);
    // auto cs_fmu = fmu.as_cs_fmu();
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

    auto input_force = md->get_variable_by_name("F").value_reference;
    vector<unsigned> topology {2, 25, 1};
    PID pid {11.9, 0, 1.26, std::numeric_limits<int>::max()}; 

    #if TRAINING_MODE == 1
        Net nn(topology);
        vector<string> gather_files {"neural_training_data23.txt", "neural_training_data34.txt",
                                "neural_training_data43.txt", "neural_training_data54.txt",
                                "neural_training_data56.txt", "neural_training_data76.txt" }; 

        Training_data training_data {};
        read_from_file(gather_files, training_data);
        if(0)
        {
            vector<string> output_files { "input.csv", "gold_data.csv" };
            write_to_files(output_files, training_data);
            slave -> terminate();
            return 0;
        }

        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(training_data.begin(), training_data.end(), g);
        /* ***************** */

        cout << "This is the current number of training points that we got in our vector: " \
                << training_data.size() << endl;

        // Get the indexes for how to split the data into test / validation / training
        Training_data::const_iterator start { training_data.begin()};
        Training_data::const_iterator train_index_end \
            {training_data.begin() + (int)(training_data.size() * 0.5)};
        Training_data::const_iterator validation_index_end \
            {train_index_end  + (int)(training_data.size() * 0.25)};
        Training_data::const_iterator test_end\
             {training_data.end() - 1};

        Training_data train_data { start, train_index_end};
        Training_data val_data   { train_index_end + 1, validation_index_end};    
        Training_data test_data  { validation_index_end + 1, test_end};

        #if CONTROLLER_MODE == 1
            for(int i {}; i < 100; i++)
            {
                nn.train(training_data);
                double val_error { nn.validate(training_data) };
                cout << "This is the average error after " << i+1 << " epoch: " << nn.get_recent_average_error() 
                        << " and this is the validation error: " << val_error << endl;
                if(val_error < 0.002)
                    break; 
            } 
            
            nn.dump_to_file("temp_nn.txt");  
            Net nn_2 { topology };
            nn_2.get_from_file("temp_nn.txt");
            cout << "This is the validation error for the nn2 network: " << nn_2.validate(training_data) << endl;
            slave -> terminate();
            return 0;
        #elif CONTROLLER_MODE == 2
            double k {1}; 
            while(k++ < 20)
            {
                for(int i {1}; i < 20; i++)
                {
                    LinearModel l_model {1/k};
                    l_model.fit(train_data, i);
                    cout << "This is the loss for the linear_regression_model learning rate " \
                        << 1/k << "one epoch: " << i << " is: " << l_model.loss(val_data) << endl;
                }
            }
            slave -> terminate();
            return 0;
        #elif CONTROLLER_MODE == 3
            slave -> terminate();
            return 0;
        #endif
    #elif !TRAINING_MODE
        #if CONTROLLER_MODE == 1 
            Net nn_2 { topology };
            nn_2.get_from_file("ML-models/saved_models/temp_nn.txt");
        #elif CONTROLLER_MODE == 2 
            LinearModel line {};
            line.import("linear_regression_model.txt");
        #elif CONTROLLER_MODE == 3
            // Import some tree stuff
            
        #endif
    #endif

    vector<double> angle_value	   {};
    vector<double> angle_velo	   {};
    vector<double> controller_input_value {}; 
    vector<double> controller_output_value {};
    vector<double> plot_time       {};
    double t = 0;
    double force {};
    while ( ( t = slave->get_simulation_time()) <= stop) 
    {
        /* Read variables from simulation */ 
        if (!slave->step(stepSize)) { break; }
        if (!slave->read_real(vr, ref)) { break; }
        
        double controller_output {};
        #if CONTROLLER_MODE == 0
            // Avoid spike for D-term in PID when old_error does not exist
            int rounded_t = t * 1000;
            if(rounded_t == 0) 
            { 
                pid.set_old_error(PI-ref[4]);
            }
            controller_output = pid.calculate(PI-ref[4]);
        #elif CONTROLLER_MODE == 1
            vector<double> nn_input { PI - ref[4], ref[1] };
            controller_output = nn_2.forward(nn_input);
        #elif CONTROLLER_MODE == 2

        #elif CONTROLLER_MODE == 3 
        
        #endif
        // slave -> read_real(input_force, force);
        slave -> write_real(input_force, controller_output);
        slave -> write_real(input_force, controller_output);

        controller_output_value.push_back(controller_output);
        controller_input_value.push_back(PI - ref[4]);
        angle_value.push_back(ref[4]);
        angle_velo.push_back(ref[1]); 
        // set_point_value.push_back(PI - ref[4]);
        plot_time.push_back(double {t});

        // cout << std::setprecision(2) << std::fixed << std::left << setw(5) << "Time: " << setw(10) << t << "Theta = " 
                // << setw(10) << (float)ref[0] * 180 / PI << "Theta velo: " << setw(10) << (float)ref[1]  
                // << "x_pos: " << setw(10) << (float)ref[2] <<  "x_vel: " << setw(10) 
                // << (float)ref[3] << "Y: " << setw(10) << (float)ref[4] << "F: " << setw(10) 
                // << (float)force << "Setpoint - Y: " << setw(10) << PI - ref[4] << endl;

    }
    
    std::stringstream ss {};
    ss << PENDULUM_VERSION << "/" << FILE_NAME;
    string file_specifics { ss.str()};
    std::ofstream myfile { file_specifics + ".txt"};

    for(size_t i {}; i < controller_input_value.size(); i++)
    {
        myfile << plot_time[i] << " " << angle_value[i] << " " << angle_velo[i] 
            << " " <<  controller_input_value[i] << " " << controller_output_value[i] << endl;
    } 
    myfile.close();
     
    plt::figure_size(1200, 780);
    plt::plot(plot_time, angle_value);
    plt::ylim(1, 5);
    plt::title("Value of angle (rad)");	

    string filename {file_specifics + ".png" };

    cout << "Saving result to " << filename << endl;
    plt::save(filename);

    slave->terminate();

	return 0;
}

void read_from_file(vector<string> const& files, Training_data & training_data)
{
    double input;
    double gold;
    double time;
    double angle;
    double angle_velo;
    for(auto file_name : files)
    {
        std::ifstream file {file_name};
        std::string file_row {};
        while(getline(file, file_row))
        {
            std::stringstream ss {file_row};
            ss >> time >> angle >> angle_velo >> input >> gold;
            /* Avoid too much training data for when pendulum have stabilized */ 
            vector<double> input_vec { input, angle_velo}; 
            if(time < 4.5)
                training_data.push_back(pair<vector<double>, double>(input_vec, gold) );
            // cout << time << " " << angle << " " << angle_velo << " " << input << " " << gold << endl;
        }
        cout << "Processed file: " << file_name << " and got " << training_data.size() 
                << " training data points!" << endl;
    }
}

void write_to_files(vector<string> const& files, Training_data const& training_data)
{
    for(auto file_name : files)
    {
        std::ofstream file {file_name};
        for(auto it : training_data)
        {
            // First file equals input file
            if(file_name == files[0])
            {
                std::stringstream ss {};
                for(auto input {begin(it.first)}; input != end(it.first); input++)
                {
                    if(input + 1 != end(it.first))
                        ss << *input << ","; 
                    else
                        ss << *input << "\n"; 
                }
                file << ss.str(); 
            } 
            else if(file_name == files[1])
            {
                std::stringstream ss {};
                ss << it.second << "\n";
                file << ss.str();
            }
            else
            { 
                std::cerr << "This was not good, you sent more than input and output\
                    file into write_to_files function. Try again. " << endl;
            }
        }
    }
    cout << "Finished writing to files." << endl;
}

double variance(std::vector<double> const& samples)
{
	size_t n {samples.size()};
	double mean = std::accumulate(samples.begin(), samples.end(), 0.0) / n;

	auto variance_func = [&mean, &n](double accumulator,const double& val)
	{
        return accumulator + ((val - mean)*(val - mean) / (n - 1));
    };


	return std::accumulate(samples.begin(), samples.end(), 0.0, variance_func);
}
