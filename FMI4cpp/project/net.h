#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <vector>
#include <cstdlib>

using std::vector;

class Neuron;
typedef vector<Neuron> Layer;
typedef vector<std::pair<double, double>> Training_data;

class Net
{
	public:
		Net(vector<unsigned int> const& topology);
        void train_net(Training_data const&);
		void forward(double const&);
		void backpropagate(double const&);
        void set_weights(vector<double> const&);
        void get_weights(vector<double> &)const; 
		void get_results(vector<double> &)const;
	private:
		vector<Layer> layers;
		double error;
		double recent_average_error;
		double smoothing_factor;
};


class Neuron
{
    friend class Net;
	public: 
		Neuron(unsigned int outputs, unsigned int index);
		void   set_output(double val) { output_value = val; }
		double get_output() const { return output_value; }
		void   forward(Layer const& prev_layer);
		void   calc_output_gradients(double gold);	
		void   calc_hidden_gradients(Layer const& next_layer);
		void   update_input_weights(Layer & prev_layer);
	private:
		static double eta; 
		static double alpha;
		static double transfer_function(double);
		static double transfer_function_derivative(double);
		double sumDOW(Layer const& next_layer)const;
		struct Connection 
		{
			/* CHANGE: How random value on weights is generated, using C library atm */ 
			Connection() 
				: weight{rand() / double(RAND_MAX)}, delta_weight{} {}
			double weight;
			double delta_weight;
			/* CHANGE: Pointer to a Neuron which it gets values from so we can easier do forward */	
		};
		
		double output_value;
		vector<Connection> output_weights;
		unsigned int my_index;
		double gradient;
};



#endif
