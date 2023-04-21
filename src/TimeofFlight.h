#ifndef tof 
#define tof
#include "Adafruit_VL53L0X.h"

class TimeOfFlight
{
public:       
    private:
        int a0;
        int a1;
        Adafruit_VL53L0X sensor = Adafruit_VL53L0X();
        int read();
    public:
        TimeOfFlight(int a0, int a1);
        bool begin();
        int readCm();
        int readMm();
};


#endif