#ifndef MAGNET_H
#define MAGNET_H

#include "Arduino.h"

class Magnet
{
  public:
    Magnet(int d0 = -1, int a0 = -1);
    bool readD();
    int readA();
  private:
    int d0;
    int a0;
};

#endif