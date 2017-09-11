#include "standardEffect.h"

#define DURATION 4000
#define HALF_DURATION (DURATION / 2)

class WaveUp : public StandardEffect {
public:
  WaveUp(int id, long startTime, int r, int g, int b, int v) : StandardEffect(id, startTime) {
    _color = _rgbToColor(r, g, b);
    _velocity = v;
  }

  bool cares(int x, int y) {
    float localPercentage = y * 1.0 / PIXEL_COUNT;

    if (_inFirstHalf) {
      return localPercentage < _percentagePassed;
    } else {
      return localPercentage > _percentagePassed;
    }
  }

  uint32_t colorFor(int x, int y) {
    return _color;
  }

private:
  void _update() {
    int timePassed = (_currentTime - _startTime) % DURATION;

    if (timePassed < HALF_DURATION) {
      _inFirstHalf = true;
      _percentagePassed = _mapFloat(timePassed, 0, HALF_DURATION, 0, 1.0);
    } else {
      _inFirstHalf = false;
      _percentagePassed = _mapFloat(timePassed, HALF_DURATION, DURATION, 0, 1.0);
    }
  }

  uint32_t _color;
  int _velocity;
  bool _inFirstHalf;
  float _percentagePassed;
};
