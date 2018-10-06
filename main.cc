#include <iostream>
#include <iomanip> 
#include <stdexcept>
#include <limits>
#include <cctype>

#include "PID.cc"

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
				run_PID();
				if(!another_go())
					break;
			}
		}
		else if(choice == 2)
		{
			while(1)
			{
				cout << "Choose from which file you want to load Q-Table (leave empty if none)" << endl;
				string filename {};
				std::getline(cin, filename);
				//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "To enter/leave training mode press T" << endl; 
				//run_q_learning(filename);
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
	cout << "Make a choice: \n 1. PID Controller\n 2. Q-Learning \n 0. Quit"<< endl;

	std::string input {};
	int choice {3};

	while (cin >> input)
	{
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		try
		{
			choice = stoi(input); 
			if(choice == 1 || choice == 2 || choice == 0)
				return choice;			
		}
		catch(std::exception & e)
		{
			cout << "That was not a valid number! \n";
		}
		cout << "Try again: \n 1. PID Controller\n 2. Q-Learning \n 0. Quit " << endl;
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
