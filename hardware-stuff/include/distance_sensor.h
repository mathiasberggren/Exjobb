#ifndef DISTANCE_SENSOR_H
#define DISTANCE_SENSOR_H


class Distance_sensor
{

    public:
        Distance_sensor(int trig_pin = 27, int echo_pin = 26, double trigger_delay = 1) 
            : trigger_delay {trigger_delay}, trig_pin{trig_pin}, echo_pin{echo_pin}
        {       
            pinMode(trig_pin, OUTPUT);
            pinMode(echo_pin, INPUT);
            digitalWrite(trig_pin, 0);
        }
        double get_distance()const;
        
    private:
        //void trigger_sensor()const;
        double trigger_delay; // in ms
        int trig_pin;
        int echo_pin;
};

#endif
