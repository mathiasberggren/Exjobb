#include "timer.h"
#include <iostream>
#include <iomanip>

int main()
{
	Timer t1{};
	std::cout << "Time elapsed was: " << std::fixed << t1.elapsed() << std::endl;




	return 0;
}
