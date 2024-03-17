#include "i2c.h"
#include "Wire.h"

i2c::i2c(/* args */)
{
    List<int> i2cChannelStack;
}

void i2c::i2cSelectChannel(uint8_t channel, bool push = true) {
    if (push) i2cChannelStack.addLast(channel);
    if (channel <= 7) channel = (1 << channel);
    Wire.beginTransmission(0x70);
    Wire.write(channel);
    Wire.endTransmission();
}

void i2c::i2cRestoreChannel() {
    i2cChannelStack.removeLast();
    uint8_t channel = i2cChannelStack.get(i2cChannelStack.getSize() - 1);
    i2cSelectChannel(channel, false);
}

uint8_t i2c::i2cGetChannel() {
    uint8_t channel = i2cChannelStack.get(i2cChannelStack.getSize() - 1);
    if (channel > 7) channel = 0;
    return channel;
}