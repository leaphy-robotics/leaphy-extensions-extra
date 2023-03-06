#ifndef LSM303AGR_H
#define LSM303AGR_H
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LIS2MDL.h>

class CompassSensor {
    private:
        Adafruit_LIS2MDL mag;
        
        
    public:
        sensors_event_t * data;
        CompassSensor();
        bool begin(uint8_t i2c_addr = _ADDRESS_MAG, TwoWire *wire = &Wire);
        bool begin_SPI(uint8_t cs_pin, SPIClass *theSPI = &SPI);
        bool begin_SPI(int8_t cs_pin, int8_t sck_pin, int8_t miso_pin,
                    int8_t mosi_pin);

        lis2mdl_rate_t getDataRate();
        void setDataRate(lis2mdl_rate_t rate);
        void reset();
};

#endif
