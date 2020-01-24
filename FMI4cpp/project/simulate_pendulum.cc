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
#include "./ML-models/r_tree.h"

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
const vector<unsigned> topology {2, 25, 1};

void read_from_file(vector<string> const& files, Training_data & training_data);
void write_to_files(vector<string> const& files, Training_data const& training_data);
double variance(vector<double> const&);
double get_pendulum_start_angle();

void train_neuralnet(Net &, Training_data const&, Training_data const&,
        Training_data const&);
void train_linear_model(LinearModel &, Training_data const&,
        Training_data const&, Training_data const&);
void train_tree(RegressionTree &, Training_data const&, Training_data const&,
        Training_data const&);

int main()
{
    double pendulum_angle {get_pendulum_start_angle()};

    cout << "\n\nThe Controller Mode is: " << CONTROLLER_MODE << " [Training mode: " 
        << TRAINING_MODE << "]" << " and the filename is: " << FILE_NAME 
        << " and the directory is: " << PENDULUM_VERSION << " and the start_angle is: "
        << START_ANGLE << " and our pendulum_angle is set to: "<< pendulum_angle << endl;

    fmi2::fmu fmu(fmuPath);
    auto cs_fmu = fmu.as_cs_fmu();
    auto md = cs_fmu->get_model_description();
    auto var = md->get_variable_by_name("theta").as_real();
    auto slave = cs_fmu->new_instance();

    /* Initialize pendulum start angle */ 
    slave->setup_experiment();
    var.write(*slave,pendulum_angle*PI);
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

#if TRAINING_MODE == 1
    train_models();
    return 0;
#elif TRAINING_MODE == 0
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
    // double force {};
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


double get_pendulum_start_angle()
{
    int factor1 {};
    int factor2 {};
    char trash {};
    std::stringstream ss {};

    ss << START_ANGLE;
    ss >> factor1;
    ss >> trash;
    ss >> factor2;

    return (static_cast<double>(factor1)/static_cast<double>(factor2));
}

void train_models()
{

    vector<string> gather_files {"training_data23.txt", "training_data34.txt",
        "training_data43.txt", "training_data54.txt",
        "training_data56.txt", "training_data76.txt" }; 
    for(auto &file: gather_files)
        file.insert(0, "./training_data/"); 

    Training_data training_data {};
    read_from_file(gather_files, training_data);
    if(0)
    {
        vector<string> output_files { "input.csv", "gold_data.csv" };
        write_to_files(output_files, training_data);
        return;
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
    Net nn(topology);
    train_neural_net(nn, training_data, test_data, val_data);
#elif CONTROLLER_MODE == 2
    LinearModel l_model {1/k};
    train_linear_model(l_model, training_data, test_data, val_data);
#elif CONTROLLER_MODE == 3

#endif
}

void train_neural_net(Net & nn, Training_data const& train_data,
        Training_data const& test_data, Training_data const& val_data)
{
    for(int i {}; i < 100; i++)
    {
        nn.train(train_data);
        double val_error { nn.validate(test_data) };
        cout << "This is the average error after " << i+1 << " epoch: " << nn.get_recent_average_error() 
            << " and this is the validation error: " << val_error << endl;
        if(val_error < 0.002)
            break; 
    } 

    nn.dump_to_file("temp_nn.txt");  
    Net nn_2 { topology };
    nn_2.get_from_file("temp_nn.txt");
    cout << "This is the validation error for the nn2 network: " << nn_2.validate(test_data) << endl;
}

void train_linear_model(LinearModel & l_model, Training_data const& train_data,
        Training_data const& test_data, Training_data const& val_data)
{
    // LinearModel l_model {1/k};
    double k {1}; 
    while(k++ < 20)
    {
        for(int i {1}; i < 20; i++)
        {
            l_model.fit(train_data, i);
            cout << "This is the loss for the linear_regression_model learning rate " \
                << 1/k << "one epoch: " << i << " is: " << l_model.loss(val_data) << endl;
        }
    }
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
