#ifndef __ledstrip__
#define __ledstrip__

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"

extern int _snelHeid;
extern int _delayTime;

class LEDSTRIP
{
	public:
    LEDSTRIP(uint8_t, uint16_t);
    void runFunction(uint8_t, uint8_t, uint8_t, uint8_t);
		void singleColor(uint8_t, uint8_t, uint8_t);
		void breathe(uint8_t, uint8_t, uint8_t);
		void marquee(int delayTime, uint8_t, uint8_t, uint8_t);
		void rainbow(uint8_t, uint8_t, uint8_t);
		void rainbowmarquee(uint8_t, uint8_t, uint8_t);
				void basis(uint8_t,uint8_t, uint8_t, uint8_t);
	private:
    uint32_t Wheel(byte);
    uint8_t pin;
    uint16_t total_leds;
		uint32_t color;
    // set strip to 60 leds , at pin 8
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 8, NEO_GRB + NEO_KHZ800);

};

#endif
