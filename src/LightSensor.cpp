#include "LightSensor.h"

LIGHTSENSOR::LIGHTSENSOR(int pin)
{
    this->pin = pin;
}

bool LIGHTSENSOR::begin()
{
    pinMode(A0, INPUT);
    return true;
}

int LIGHTSENSOR::read()
{
    return analogRead(A0);
}