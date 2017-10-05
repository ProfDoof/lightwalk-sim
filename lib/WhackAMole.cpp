#include "interactiveEffect.h"
#include "application.h"

class WhackAMole : public InteractiveEffect {
public:
  WhackAMole(int id, long startTime, int r, int g, int b, int difficulty) : InteractiveEffect(id, startTime) {
    _color = _rgbToColor(r, g, b);
    _difficulty = difficulty;

    _resetMole();
  }

  bool cares(int x, int y) {
    if (_moleOn) {
      int timePassed = _currentTime - _moleStart;
      int risingBar = _mapFloat(timePassed, 0, 4000, 0, PIXEL_COUNT);
      risingBar = min(risingBar, PIXEL_COUNT);

      return _belowBar(x, y, risingBar);

    } else if (_moleHit > 0) {
      int moleTime = _moleHit - _lastMoleStart;
      int topReached = _mapFloat(moleTime, 0, 4000, 0, PIXEL_COUNT);

      int timePassed = _currentTime - _moleHit;
      int fallingBar = _mapFloat(timePassed, 0, 500.0 * topReached / PIXEL_COUNT, topReached, 0);
      fallingBar = min(fallingBar, PIXEL_COUNT);
      fallingBar = max(fallingBar, 0);

      return _belowBar(x, y, fallingBar);

    } else {
      return false;
    }
  }

  uint32_t colorFor(int x, int y) {
    return _color;
  }

private:
  void _update() {
    if (!_moleOn && _currentTime > _moleStart) {
      _moleOn = true;
    }

    if (_moleOn && _detectingMovement) {
      _moleOn = false;
      _moleHit = _currentTime;
      _lastMoleStart = _moleStart;
      _resetMole();
    }
  }

  void _resetMole() {
    int multiplier = _mapFloat(_difficulty, 1, 10, 2000, 300);
    _moleStart = _currentTime + 1000 + random(NODE_COUNT * multiplier);
  }

  bool _belowBar(int x, int y, int bar) {
    if (x < 3)
      // left shoulder
      return y < bar - 4;
    else if (x < 7)
      // head
      return y < bar;
    else {
      // right shoulder
      return y < bar - 4;
    }
  }

  void _movementOn(long currentTime, int xOffset, int nodeId) {
    if (nodeId == _nodeId) {
      _detectingMovement = true;
    }
  }

  void _movementOff(int xOffset, int nodeId) {
    if (nodeId == _nodeId) {
      _detectingMovement = false;
    }
  }

  uint32_t _color;
  int _difficulty;

  long _moleStart     = 0;
  long _lastMoleStart = 0;
  long _moleHit       = 0;

  bool _moleOn = false;
  bool _detectingMovement = false;
};
