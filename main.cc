
#include <iostream>
#include <iomanip> 
#include <stdexcept>
#include <limits>
#include <cctype>

#include "./system_functions.cc"
#include "./PID_controller.cc"
#include "./q_learning.cc"

using std::cin;
using std::cout;
using std::string;
using std::endl;

int main_menu();
bool another_go();

int main()
{
	while(1)
	{
		int choice = main_menu();

		if(choice == 1)
		{
			while(1) 
			{
				cout << "The pendulum balanced for: " << std::fixed << std::setprecision(2) << run_PID() << " seconds. " << endl;
				if(!another_go())
					break;
			}
		}
		else if(choice == 2)
		{
			cout << "Choose from which file you want to load Q-Table (leave empty if none)" << endl;
			string filename {};
			std::getline(cin, filename);
			//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//cout << "To enter/leave training mode press T" << endl; 
			while(1)
			{
				run_qlearning(filename);
				if(!another_go())
					break;	

			}	
		}
		else if(choice == 3)
		{
			cout << "Choose from which file you want to load Q-Table (leave empty if none)" << endl;
			string filename {};
			std::getline(cin, filename);
			//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			while(1)
			{
				run_qlearning(filename, false);
				if(!another_go())
					break;	

			}	
		}
		else if(choice == 0)
			break;		
	}
	return 0;
}

int main_menu()
{
	cout << "Make a choice: \n 1. PID Controller\n 2. Q-Learning training \n 3. Q-learning controller\n 0. Quit"<< endl;

	std::string input {};
	int choice {3};

	while (cin >> input)
	{
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		try
		{
			choice = stoi(input); 
			if(choice == 1 || choice == 2 || choice == 3 || choice == 0)
				return choice;			
		}
		catch(std::exception & e)
		{
			cout << "That was not a valid number! \n";
		}
		cout << "Try again: \n 1. PID Controller\n 2. Q-Learning training \n 3. Q-learning controller\n 0. Quit " << endl;
	}	
	return 3;
}

bool another_go()
{
	char a {};
	cout << "Another go? Y/N" << endl;
	cin >> a;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return std::tolower(a) == 'y';
}		
