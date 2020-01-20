#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "net.h"

using std::cout;
using std::endl;

double Neuron::eta   = 0.01; // Learning rate
double Neuron::alpha = 0.5;  // Momentum, multiplier of last delta weight

Net::Net(vector<unsigned int> const& topology)
    :layers{}, error {}, recent_average_error {}, smoothing_factor {}
{
    /* Long to avoid type conversion */
    long unsigned int num_layers { topology.size()};

    for (unsigned int layer_index {}; layer_index < num_layers; layer_index++)
    {
        layers.push_back(Layer());
        unsigned int outputs { layer_index == topology.size() - 1 ? 0 : topology[layer_index+1]};
        for(unsigned int neuron_index {}; neuron_index <= topology[layer_index]; neuron_index++)
        {
            layers.back().push_back(Neuron{outputs, neuron_index});
        }
    }

    // Force bias node's output value to 1.0
    layers.back().back().set_output(1.0);
}

void Net::train(Training_data const& training_data)
{
    smoothing_factor = training_data.size();
    for(auto training_sample : training_data)
    {
        // vector<double> first { training_sample.first };
        vector<double> second { training_sample.second };
        // cout << "first[0] = " << training_sample.first[0] << " first[1] = " << training_sample.first[1] 
            // << "output = " << forward(training_sample.first) << " gold = " << second[0] << endl;
        forward(training_sample.first);
        backpropagate(second); 
    }

    

}

void Net::backpropagate(vector<double> const& gold)
{
    Layer& output_layer { layers.back() };
    error = 0;

    /* Get the sum of all output neurons */ 	
    for(unsigned n {}; n < output_layer.size() - 1; ++n)
    { 
        double delta { gold[n] - output_layer[n].get_output() };
        // cout << "Gold = " << gold[n] << " Y-hat = " << output_layer[n].get_output() << endl; 
        error += delta * delta;
    }
    error /= output_layer.size() - 1; // Average squared error
    error = sqrt(error); // RMS (Root Mean Square)
   
    recent_average_error = (recent_average_error * smoothing_factor + error) / (smoothing_factor + 1.0);
    // cout << "The recent_average_error is: " << recent_average_error << " smoothing_factor: "  
        // << smoothing_factor << " the error is: " << error << endl;
    // Calculate gradients for output neurons
    for(unsigned n {0}; n < output_layer.size() - 1; ++n)
        output_layer[n].calc_output_gradients(gold[n]);

    // Calculate gradients on hidden layers, skip bias?
    for(long unsigned int layer_index {layers.size() - 2}; layer_index > 0; --layer_index)
    {
        Layer& hidden_layer { layers[layer_index] }; 	
        Layer& next_layer   { layers[layer_index + 1] };

        for(unsigned int i {}; i < hidden_layer.size(); i++)
        {
            hidden_layer[i].calc_hidden_gradients(next_layer);
        } 
    }

    for(long unsigned int layer_index {layers.size() - 1}; layer_index > 0; --layer_index)
    {
        Layer& layer { layers[layer_index] };
        Layer& previous_layer { layers[layer_index - 1] };

        for(unsigned int i {}; i < layer.size() - 1; ++i)
        {
            layer[i].update_input_weights(previous_layer);
        }	
    } 
}

double Net::forward(vector<double> const& input)
{
    // Assign the input values into the input neurons (layer 0)	
    /* CHANGE: loop over layers[0] iterators to increase performance */ 
    for(unsigned int i {}; i < input.size(); i++)
    {
    	
        layers[0][i].set_output(input[i]);
    }
    // Forward through all layers
    for(unsigned int layer_index {1}; layer_index < layers.size(); layer_index++) 
    {
        Layer& prev_layer { layers[layer_index-1] }; 
        /* Call forward on each individual neuron */
        for(unsigned int i {}; i < layers[layer_index].size() - 1; i++)
            layers[layer_index][i].forward(prev_layer);
    }

    // Layer& output_layer { layers.back() };

    // for(int i {}; i < output_layer.size() - 1; i++)
        // cout << "This is the output from neuron " << i << " :  " << output_layer[i].get_output() << endl;

    return get_result();
}

double Net::validate(Training_data const& validation_data)
{
    double sum_square_error {};
    for(auto datapoint : validation_data)
    {
        vector<double> input_data {datapoint.first};
        forward(input_data);
        sum_square_error += std::pow(datapoint.second - get_result(), 2); 
    }
    return sum_square_error/validation_data.size(); 

}
inline double Net::get_result()const
{
    return layers.back()[0].get_output();
}

void Net::dump_to_file(std::string const& filename)const
{
    vector<double> temp_weights;
    get_weights(temp_weights);

    std::ofstream file { filename };
    for(auto w : temp_weights)
        file << w << " ";
}

void Net::get_from_file(std::string const& filename)
{
    std::ifstream file { filename };
    vector<double> temp_weights {};
    double t_w {};
    while(file >> t_w)
    {
        temp_weights.push_back(t_w);
    }

    set_weights(temp_weights); 
}

void Net::get_weights(vector<double> & w)const
{
    for(auto layer : layers)
    {
        for(auto neuron : layer)
        {
            for(auto c : neuron.output_weights)
                w.push_back(c.weight);        
        }
    } 
}

void Net::set_weights(vector<double> const& w)
{
    int i {};
    for(auto &layer : layers)
    {

        for(auto &neuron : layer)
        {
            for(auto &c : neuron.output_weights)
                c.weight = w[i++];        
        }
    } 
    cout << "Successfully loaded weights, there were " << i << " weights in total!" << endl;
}

Neuron::Neuron(unsigned int outputs, unsigned int index)
    : output_value {}, output_weights{},  my_index {index}, gradient {} 
{
    for(unsigned int i {}; i < outputs; i++)
        output_weights.push_back(Connection());
}

void Neuron::forward(Layer const& prev_layer)
{
    double sum {};

    /* Get all inputs from Neurons on prev layer, include the bias neuron */ 
    for(unsigned int i {}; i < prev_layer.size(); i++)
    {
        sum += prev_layer[i].get_output() * 
            prev_layer[i].output_weights[my_index].weight;
    }

    /* CHANGE: Make it possible to change transfer function
     * depending on function call, this would make it possible
     * to have a differenttransfer function for the output neuron(s)
     *  */
    // cout << "This is my index : " << my_index << " doing forward, " 
        // << "the previous layer has size: " << prev_layer.size() 
        // << " and the sum is " << sum << endl; 


    // Let the output Neuron have a linear activation function 
    if(prev_layer.size() > 3) 
        output_value = sum; 
    else   
        output_value = Neuron::transfer_function(sum);
}

void Neuron::calc_output_gradients(double gold)
{
    double delta = gold - output_value;
    if(delta > 0)
    {
        gradient = 1;
        // gradient = delta;
    }
    else if(delta < 0)
        gradient = -1;
    else 
        gradient = 0;
    // gradient = -delta;
    // gradient = 1;
    // gradient = delta;
    // gradient = delta * Neuron::transfer_function_derivative(output_value);
}

void Neuron::calc_hidden_gradients(Layer const& next_layer)
{
    double dow = sumDOW(next_layer);
    gradient = dow * Neuron::transfer_function_derivative(output_value);
}


void Neuron::update_input_weights(Layer & prev_layer)
{
    for(unsigned int i {}; i < prev_layer.size(); i++)
    {
        Neuron& neuron = prev_layer[i];
        double old_delta_weight { neuron.output_weights[my_index].delta_weight};

        double new_delta_weight { eta * neuron.get_output() * gradient + alpha * old_delta_weight};
        neuron.output_weights[my_index].delta_weight = new_delta_weight;
        neuron.output_weights[my_index].weight += new_delta_weight;
    }
}

double Neuron::sumDOW(Layer const& next_layer)const
{
    double sum {};

    // Sum our contributions of the errors at the nodes we feed
    for(unsigned int i {}; i < next_layer.size() - 1; ++i) 
    {
        sum += output_weights[i].weight * next_layer[i].gradient;
    }

    return sum;
}
double Neuron::transfer_function(double input)
{
    // RELU
    // return std::max(input, 0.0);
    // TANH
    return tanh(input);
}

double Neuron::transfer_function_derivative(double input)
{
    // RELU
    // double ret_val {};
    // if(input > 0)
        // ret_val = 1;
// 
    // return ret_val;

    // tanh() 
    return 1 - input * input;
}
