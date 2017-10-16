#include "standardEffect.h"
#include "application.h"
#include "gradient.h"

#define DURATION 4000
#define HALF_DURATION (DURATION / 2)

class WaveUpGradient : public StandardEffect {
public:
  WaveUpGradient(int id, long startTime, int r1, int g1, int b1, int r2, int g2, int b2, int v) : StandardEffect(id, startTime) {
    _gradient.configure(r1, g1, b1, r2, g2, b2);
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
    float localPercentage = y * 1.0 / PIXEL_COUNT;
    return _gradient.calculateColor(localPercentage);
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

  Gradient _gradient;
  int _velocity;
  bool _inFirstHalf;
  float _percentagePassed;
};
