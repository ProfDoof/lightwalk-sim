#ifndef Effect_h
#define Effect_h

#include "constants.h"
#include "math.h"

class Effect {
public:
  Effect(int id, long startTime) {
    randomSeed(startTime);

    EEPROM.get(OFFSET_ADDRESS, _xOffset);

    identifier   = id;
    _startTime   = startTime;
    _currentTime = startTime;
  }

  void update(long currentTime) {
    _currentTime = currentTime;
    _update();
  }

  int identifier;

  virtual bool cares(int x, int y) = 0;
  virtual uint32_t colorFor(int x, int y) = 0;

  virtual bool interactive() = 0;
  virtual void movementOn(int xOffset, long currentTime) = 0;
  virtual void movementOff(int xOffset) = 0;

private:
  virtual void _update() = 0;

protected:
  float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  uint32_t _rgbToColor(int r, int g, int b) {
    return (r << 16) + (b << 8) + g;
  }

  uint16_t _xOffset;

  long _startTime;
  long _currentTime;
};

#endif
