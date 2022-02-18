#include "OLED_Display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display_internal(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OLEDDISPLAY::OLEDDISPLAY(){
    Serial.begin(9600);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display_internal.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display_internal.display();
}

void OLEDDISPLAY::print(const String &s)
{
  display_internal.print(s);
}   

void OLEDDISPLAY::print(const char str[])
{
  display_internal.print(str);
}

void OLEDDISPLAY::print(char c)
{
  display_internal.print(c);
}

void OLEDDISPLAY::print(unsigned char b, int base)
{
  display_internal.print(b, base);
}

void OLEDDISPLAY::print(int n, int base)
{
  display_internal.print(n, base);
}

void OLEDDISPLAY::print(unsigned int n, int base)
{
  display_internal.print(n, base);
}

void OLEDDISPLAY::print(long n, int base)
{
  display_internal.print(n, base);
}

void OLEDDISPLAY::print(unsigned long n, int base)
{
  display_internal.print(n, base);
}

void OLEDDISPLAY::print(double n, int digits)
{
  display_internal.print(n, digits);
}

void OLEDDISPLAY::println(void)
{
  display_internal.println();
}

void OLEDDISPLAY::println(const String &s)
{
  display_internal.println(s);
}

void OLEDDISPLAY::println(const char c[])
{
  display_internal.println(c);
}

void OLEDDISPLAY::println(char c)
{
  display_internal.println(c);
}

void OLEDDISPLAY::println(unsigned char b, int base)
{
  display_internal.println(b, base);
}

void OLEDDISPLAY::println(int num, int base)
{
  display_internal.println(num, base);
}

void OLEDDISPLAY::println(unsigned int num, int base)
{
  display_internal.println(num, base);
}

void OLEDDISPLAY::println(long num, int base)
{
  display_internal.println(num, base);
}

void OLEDDISPLAY::println(unsigned long num, int base)
{
  display_internal.println(num, base);
}

void OLEDDISPLAY::println(double num, int digits)
{
  display_internal.println(num, digits);
}
