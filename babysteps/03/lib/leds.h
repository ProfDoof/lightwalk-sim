#ifndef Leds_h
#define Leds_h

#include "application.h"
#include "constants.h"
#include "dotstar.h"

class Leds {
public:
  Leds() {};

  void initialize();
  void startupSequence();
  void setAll(uint32_t color);
  void setAll(int r, int g, int b);
  void setPixel(int x, int y, uint32_t color);
  void setPixel(int x, int y, int r, int g, int b);
  void show();
  void rgbwTest();

private:
  uint32_t colorFor(int r, int g, int b);

  Adafruit_DotStar* strips[REED_COUNT];
  int reedPins[REED_COUNT] = {
    D3, D4, D5, D6, D7, A0, A1, A2, A3, A4
  };
  int _clockPin = D0;
};

#endif
