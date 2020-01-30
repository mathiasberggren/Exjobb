#if 0

#include "timer.h"
#include <iostream>
#include <iomanip>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <wiringPiI2C.h>
#include "distance_sensor.h"
//#define DEVICE "ttyAMA0"

int get_angle(int const&);
int main()
{
    bool dist_sensor {true};


    std::cout << "Testing timer!" << std::endl;
    Timer t1{};
    std::cout << "Time elapsed was: " << std::fixed << t1.elapsed() << std::endl;

    wiringPiSetup();
    if (dist_sensor) 
    {
        std::cout << "Testing distance sensor!" << std::endl;
        Distance_sensor dist{};
        std::cout << "Distance is: " << std::fixed << dist.get_distance() 
                << std::endl;
    }


    int i2cfd {wiringPiI2CSetup(0x48)};
    if (i2cfd < 0) 
        std::cout << "Could not find I2C device. " << std::endl;
    
    std::cout << "The i2cfd: " << i2cfd << ". " << "Reading from I2C buffer: " << wiringPiI2CRead(i2cfd) << std::endl;

    /*char const *device = "/dev/ttyACM0";
    int fd_arduino = serialOpen(device, 115200);
    if (fd_arduino < 0)
        std::cout << "Failed to open connection between arduino and raspberry :(" << std::endl;
    else
    {
        serialFlush(fd_arduino);
        std::cout << "Successfully opened connection! There is " << serialDataAvail(fd_arduino) << " bits waiting to be read. " << std::endl;
    }
    std::cout << "Testing angle sensor / arduino communication!" << std::endl;
    std::cout << "Opening connection returns: " << fd_arduino << std::endl;
    
 //   delay(1000);
//    serialFlush(fd_arduino);
    while(1)
    {
        std::cout << "Number of characters available: " << serialDataAvail(fd_arduino) << std::endl; 
        Timer t2 {};
        std::cout << "Angle is: " << get_angle(fd_arduino) << " took " << t2.elapsed() << " seconds to retrieve." << std::endl;
    }
    serialClose(fd_arduino);
    */
    return 0;
}


/*
int get_angle(int const& fd)
{
    int angle {};
    std::string s{};
    while(1)
    {
        try
        {
//            std::cout << "Inside get_angle function, return from serialGetchar is: " 
//                    << serialGetchar(fd) << std::endl;
            char c {static_cast<char>(serialGetchar(fd))};
            
            while('\r' != c)
            {
                s += c;
                c = static_cast<char>(serialGetchar(fd));
            }
            //if (angle == -1)
            //    continue;
            angle = std::stoi(s);
            break;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return angle;
}*/

#endif
