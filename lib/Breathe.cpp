#include "standardEffect.h"
#include "application.h"


class Breathe : public StandardEffect {
public:
  Breathe(int id, long startTime, int r, int g, int b, int p) : StandardEffect(id, startTime) {
    _r = r;
    _g = g;
    _b = b;
    _duration = 4000 - (p * 300);
  }

  bool cares(int x, int y) {
    return true;
  }

  uint32_t colorFor(int x, int y) {
    int relativeR = _r * _intensity;
    int relativeG = _g * _intensity;
    int relativeB = _b * _intensity;

    return _rgbToColor(relativeR, relativeG, relativeB);
  }

private:
  void _update() {
    int halfDuration = _duration / 2;
    int timePassed = (_currentTime - _startTime) % _duration;

    if (timePassed < halfDuration) {
      _intensity = _mapFloat(timePassed, 0, halfDuration, 0.1, 1.0);
    } else {
      _intensity = _mapFloat(timePassed, halfDuration, _duration, 1.0, 0.1);
    }
  }

  
  int _r;
  int _g;
  int _b;
  int _duration;
  float _intensity;
};

