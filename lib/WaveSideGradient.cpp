#include "standardEffect.h"
#include "application.h"
#include "gradient.h"

class WaveSideGradient : public StandardEffect {
public:
  WaveSideGradient(int id, long startTime, int r1, int g1, int b1, int r2, int g2, int b2, int d, int velocity) : StandardEffect(id, startTime) {
    _duration   = 30000 - (200 * velocity);
    _gradient.configure(r1, g1, b1, r2, g2, b2);
    _movesRight = d == 0;
  }

  bool cares(int x, int y) {
    int relativeX = _movesRight ? _xOffset + x : MAX_WIDTH - (_xOffset + x);
    float localPercentage = relativeX * 1.0 / MAX_WIDTH;

    if (_inFirstHalf) {
      return localPercentage < _percentagePassed;
    } else {
      return localPercentage > _percentagePassed;
    }
  }

  uint32_t colorFor(int x, int y) {
    float localPercentage = (x + _xOffset) * 1.0 / (NODE_COUNT * REED_COUNT);
    return _gradient.calculateColor(localPercentage);
  }

private:
  void _update() {
    int halfDuration = _duration / 2;
    int timePassed = (_currentTime - _startTime) % _duration;

    if (timePassed < halfDuration) {
      _inFirstHalf = true;
      _percentagePassed = _mapFloat(timePassed, 0, halfDuration, 0, 1.0);
    } else {
      _inFirstHalf = false;
      _percentagePassed = _mapFloat(timePassed, halfDuration, _duration, 0, 1.0);
    }
  }

  Gradient _gradient;
  bool _movesRight;
  bool _inFirstHalf;
  int _duration;
  float _percentagePassed;
};
