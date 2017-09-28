#include "standardEffect.h"
#include "application.h"

class RainbowDrop {
public:
  RainbowDrop() {}

  void configure(uint32_t c, int sp, int h, float v, long st) {
    color          = c;
    position       = sp;
    _height        = h;
    _startPosition = sp;
    _velocity      = v;
    _startTime     = st;
  }

  void update(long currentTime) {
    position = _startPosition - (currentTime - _startTime) * _velocity;
  }

  bool surrounds(int y) {
    return position >= y && (position - _height) < y;
  }

  uint32_t color;
  int position;

private:
  int _height;
  int _startPosition;
  float _velocity;
  long _startTime;
};

class RainbowRain : public StandardEffect {
public:
  RainbowRain(int id, long startTime) : StandardEffect(id, startTime) {
    identifier = id;
    for (int i = 0; i < REED_COUNT; i++) {
      _restartDrop(i);
    }
  }

  bool cares(int x, int y) {
    return _drops[x].surrounds(y);
  }

  uint32_t colorFor(int x, int y) {
    return _drops[x].color;
  }

private:
  void _update() {
    for (int i = 0; i < REED_COUNT; i++) {
      _drops[i].update(_currentTime);

      if (_drops[i].position < 0) {
        _restartDrop(i);
      }
    }
  }

  // bnr (0, 12)
  void _restartDrop(int index) {
    uint32_t color    = _possibleColors[ random(0, 12) ];
    int height        = random(3, 8);
    int startPosition = random(PIXEL_COUNT, PIXEL_COUNT * 2);
    float velocity    = random(30, 60) * 1.0 / 1000;

    _drops[index].configure(color, startPosition, height, velocity, _currentTime);
  }

  uint32_t _possibleColors[12] = {
    _rgbToColor(255, 0,   0),
    _rgbToColor(255, 120, 0),
    _rgbToColor(255, 255, 0),
    _rgbToColor(120, 255, 0),
    _rgbToColor(0,   255, 0),
    _rgbToColor(0,   255, 120),
    _rgbToColor(0,   255, 255),
    _rgbToColor(0,   120, 255),
    _rgbToColor(0,   0,   255),
    _rgbToColor(120, 0,   255),
    _rgbToColor(255, 0,   255),
    _rgbToColor(255, 0,   120)
  };

  RainbowDrop _drops[REED_COUNT];
};
