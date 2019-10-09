#include <iostream>
#include <cmath>
#include <algorithm>

#include "net.h"

using std::cout;
using std::endl;

double Neuron::eta   = 0.15; // Learning rate
double Neuron::alpha = 0.5;  // Momentum, multiplier of last delta weight

Net::Net(vector<unsigned int> const& topology)
    :layers{}
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

void Net::train_net(Training_data const& training_data)
{
    for(auto training_sample : training_data)
    {
        forward(training_sample.first);
        backpropagate(training_sample.second); 
    }

}

void Net::backpropagate(double const& gold)
{
    Layer& output_layer { layers.back() };

    error = 0.0;

    /* Get the sum of all output neurons */ 	
    output_layer[0].get_output();	
    double delta { gold - output_layer[0].get_output() };
    error += delta * delta;

    error /= output_layer.size() - 1; // Average squared error
    error = sqrt(error); // RMS (Root Mean Square)

    recent_average_error = (recent_average_error * smoothing_factor + error) / smoothing_factor + 1.0;

    // Calculate gradients for output neurons
    output_layer[0].calc_output_gradients(gold);

    // Calculate gradients on hidden layers	
    for(long unsigned int layer_index {layers.size() - 2}; layer_index > 0; layer_index--)
    {
        Layer& hidden_layer { layers[layer_index] }; 	
        Layer& next_layer   { layers[layer_index + 1] };

        for(unsigned int i {}; i < hidden_layer.size(); i++)
        {
            hidden_layer[i].calc_hidden_gradients(next_layer);
        } 
    }

    for(long unsigned int layer_index {layers.size() - 1}; layer_index > 0; layer_index--)
    {
        Layer& layer { layers[layer_index] };
        Layer& previous_layer { layers[layer_index - 1] };

        for(unsigned int i {}; i < layer.size() - 1; i++)
        {
            layer[i].update_input_weights(previous_layer);
        }	
    } 
}

void Net::forward(double const& input)
{
    // Assign the input values into the input neurons (layer 0)	
    /* CHANGE: loop over layers[0] iterators to increase performance */ 
    // for(unsigned int i {}; i < input.size(); i++)
    // {
    // }	
    layers[0][0].set_output(input);

    // Forward through all layers
    for(unsigned int layer_index {1}; layer_index < layers.size(); layer_index++) 
    {
        Layer& prev_layer { layers[layer_index-1] }; 
        /* Call forward on each individual neuron */
        for(unsigned int i {}; i < layers[layer_index].size() - 1; i++)
            layers[layer_index][i].forward(prev_layer);
    }
}

void Net::get_results(vector<double> & result)const
{
    result.clear();

    for(unsigned int i {}; i < layers.back().size() - 1; i++)
    {
        result.push_back(layers.back()[i].get_output());
    }

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
    std::reverse(w.begin(), w.end());
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
    : output_weights{}, my_index {index} 
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

    /* CHANGE: Make it possible to change transfer function depending on function call */
    output_value = Neuron::transfer_function(sum);
}

void Neuron::calc_output_gradients(double gold)
{
    double delta = gold - output_value;
    gradient = delta * Neuron::transfer_function_derivative(output_value);
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
    return std::max(input, 0.0);
    // TANH
    // return tanh(input);
}

double Neuron::transfer_function_derivative(double input)
{
    // RELU
    double ret_val {};
    if(input > 0)
        ret_val = 1;

    return ret_val;

    // tanh() 
    // return 1 - input * input;
}
