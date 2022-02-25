#ifndef __oleddisplay__
#define __oleddisplay__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLEDDISPLAY 
{
    public:
    OLEDDISPLAY();
	bool begin();
	void clearDisplay();
	void setTextSize(int size);
	void setTextColor(uint16_t c);
	void setCursor(int16_t x, int16_t y);
	void display();
	
    void print(const String &);
    void print(const char[]);
    void print(char);
    void print(unsigned char, int = DEC);
    void print(int, int = DEC);
    void print(unsigned int, int = DEC);
    void print(long, int = DEC);
    void print(unsigned long, int = DEC);
    void print(double, int = 2);
 
    void println(const String &s);
    void println(const char[]);
    void println(char);
    void println(unsigned char, int = DEC);
    void println(int, int = DEC);
    void println(unsigned int, int = DEC);
    void println(long, int = DEC);
    void println(unsigned long, int = DEC);
    void println(double, int = 2);
    void println(void);
};

#endif
