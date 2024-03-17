#include "OLED_Display.h"
#include "ledstrip.h"
#include "RedMP3.h"

LEDSTRIP ledstrip(1, 60);

#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_16X);
MP3 mp3(7, 8);
uint16_t RawColor_Red, RawColor_Green, RawColor_Blue, RawColor_Clear;
byte Color_Red, Color_Green, Color_Blue, Color_Clear;

double getColor(int colorCode, bool isRaw) {
  tcs.getRawData(&RawColor_Red, &RawColor_Green, &RawColor_Blue, &RawColor_Clear);
  Color_Red = min(RawColor_Red/5,255); Color_Green = min(RawColor_Green/5,255); Color_Blue = min(RawColor_Blue/5,255);
  switch(colorCode) {
    case 0:
      return (isRaw) ? RawColor_Red : Color_Red;
    case 1:
      return (isRaw) ? RawColor_Green : Color_Green;
    case 2:
      return (isRaw) ? RawColor_Blue : Color_Blue;
  }
}

OLEDDISPLAY display;
void leaphyProgram() {
  _snelHeid = 1;
  ledstrip.runFunction(4, getColor(0, true), getColor(1, true), getColor(2, true));
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Hallo");
  display.display();
  delay(500);
  mp3.playWithVolume(0x01, 0x1a);
}

void setup() {
  if (tcs.begin()) {
    Serial.println("RGB-sensor gevonden!");
  } else {
    Serial.println("Geen RGB-sensor gevonden... check je verbindingen...");
  }
  Serial.begin(115200);
  if(!display.begin())
  {
    Serial.println(F("Contact with the display failed: Check the connections"));
  }


  leaphyProgram();
}

void loop() {

}
