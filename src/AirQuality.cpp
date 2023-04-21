#include "AirQuality.h"

SGP30::SGP30(TwoWire *wire)
{
  _address  = 0x58;
  _wire     = wire;

  _tvoc     = 0;
  _co2      = 0;
  _h2       = 0;
  _ethanol  = 0;

  _lastTime = 0;
  _error    = SGP30_OK;
}


bool SGP30::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  _init();
  return true;
}


bool SGP30::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}

bool SGP30::measure(bool all) 
{
  if (millis() - _lastTime < 1000) return false;
  _lastTime = millis();

  request();
  delay(12);
  read();

  if (not all) return true;

  requestRaw();
  delay(25);
  readRaw();
  return true;
}


void SGP30::request()
{
  _lastRequest = millis();
  _command(0x2008);
}


bool SGP30::read()
{
  if (_lastRequest == 0) return false;
  if (millis() - _lastRequest < 13) return false;
  _lastRequest = 0;

  if (_wire->requestFrom(_address, (uint8_t)6) != 6)
  {
    _error = SGP30_ERROR_I2C;
    return false;
  }
  _co2  =  _wire->read() << 8;
  _co2  += _wire->read();
  uint8_t crc = _wire->read();
  if (_CRC8(_co2) != crc)
  {
    _error = SGP30_ERROR_CRC;
    return false;
  }
  _tvoc =  _wire->read() << 8;
  _tvoc += _wire->read();
  crc = _wire->read();
  if (_CRC8(_tvoc) != crc)
  {
    _error = SGP30_ERROR_CRC;
    return false;
  }
  _error = SGP30_OK;
  return true;
}


void SGP30::requestRaw()
{
  _lastRequest = millis();
  _command(0x2050);
}


bool SGP30::readRaw()
{
  if (_lastRequest == 0) return false;
  if (millis() - _lastRequest < 26) return false;
  _lastRequest = 0;

  if (_wire->requestFrom(_address, (uint8_t)6) != 6)
  {
    _error = SGP30_ERROR_I2C;
    return false;
  }
  _h2      =  _wire->read() << 8;
  _h2      += _wire->read();
  uint8_t crc = _wire->read();
  if (_CRC8(_h2) != crc)
  {
    _error = SGP30_ERROR_CRC;
    return false;
  }
  _ethanol =  _wire->read() << 8;
  _ethanol += _wire->read();
  crc = _wire->read();
  if (_CRC8(_ethanol) != crc)
  {
    _error = SGP30_ERROR_CRC;
    return false;
  }
  _error = SGP30_OK;
  return true;
}

float SGP30::getH2()
{
  float cref = 0.5;  //  ppm
  return cref * exp((_srefH2 - _h2) * 1.953125e-3);
}


float SGP30::getEthanol()
{
  float cref = 0.4;  //  ppm
  return cref * exp((_srefEth - _ethanol) * 1.953125e-3);
}

int SGP30::_command(uint16_t cmd)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd >> 8);
  _wire->write(cmd & 0xFF);
  _error = _wire->endTransmission();
  return _error;
}


int SGP30::_command(uint16_t cmd, uint16_t v1)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd >> 8);
  _wire->write(cmd & 0xFF);
  _wire->write(v1 >> 8);
  _wire->write(v1 & 0xFF);
  _wire->write(_CRC8(v1));
  _error = _wire->endTransmission();
  return _error;
}


int SGP30::_command(uint16_t cmd, uint16_t v1, uint16_t v2)
{
  _wire->beginTransmission(_address);
  _wire->write(cmd >> 8);
  _wire->write(cmd & 0xFF);
  _wire->write(v1 >> 8);
  _wire->write(v1 & 0xFF);
  _wire->write(_CRC8(v1));
  _wire->write(v2 >> 8);
  _wire->write(v2 & 0xFF);
  _wire->write(_CRC8(v2));
  _error = _wire->endTransmission();
  return _error;
}

uint8_t SGP30::_CRC8(uint16_t data)
{
  uint8_t val[2];
  val[0] = data >> 8;
  val[1] = data & 0xFF;

  uint8_t crc = 0xFF;          
  for(uint8_t i = 0; i < 2; i++)
  {
    crc ^= val[i];
    for (uint8_t b = 8; b > 0; b--)
    {
      if (crc & 0x80)
        crc = (crc << 1) ^ 0x31;
      else
        crc <<= 1;
    }
  }
  return crc;
};


void SGP30::_init()
{
  _command(0x2003);
};
