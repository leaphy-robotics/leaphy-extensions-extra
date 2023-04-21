#include "TimeofFlight.h"
#include "Adafruit_VL53L0X.h"

bool TimeOfFlight::begin()
{
    if (!sensor.begin()) {
        return false;
    }
    return true;
}

int TimeOfFlight::read()
{
    VL53L0X_RangingMeasurementData_t measure;
    sensor.rangingTest(&measure, false);
    if (measure.RangeStatus == 4) { 
        return -1;
    }
    return measure.RangeMilliMeter;
}

int TimeOfFlight::readCm()
{
    return this->read() / 10;
}

int TimeOfFlight::readMm()
{
    return this->read();
}