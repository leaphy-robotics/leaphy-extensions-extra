#include "OLED_Display.h"
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     1 // Reset pin # (or -1 if sharing Arduino reset pin)

// Instantiate the display class
Adafruit_SSD1306 display_internal(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

OLEDDISPLAY::OLEDDISPLAY(){
}

bool OLEDDISPLAY::begin()
{
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display_internal.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3C for 128x32
	{ 
		return false;
	}
	
	display_internal.clearDisplay();
	display_internal.setTextSize(1);             // Normal 1:1 pixel scale
	display_internal.setTextColor(SSD1306_WHITE);        // Draw white text
	display_internal.setCursor(0,0);             // Start at top-left corner
	display_internal.println(F("Leaphy OLED"));
	display_internal.display();
	
	return true;
}

void OLEDDISPLAY::clearDisplay()
{
	display_internal.clearDisplay();
}

void OLEDDISPLAY::setTextSize(int size)
{
	display_internal.setTextSize(size);
}

void OLEDDISPLAY::setTextColor(uint16_t c)
{
	display_internal.setTextColor(c);
}

void OLEDDISPLAY::setCursor(int16_t x, int16_t y) 
{
    display_internal.setCursor(x, y);
}
  
void OLEDDISPLAY::display()
{
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

void OLEDDISPLAY::drawBitmap(int16_t x, xint16_t y, const uint8_t * bitmap, int16_t w, int16_t h, uint16_t color)
{
	display_internal.drawBitmap(x, y, bitmap, w, h, color);
}

void OLEDDISPLAY::drawPixel(int16_t x, int16_t y, uint16_t color)
{
	display_internal.drawPixel(x, y, color);
}

void OLEDDISPLAY::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
	display_internal.drawLine(x0, y0, x1, y1, color);
}

void OLEDDISPLAY::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
	display_internal.drawRect(x, y, w, h, color);
}

void OLEDDISPLAY::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	display_internal.drawCircle(x0, y0, r, color);
}

