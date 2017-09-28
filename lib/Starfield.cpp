#include "standardEffect.h"
#include "application.h"

#define MAX_BLIPS 200

class Blip {
public:
  Blip() {}

  void restart(long startTime, int speed) {
    if (speed <= 0)
      speed = 1;

    _startTime = startTime;
    _duration  = random(500 / speed, 4000 / speed);
    _x         = random(0, REED_COUNT);
    _y         = random(0, PIXEL_COUNT);

  }

  void update(long currentTime) {
    _currentTime = currentTime;
  }

  bool isAt(int x, int y) {
    return x == _x && y == _y;
  }

  bool expired() {
    return (_currentTime > _startTime + _duration);
  }

  float intensity() {
    if (_currentTime < _startTime) return 0;

    int timePassed = _currentTime - _startTime;
    float percentagePassed = timePassed * 1.0 / _duration;

    if (percentagePassed < 0.2) {
      return _mapFloat(percentagePassed, 0, .2, 0, 1.0);
    } else if (percentagePassed < 0.8) {
      return 1.0;
    } else {
      return _mapFloat(percentagePassed, 0.8, 1.0, 1.0, 0);
    }
  }

private:
  float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }

  int _x, _y, _duration;
  long _startTime, _currentTime;
};

class Starfield : public StandardEffect {
public:
  Starfield(int id, long startTime, int r, int g, int b, int density, int speed) : StandardEffect(id, startTime) {
    _r = r;
    _g = g;
    _b = b;
    _speed = speed;
    _blipCount = min(10 * density, MAX_BLIPS);

    // bnr add (0 )
    for (int i = 0; i < _blipCount; i++) {
      _blips[i].restart(_currentTime + random(0, 1500), _speed);
    }
  }

  bool cares(int x, int y) {
    for (int i = 0; i < _blipCount; i++) {
      if (_blips[i].isAt(x, y)) {
        return true;
      }
    }

    return false;
  }

  uint32_t colorFor(int x, int y) {
    for (int i = 0; i < _blipCount; i++) {
      if (_blips[i].isAt(x, y)) {
        float intensity = _blips[i].intensity();
        return _rgbToColor(_r * intensity, _g * intensity, _b * intensity);
      }
    }

    return 0;
  }

private:
  void _update() {
    for (int i = 0; i < _blipCount; i++) {
      _blips[i].update(_currentTime);

      if (_blips[i].expired()) {
        _blips[i].restart(_currentTime, _speed);
      }
    }
  }

  int _r, _g, _b;
  int _speed;
  int _blipCount;
  Blip _blips[MAX_BLIPS];
};
