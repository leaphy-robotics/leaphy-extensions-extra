#pragma once
//
//    FILE: SGP30.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
//    DATE: 2021-06-24
// PURPOSE: Arduino library for SGP30 environment sensor.
//     URL: https://github.com/RobTillaart/SGP30
//          https://www.adafruit.com/product/3709


#include "Arduino.h"
#include "Wire.h"

#define AirQuality_OK                        0x00
#define AirQuality_ERROR_CRC                 0xFF
#define AirQuality_ERROR_I2C                 0xFE


class AirQuality
{
public:
  explicit AirQuality(TwoWire *wire = &Wire);
  bool     begin();
  bool     isConnected();
  void     GenericReset();
  bool     getID();
  uint16_t getFeatureSet();
  bool     measureTest();
  uint32_t lastMeasurement() { return _lastTime; };
  bool     measure(bool all = false);
  void     request();
  bool     read();
  void     requestRaw();
  bool     readRaw();

  uint16_t getTVOC()        { return _tvoc; };     //   PPB
  uint16_t getCO2()         { return _co2; };      //   PPM
  uint16_t getH2_raw()      { return _h2; };       //   UNKNOWN
  uint16_t getEthanol_raw() { return _ethanol; };  //   UNKNOWN
  float    getH2();         //  experimental       //   PPM
  float    getEthanol();    //  experimental       //   PPM

  void      setSrefH2(uint16_t s = 13119)      { _srefH2 = s; };
  uint16_t  getSrefH2()                        { return _srefH2; };
  void      setSrefEthanol(uint16_t s = 18472) { _srefEth = s; };
  uint16_t  getSrefEthanol()                   { return _srefEth; };


  int      lastError();
  uint8_t  _id[6];


private:
  uint8_t  _address;
  int      _error;
  uint32_t _lastTime    = 0;
  uint32_t _lastRequest = 0;
  int      _command(uint16_t cmd);
  int      _command(uint16_t cmd, uint16_t v1);
  int      _command(uint16_t cmd, uint16_t v1, uint16_t v2);
  uint8_t  _CRC8(uint16_t val);
  void     _init();

  uint16_t _tvoc;
  uint16_t _co2;
  uint16_t _h2;
  uint16_t _ethanol;
  uint16_t _srefH2  = 13119;
  uint16_t _srefEth = 18472;

  TwoWire*  _wire;
};


//  -- END OF FILE --
