#include <chrono>

class Timer
{
	public:
		Timer() : starting_time(clock::now()) {}
		void reset() { starting_time = clock::now(); }
		double elapsed() const { 
			return std::chrono::duration_cast<second>(clock::now() - starting_time).count(); 
		}
		
	private:
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::duration<double, std::ratio<1> > second;
		std::chrono::time_point<clock> starting_time;
};
