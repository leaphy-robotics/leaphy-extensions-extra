#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

class LIGHTSENSOR
{
public:       
    private:
        int pin;
    public:
        LIGHTSENSOR(int pin);
        bool begin();
        int read();
};


#endif