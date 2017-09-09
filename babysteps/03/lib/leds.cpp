#include "leds.h"

void Leds::initialize() {
  for (int i = 0; i < REED_COUNT; i++) {
    strips[i] = new Adafruit_DotStar(PIXEL_COUNT, reedPins[i], _clockPin);

    strips[i]->begin();
    strips[i]->setBrightness(BRIGHTNESS);
  }

  for (int i = 0; i < 100; i++) {
    int value = 255 * (i * 1.0 / 100);

    setAll(value, value, value);
    show();
    delay(5);
  }

  for (int i = 100; i > 0; i--) {
    int value = 255 * (i * 1.0 / 100);

    setAll(value, value, value);
    show();
    delay(5);
  }

  setAll(0);
  show();
}

void Leds::startupSequence() {
  // purple
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(74, 20, 140));
      strips[i]->show();
    }
    delay(30);
  }

  // white
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(125, 125, 125));
      strips[i]->show();
    }
    delay(30);
  }

  // purple
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(74, 20, 140));
      strips[i]->show();
    }
    delay(30);
  }

  // fade out
  for (int i = 0; i < 100; i++) {
    float percentage = 1.0 * (100 - i) / 100;
    setAll(74 * percentage, 20 * percentage, 140 * percentage);
    show();
    delay(5);
  }

  setAll(0);
  show();
}

void Leds::setAll(uint32_t color) {
  for (int i = 0; i < REED_COUNT; i++) {
    for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
      strips[i]->setPixelColor(j, color);
    }
  }
}

void Leds::setAll(int r, int g, int b) {
  setAll(colorFor(r, g, b));
}

void Leds::setPixel(int x, int y, uint32_t color) {
  strips[x]->setPixelColor(y, color);
}

void Leds::setPixel(int x, int y, int r, int g, int b) {
  setPixel(x, y, colorFor(r, g, b));
}

void Leds::show() {
  for (int i = 0; i < REED_COUNT; i++) {
    strips[i]->show();
  }
}

uint32_t Leds::colorFor(int r, int g, int b) {
  return (r << 16) + (b << 8) + g;
}

void Leds::rgbwTest() {
  // red
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(255, 0, 0));
      strips[i]->show();
    }
    delay(30);
  }

  // green
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(0, 255, 0));
      strips[i]->show();
    }
    delay(30);
  }

  // blue
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(0, 0, 255));
      strips[i]->show();
    }
    delay(30);
  }

  // white
  for(uint16_t j = 0; j < PIXEL_COUNT; j++) {
    for (int i = 0; i < REED_COUNT; i++) {
      strips[i]->setPixelColor(j, colorFor(255, 255, 255));
      strips[i]->show();
    }
    delay(30);
  }
}
