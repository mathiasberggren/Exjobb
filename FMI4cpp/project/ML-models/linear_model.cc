#include <algorithm> 
#include <cassert>
#include <cmath>
#include <iostream>
#include <fstream>
#include <exception>

#include "linear_model.h"

#define DEBUG_MODE 1

LinearModel::LinearModel(double learning_rate) 
    : learning_rate {learning_rate}, change_k1 {}, change_k2{}, change_m{}, k1 {1}, k2 {1}, m {1} {}

inline double LinearModel::predict(double x1, double x2)const 
{ return x1 * k1 + x2 * k2 + m; } 

double LinearModel::loss(Training_data const& train_data)const
{
    double sum {};
    for(auto training_sample : train_data)
    {
        sum += loss(training_sample.first[0], training_sample.first[1], training_sample.second);
    }

    return sum;
}

void LinearModel::fit(Training_data const& training_data, int epochs)
{
    assert(training_data.size() != 0);

    /* Initialize m so that we have a straight line between the highest and the lowest value */
    auto [min, max] = std::minmax_element(training_data.begin(), training_data.end(), \
            [](std::pair<std::vector<double>, double> const& a, \
                std::pair<std::vector<double>, double> const& b) \
            { return a.second < b.second; });
    m = ((*max).second + (*min).second) / 2 ;

    #if DEBUG_MODE
        std::cout << "m was initialized to : " << m << std::endl;
    #endif

    while(epochs-- > 0)
    {
        for(auto training_sample : training_data)
        {
            change_k1 = learning_rate * der_loss_k1(training_sample.first[0], \
                    training_sample.first[1], training_sample.second);
            change_k2 = learning_rate * der_loss_k2(training_sample.first[0], \
                    training_sample.first[1], training_sample.second);
            change_m  = learning_rate * der_loss_m(training_sample.first[0],   \
                    training_sample.first[1], training_sample.second);
        }
        k1 -= change_k1;
        k2 -= change_k2;
        m  -= change_m;
    }


    #if DEBUG_MODE
        std::cout << "The changes; k1: " << change_k1 << " k2: " << change_k2 << " m: " << change_m << std::endl;
    #endif

    std::cout << "The fitted line is: " << k1 << " * x1 + " << k2 << " * x2 + " << m << "." << std::endl;
}

void LinearModel::dump(std::string const& filename )const
{
    try{
        std::ofstream out_file {filename};
        out_file << k1 << " " << k2 << " " << m << std::endl;
    }
    catch(std::exception& e){
        std::cerr << "Could not open/write fo file \"" << filename 
            << "\" in function LinearModel::dump. Try again." << std::endl;
    }
}

void LinearModel::import(std::string const& filename)
{
    try{
        std::ifstream in_file {filename};
        in_file >> k1 >> k2 >> m;
    }
    catch(std::exception& e){
        std::cerr << "Could not open/read from file \"" << filename 
            << "\" in function LinearModel::import. Try again." << std::endl;
    }
}
inline double LinearModel::residual(double x1, double x2, double y)const
{ return y - predict(x1, x2); }

/* Sum of squared residuals as loss function */
inline double LinearModel::loss(double x1, double x2, double y)const
{ return std::pow(residual(x1, x2, y), 2); }

inline double LinearModel::der_loss_k1(double x1, double x2, double y)const
{ return -2 * k1 * residual(x1, x2, y); }

inline double LinearModel::der_loss_k2(double x1, double x2, double y)const
{ return -2 * k2 * residual(x1, x2, y); }

inline double LinearModel::der_loss_m(double x1, double x2, double y)const
{ return -2 * m * residual(x1, x2, y); }
