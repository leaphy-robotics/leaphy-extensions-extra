#include "ledstrip.h"

LEDSTRIP::LEDSTRIP(uint8_t p, uint16_t tot){
  strip.begin();
  strip.setPin(p);
  strip.updateLength(tot);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

int _snelHeid = 50;
int _delayTime = 20;

void LEDSTRIP::runFunction(uint8_t f, uint8_t r, uint8_t g, uint8_t b){
  switch(f){
    case 0 :
      singleColor(r,g,b);
      break;
    case 1 :
      breathe(r,g,b);
      break;
    case 2 :
      marquee(_delayTime,r,g,b);
      break;
    case 3 :
      rainbow(r,g,b);
      break;
    case 4 :
      rainbowmarquee(r,g,b);
      break;
    default :
      marquee(_delayTime,r,g,b);
      break;

  }
}

void LEDSTRIP::singleColor(uint8_t r, uint8_t g, uint8_t b){
  strip.setBrightness(255);
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r,g,b));
  }
  strip.show();
}

void LEDSTRIP::breathe(uint8_t r, uint8_t g, uint8_t b){
  _delayTime = (101 -_snelHeid);
  //set to dark
  strip.setBrightness(1);
  strip.show();
  for(int i = 0; i < 255; i++){
    strip.setBrightness(i);
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r,g,b));
    }
    strip.show();
    delay(_delayTime/10);
  }
  delay(40);
  for(int i = 255; i >= 0; i--){
    strip.setBrightness(i);
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(r,g,b));
    }
    strip.show();
    delay(_delayTime/10);
  }
  delay(1);
}

void LEDSTRIP::marquee(int delayTime, uint8_t r, uint8_t g, uint8_t b){
  uint16_t scale;
  strip.setBrightness(255);
  _delayTime = (101 -_snelHeid);
  for(int i = 0; i < strip.numPixels()+4; i++){
   //light up 5 leds at a time with dim color
    for (int j = 0; j < 5; j++) {
      if (i-j >= 0 && i-j < strip.numPixels()) {
        scale = 255-80*j >= 0 ? 255-80*j : 0;
        uint8_t r1 = r * scale >>8;
        uint8_t g1 = g * scale >>8;
        uint8_t b1 = b * scale >>8;
        strip.setPixelColor(i-j, strip.Color(r1,g1,b1));
      }
    }
    strip.show();
    delay(_delayTime);
  }
  for(int i = strip.numPixels() - 1; i >= -4 ; i--){
    //light up 5 leds at a time with dim color
    for (int j = 0; j < 5; j++) {
      if (i+j >= 0 && i+j < strip.numPixels()) {
        scale = 255-80*j >= 0 ? 255-80*j : 0;
        uint8_t r1 = r * scale >>8;
        uint8_t g1 = g * scale >>8;
        uint8_t b1 = b * scale >>8;
        strip.setPixelColor(i+j, strip.Color(r1,g1,b1));
      }
    }
    strip.show();
    delay(_delayTime);
  }
}

void LEDSTRIP::rainbow(uint8_t r, uint8_t g, uint8_t b){
  uint16_t i, j;
  _delayTime = (101 -_snelHeid);
  strip.setBrightness(255);
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(_delayTime);
  }
}

void LEDSTRIP::rainbowmarquee(uint8_t r, uint8_t g, uint8_t b){
  int wait = 20;
  _delayTime = (101 -_snelHeid);
  strip.setBrightness(255);
   for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();

        delay(_delayTime*20);

        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}
uint32_t LEDSTRIP::Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void LEDSTRIP::basis(uint8_t led, uint8_t r, uint8_t g, uint8_t b){
  strip.setPixelColor(led, r, g, b );
  strip.show();
}
