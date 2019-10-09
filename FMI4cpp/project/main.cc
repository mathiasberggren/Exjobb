#include "net.h"


int main(int argv, char* argc [])
{
	
	vector<unsigned int> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);	
	Net myNet {topology};
	
	vector<double> inputVals {1, 2, 3};
	myNet.forward(inputVals);
	
	vector<double> targetVals;
	myNet.backpropagate(targetVals);
	
	vector<double> resultVals;
	myNet.get_results(resultVals);	

	return 0;
}
