#include "LSM303AGR.h"

#define _ADDRESS_MAG 0x1E   //!< Default address
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SPIDevice.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

CompassSensor::CompassSensor() {
  CompassSensor::mag = Adafruit_LIS2MDL();
  // initiate the event
  CompassSensor::mag.getEvent(&data);
}

bool CompassSensor::begin(uint8_t i2c_addr = _ADDRESS_MAG, TwoWire *wire = &Wire) {
    CompassSensor::mag.begin(i2c_addr = _ADDRESS_MAG, wire = &Wire);

    return true;
}

bool CompassSensor::begin_SPI(uint8_t cs_pin, SPIClass *theSPI = &SPI) {
    CompassSensor::mag.begin_SPI(cs_pin, theSPI);

    return true;
}

bool CompassSensor::begin_SPI(int8_t cs_pin, int8_t sck_pin, int8_t miso_pin, int8_t mosi_pin) {
    CompassSensor::mag.begin_SPI(cs_pin, sck_pin, miso_pin, mosi_pin);

    return true;
}

lis2mdl_rate_t CompassSensor::getDataRate() {
    return CompassSensor::mag.getDataRate();
}

void CompassSensor::setDataRate(lis2mdl_rate_t rate) {
    CompassSensor::mag.setDataRate(rate);
}

void CompassSensor::reset() {
    CompassSensor::mag.reset();
}

void CompassSensor::update() {
  CompassSensor::mag.getEvent(&data);
}
