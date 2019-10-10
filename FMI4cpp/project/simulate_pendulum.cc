
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

typedef vector< pair< double, double> > Training_data;

const double PI {3.14159265359};
const double stop	   {10};
const double stepSize {1E-3};
const string fmuPath = "/home/lapbottom/Programming/Exjobb/Models/InvertedPendulum/InvertedPendulum.fmu";

double variance(std::vector<double> const&);
void read_from_file(vector<string> const& files, Training_data & training_data);

int main()
{
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

    auto input_force = md->get_variable_by_name("F").value_reference;
    PID pid {11.9, 0, 1.26, std::numeric_limits<int>::max()}; 
    vector<unsigned> topology {1, 10, 1};
    Net nn(topology);
    vector<string> files {  "neural_training_data23.txt", "neural_training_data34.txt",
                            "neural_training_data43.txt", "neural_training_data54.txt",
                            "neural_training_data56.txt", "neural_training_data76.txt" }; 

    Training_data training_data {};

    read_from_file(files, training_data);


    // for(auto container : training_data)
    // {
        // for(auto datapoint : container.first)
            // cout << "The datapoint is: " << datapoint << endl; 
    // }
    // Mix the data 
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


    cout << train_data.size() << " " << val_data.size() << " " << test_data.size() << endl;
    cout << "Train_index: 0-" << train_index_end - training_data.begin() 
            << "\nVal index: " << train_index_end + 1 -training_data.begin() << "-" 
            << validation_index_end - training_data.begin() << "\nTest index: " 
            << validation_index_end + 1 - training_data.begin() << "-" << training_data.size() - 1
            << endl; 

    nn.train(train_data);
    cout << "This is the average error after 1 epoch: " << nn.get_recent_average_error() << endl;
    nn.train(train_data);
    cout << "This is the average error after 2 epochs: " << nn.get_recent_average_error() << endl;
    nn.train(train_data);
    cout << "This is the average error after 3 epoch: " << nn.get_recent_average_error() << endl;
    nn.train(train_data);
    cout << "This is the average error after 4 epochs: " << nn.get_recent_average_error() << endl;
    slave -> terminate();
    return 0;
    // validation_index_end - train_index_end 
    vector<double> angle_value	   {};
    vector<double> pid_input_value {}; 
    vector<double> pid_output_value {};
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

    }
     
    std::ofstream myfile {"./neural_training_data23.txt"};

    for(size_t i {}; i < pid_input_value.size(); i++)
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

	return 0;
}

void read_from_file(vector<string> const& files, Training_data & training_data)
{
    double input;
    double gold;
    double time;
    double angle;
    for(auto file_name : files)
    {
        std::ifstream file {file_name};
        std::string file_row {};
        while(getline(file, file_row))
        {
            std::stringstream ss {file_row};
            ss >> time >> angle >> input >> gold;
            /* Avoid too much training data for when pendulum have stabilized */ 
            if(time < 4.5)
                training_data.push_back(pair<double, double>(input, gold) );
            // cout << time << " " << angle << " " << input << " " << gold << endl;
        }
        cout << "Processed file: " << file_name << " and got " << training_data.size() 
                << " training data points!" << endl;
    }
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
