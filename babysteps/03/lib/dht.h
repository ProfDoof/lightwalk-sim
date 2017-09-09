//
// Based on https://gist.github.com/wgbartley/8301123
// and https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.h
//
#ifndef DHT_H
#define DHT_H

#include "application.h"

#define DHT_TIMINGS 85
#define DHT_PIN A5
#define DHT_COUNT 6

class DHT {
public:
  DHT();

  void read();

  float temperature;
  float humidity;

private:
  uint8_t _data[6];
  unsigned long _lastReadTime = 0;
  bool _firstReading = true;
};

#endif
