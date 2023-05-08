#include "LightSensor.h"
#include <Arduino.h>

LIGHTSENSOR::LIGHTSENSOR(int pin)
{
    this->pin = pin;
}

bool LIGHTSENSOR::begin()
{
    pinMode(pin, INPUT);
    return true;
}

int LIGHTSENSOR::read()
{
    return analogRead(pin);
}