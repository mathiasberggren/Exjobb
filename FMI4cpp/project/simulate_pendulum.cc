#include <string>
#include <regex>
#include <memory>
#include <vector>
#include <random>
#include <fstream>
#include <iomanip>
#include <utility>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <filesystem>

/* Local dependencys */ 
#include "PID.h"
#include <type_printing>
#include "./ML-models/net.h"
#include "./ML-models/r_tree.h"
#include "./ML-models/linear_model.h"

/* Installed dependencys */ 
/* https://github.com/lava/matplotlib-cpp */ 
#include "matplotlibcpp.h"
/* https://github.com/NTNU-IHB/FMI4cpp */ 
#include <fmi4cpp/fmi4cpp.hpp>
// #include <fmi4cpp/mlog.hpp>
// #include <fmi4cpp/file_logger.hpp>
using std::cin;
using std::cout;
using std::setw;
using std::endl;
using std::pair;
using std::vector;
using std::string;
using namespace fmi4cpp;
using namespace fmi4cpp::solver;

namespace plt = matplotlibcpp;
typedef vector< pair<vector<double>, double> > Training_data;

/* Macros FILENAME and DIRECTORY is defined when doing make */ 
#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)
#define FILE_NAME (TO_STR(FILENAME))
#define PENDULUM_VERSION (TO_STR(DIRECTORY))
#define LOG_LEVEL_OFF
const double PI {3.14159265359};
const double stop	   {10};
const double stepSize {1E-3};
const vector<unsigned> topology {2, 25, 1};
const string fmuPath = "/home/lapbottom/Programming/Exjobb/Models/\
InvertedPendulum/InvertedPendulum.fmu";

void train_model();
double get_pendulum_start_angle();
double variance(vector<double> const&);
void read_from_file(vector<string> const& files, Training_data &);
void write_to_files(vector<string> const& files, Training_data const&);

void train_linear_model(Training_data const&, Training_data const&, 
    Training_data const&, vector< vector<double> > const& hyper_parameters);

void train_tree(Training_data const&, Training_data const&,
        Training_data const&, vector< vector<unsigned> > const& hyper_parameters);

void train_neuralnet(Training_data const&, Training_data const&,
        Training_data const&, vector< vector<double> > const& hyper_parameters);

/* Test later */ 
void init_simulation(std::unique_ptr<fmi4cpp::fmi2::cs_slave,\
        std::default_delete<fmi4cpp::fmi2::cs_slave> > &);
 /* void run_simulation(std::unique_ptr<fmi4cpp::fmi2::cs_slave,\
        // std::default_delete<fmi4cpp::fmi2::cs_slave> >,\
        // vector<double> & angle_value, vector<double> & angle_velo,\
        // vector<double> & controller_input_value, vector<double> & plot_time,\
        // vector<double> & controller_output_value);
*/


int main()
{
    std::unique_ptr<fmi4cpp::fmi2::cs_slave,\
        std::default_delete<fmi4cpp::fmi2::cs_slave> > slave {};
    init_simulation(slave); 
    
    // cout << "\n\nThe Controller Mode is: " << CONTROLLER_MODE << " [Training mode: " 
        // << TRAINING_MODE << "]" << " and the filename is: " << FILE_NAME 
        // << " and the directory is: " << PENDULUM_VERSION << " and the start_angle is: "
        // << START_ANGLE  << endl;
    
    

    fmi2::fmu fmu(fmuPath);
    auto cs_fmu = fmu.as_cs_fmu();
    auto md = cs_fmu->get_model_description();
    // cout << "Modeldescriptor is of type: " << type_name<decltype(md)> << endl;
    // auto var = md->get_variable_by_name("theta").as_real();
    // auto slave = cs_fmu->new_instance();
// 
    // // cout << "Type of slave: " << type_name<decltype(slave)>() << endl;
    // 
    // /* Initialize pendulum start angle */ 
    // slave->setup_experiment();
    // var.write(*slave,pendulum_angle*PI);
    // slave->enter_initialization_mode();
// 
    // slave->exit_initialization_mode();

    vector<fmi2Real> ref(5);
    vector<fmi2ValueReference> vr = {md->get_variable_by_name("theta").value_reference,
        md->get_variable_by_name("theta_velo").value_reference,
        md->get_variable_by_name("x_pos").value_reference,
        md->get_variable_by_name("x_vel").value_reference,
        md->get_variable_by_name("Y").value_reference};

    auto P_L = md->get_value_reference("L");
    auto M_L = md->get_value_reference("M");
    auto m_L = md->get_value_reference("m");
    auto input_force = md->get_variable_by_name("F").value_reference;
    PID pid {11.9, 0, 1.26, std::numeric_limits<int>::max()}; 

    double L {};
    double M {};
    double m {};

    slave -> read_real(vr, ref);
    slave -> read_real(P_L, L);
    slave -> read_real(M_L, M);
    slave -> read_real(m_L, m);

    cout << "Starting simulation of pendulum.\n\tM = " << M << "\n\tm = " << m
        << "\n\tL = " << L << "\n\tTheta = " << (float)ref[0] * 180 / PI << endl;
#if TRAINING_MODE == 1
    train_model();
    return 0;
#endif

#if CONTROLLER_MODE == 1 
    Net nn_2 { topology };
    nn_2.get_from_file("ML-models/saved_models/best_nn.txt");
#elif CONTROLLER_MODE == 2 
    LinearModel line {};
    line.import("ML-models/saved_models/best_lm.txt");
    // line.import("ML-models/saved_models/linear_regression_model.txt");
#elif CONTROLLER_MODE == 3
    RegressionTree tree {};
    tree.import("ML-models/saved_models/best_tree.txt");
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
        controller_output = line.predict(PI - ref[4], ref[1]);
#elif CONTROLLER_MODE == 3 
        controller_output = tree.predict(PI - ref[4], ref[1]);
#endif

        // slave -> read_real(input_force, force);
        slave -> write_real(input_force, controller_output);

        controller_output_value.push_back(controller_output);
        controller_input_value.push_back(PI - ref[4]);
        angle_value.push_back(ref[4]);
        angle_velo.push_back(ref[1]); 
        // set_point_value.push_back(PI - ref[4]);
        plot_time.push_back(double {t});

        // cout << std::setprecision(2) << std::fixed << std::left << setw(5) << "Time: " 
        // << setw(10) << t << "Theta = " 
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

void init_simulation(std::unique_ptr<fmi4cpp::fmi2::cs_slave,\
        std::default_delete<fmi4cpp::fmi2::cs_slave> > & slave)
{
    fmi2::fmu fmu(fmuPath);
    auto cs_fmu = fmu.as_cs_fmu();
    auto md = cs_fmu->get_model_description();
    slave = cs_fmu->new_instance();
    slave->setup_experiment();

#if TRAINING_MODE == 0
    double pendulum_angle {get_pendulum_start_angle()};

    string pendulum_version = PENDULUM_VERSION;
    std::regex regex_string("(\\d+\\.\\d*|\\d*\\.\\d+)");
    auto words_begin = std::sregex_iterator { pendulum_version.begin(),\
        pendulum_version.end(), regex_string};
    
    std::smatch match1 = *(words_begin++);
    double M = std::stod(match1.str());
    std::smatch match2 = *(words_begin++);
    double L = std::stod(match2.str());
    std::smatch match3 = *(words_begin++);
    double m = std::stod(match3.str());

    auto theta_var = md->get_variable_by_name("theta").as_real();
    auto M_var = md->get_variable_by_name("M").as_real();
    auto m_var = md->get_variable_by_name("m").as_real();
    auto l_var = md->get_variable_by_name("L").as_real();


    // cout << "Type of slave: " << type_name<decltype(slave)>() << endl;
    // mlog::file_logger logfile("log.txt");
    // mlog::manager->set_log(logfile);

    /* Initialize pendulum start parameters */ 
    theta_var.write(*slave, pendulum_angle*PI);
    M_var.write(*slave, M);
    m_var.write(*slave, m);
    l_var.write(*slave, L);
#endif

    slave->enter_initialization_mode();
    slave->exit_initialization_mode();
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

void train_model()
{

    vector<string> gather_files {"training_data23.txt", "training_data34.txt",
        "training_data43.txt", "training_data54.txt",
        "training_data56.txt", "training_data76.txt" }; 

    for(auto &file: gather_files)
        file.insert(0, "./training_data/"); 

    Training_data training_data {};
    read_from_file(gather_files, training_data);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(training_data.begin(), training_data.end(), g);

    // Get the indexes for how to split the data into test / validation / training
    Training_data::const_iterator start { training_data.begin()};

    Training_data::const_iterator train_index_end \
        {training_data.begin() + (int)(training_data.size() * 0.5)};

    Training_data::const_iterator validation_index_end \
        {train_index_end  + (int)(training_data.size() * 0.25)};

    Training_data::const_iterator test_end {training_data.end() - 1};

    Training_data train_data { start, train_index_end};
    Training_data val_data   { train_index_end, validation_index_end};    
    Training_data test_data  { validation_index_end + 1, test_end};

#if CONTROLLER_MODE == 1
    vector<double> epochs        {1, 5, 10, 15, 20, 25, 30, 35, 40};

    vector<double> momentum      {0.001, 0.002, 0.005, 0.008, 0.01, 0.02, 0.03};
    // vector<double> momentum      {0.01, 0.02, 0.03, 0.05, 0.1, 0.3, 0.5};
    vector<double> learning_rate {0.001, 0.002, 0.005, 0.008, 0.01, 0.02, 0.03};
    // vector<double> learning_rate {0.01, 0.02, 0.03, 0.05, 0.1, 0.3, 0.5};
    vector< vector<double> > hyper_params {epochs, momentum, learning_rate};
    train_neuralnet(training_data, test_data, val_data, hyper_params);
#elif CONTROLLER_MODE == 2
    vector<double> epochs        {1, 5, 10, 15, 20, 25, 30, 35, 40};
    // vector<double> learning_rate {0.01, 0.02, 0.03, 0.05, 0.1, 0.3, 0.5};
    vector<double> learning_rate {0.001, 0.002, 0.005, 0.008, 0.01, 0.02, 0.03};
    vector< vector<double> > hyper_params {epochs, learning_rate};
    train_linear_model(training_data, test_data, val_data, hyper_params);
#elif CONTROLLER_MODE == 3
    vector<unsigned> depth   {10, 20, 50};
    vector<unsigned> leaf_k  {10, 50, 100};
    vector< vector<unsigned> > hyper_params {depth, leaf_k};
    train_tree(training_data, test_data, val_data, hyper_params);
#endif
}

void train_neuralnet(Training_data const& train_data, Training_data const& test_data,
        Training_data const& , vector< vector<double> > const& hyper_parameters)
{
    vector<double> epochs      = hyper_parameters[0]; 
    vector<double> learning_rate = hyper_parameters[1];
    vector<double> momentum        = hyper_parameters[2];
      
    for(double m : momentum)
    {
        for(double l : learning_rate) 
        {
            for(unsigned epoch : epochs) 
            {
                Net local_net {topology};
                Neuron::eta   = l;
                Neuron::alpha = m; 
                for(unsigned i {}; i < epoch; i++)
                {
                    local_net.train(train_data);
                } 

                if(std::filesystem::exists("./ML-models/saved_models/best_nn.txt"))
                {
                    cout << "Trained Local net. Momentum: " << m << " Learning rate: "
                        << l << " Epochs: " << epoch << endl;
                    Net nn2 { topology };
                    nn2.get_from_file("./ML-models/saved_models/best_nn.txt");
                    double local_loss = local_net.loss(test_data); 
                    cout << "Local Net loss: " << local_loss << endl;
                    double file_loss = nn2.loss(test_data);
                    cout << "File Net loss: " << file_loss << endl;
                    if(local_loss < file_loss)
                        local_net.dump_to_file("./ML-models/saved_models/best_nn.txt");  
                }
                else
                    local_net.dump_to_file("./ML-models/saved_models/best_nn.txt");  
                

            }
        }
    }
}

void train_tree(Training_data const& train_data, Training_data const& test_data,
        Training_data const& , vector< vector<unsigned> > const& hyper_parameters)
{
    vector<unsigned> depths = hyper_parameters.front(); 
    vector<unsigned> leaf_k = hyper_parameters.back();
    cout << "---------------- Starting training of tree -----------------" << endl;
      
    for(unsigned depth : depths)
    {
        for(unsigned k : leaf_k) 
        {
            RegressionTree local_tree {depth, k};
            local_tree.train(train_data);
            double loss = local_tree.loss(test_data);

            cout << "Trained tree with depth = " << depth 
                << " and leaf_k = " << k << " got loss: "
                << loss << endl;
            if(std::filesystem::exists("./ML-models/saved_models/best_tree.txt"))
            {
                RegressionTree t2 {};
                t2.import("./ML-models/saved_models/best_tree.txt");
                double local_loss = local_tree.loss(test_data);
                cout << "Local Tree loss: " << local_loss << endl;
                double file_loss = t2.loss(test_data);
                cout << "File Tree loss: " << file_loss << endl;
                if(local_loss < file_loss)
                    local_tree.dump("./ML-models/saved_models/best_tree.txt");  
            }
            else
                local_tree.dump("./ML-models/saved_models/best_tree.txt");  
        }
    }
    RegressionTree tree {};
    tree.import("./ML-models/saved_models/best_tree.txt");
    cout << "Trained Tree model loss [" << tree.loss(test_data) << "]" << endl;

}

void train_linear_model(Training_data const& train_data, Training_data const& test_data, 
    Training_data const& , vector< vector<double> > const& hyper_parameters)
{
    vector<double> epochs        = hyper_parameters.front();
    vector<double> learning_rate = hyper_parameters.back();

    for(double l : learning_rate) 
    {
        for(unsigned epoch : epochs) 
        {
            LinearModel l_model {l};
            l_model.fit(train_data, epoch);

            cout << "Trained Local LM. Learning rate: " << l << " Epochs: " 
                << epoch << endl;
            if(std::filesystem::exists("./ML-models/saved_models/best_lm.txt"))
            {
                LinearModel l_2 {};
                l_2.import("./ML-models/saved_models/best_lm.txt");
                double local_loss = l_model.loss(test_data); 
                cout << "Local LM loss: " << local_loss << endl;
                double file_loss = l_2.loss(test_data);
                cout << "File LM loss: " << file_loss << endl;
                if(local_loss < file_loss)
                    l_model.dump("./ML-models/saved_models/best_lm.txt");  
            }
            else
                l_model.dump("./ML-models/saved_models/best_lm.txt");  

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
