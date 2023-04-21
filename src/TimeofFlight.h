#ifndef tof 
#define tof
#include "Adafruit_VL53L0X.h"

class TimeOfFlight
{
public:       
    private:
        Adafruit_VL53L0X sensor = Adafruit_VL53L0X();
        int read();
    public:
        bool begin();
        int readCm();
        int readMm();
};


#endif