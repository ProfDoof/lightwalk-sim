#include "standardEffect.h"

class WaveSide : public StandardEffect {
public:
  WaveSide(int id, long startTime, int r, int g, int b, int d, int velocity) : StandardEffect(id, startTime) {
    _duration   = 30000 - (200 * velocity);
    _color      = _rgbToColor(r, g, b);
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
    return _color;
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

  uint32_t _color;
  bool _movesRight;
  bool _inFirstHalf;
  int _duration;
  float _percentagePassed;
};
