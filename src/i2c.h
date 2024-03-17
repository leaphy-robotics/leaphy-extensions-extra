#ifndef LEAPHY_I2C_H
#define LEAPHY_I2C_H

#include <Wire.h>
#include <List.hpp>


class i2c
{
private:
    List<int> i2cChannelStack;
public:
    i2c();
    void i2cSelectChannel(uint8_t channel, bool push = true);
    void i2cRestoreChannel();
    uint8_t i2cGetChannel();
};

#endif