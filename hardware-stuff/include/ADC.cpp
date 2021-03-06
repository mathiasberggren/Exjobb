
#if 0
/*
Provided to you by Emlid Ltd (c) 2014.
twitter.com/emlidtech || www.emlid.com || info@emlid.com

Example: Control ADS1115 connected to PCA9685 driver onboard of Navio shield for Rapspberry Pi.

Connect a wire to P1 and the ADC will measure its voltage and display it.
Be careful, do not connect high-voltage circuits, for acceptable range check the datasheet for ADS1115.

To run this example navigate to the directory containing it and run following commands:
make
./ADC
*/

//#include <stdio.h>
//#include <unistd.h>
#include <iostream>
#include "./ADS1115.h"
//#include "Navio/Util.h"
#define ADDRESS 0x48
int get_angle(int const&);
//#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])
int main() {

    ADS1115 adc;

    //if (check_apm()) {
    //    return 1;
    //}

    adc.setMode(ADS1115_MODE_SINGLESHOT);
    adc.setRate(ADS1115_RATE_860); 

    //uint16_t muxes[] = {ADS1115_MUX_P0_NG}; //, ADS1115_MUX_P1_NG, ADS1115_MUX_P2_NG, ADS1115_MUX_P3_NG};
    //std::cout << ARRAY_SIZE(muxes) << std::endl;
    //float results[ARRAY_SIZE(muxes)] = {0.0f};
    int i = 0;
    
    
    while (true) {
        //adc.setMultiplexer(muxes[i]);

        int conversion = adc.getMilliVolts();
        //results[i] = conversion;

        //i = (i + 1) % ARRAY_SIZE(muxes);

      //  for (int j = 0; j < ARRAY_SIZE(muxes); j++) {
            std::cout << get_angle(conversion) << std::endl;      
         //       printf("A%d: %.4fV ", j, results[j] / 1000);
        //}
//        printf("\n");
    }

    return 0;
}

int get_angle(int const& a)
{
    return a / 100;

}

#endif
