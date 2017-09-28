#include "standardEffect.h"
#include "application.h"

/*
Name: Acid Rain
Arguments:
- Color
  - Type: color
- Velocity: 1 is slow, 10 is fast.
  - Range: 1 - 10
*/

class RainDrop {
public:
  RainDrop() {}

  void configure(int sp, int h, float v, long st) {
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

  int position;

private:
  int _height;
  int _startPosition;
  float _velocity;
  long _startTime;
};

class AcidRain : public StandardEffect {
public:
  AcidRain(int id, long startTime, int r, int g, int b, int sp) : StandardEffect(id, startTime) {
    _color = _rgbToColor(r, g, b);
    _speed = sp;

    for (int i = 0; i < REED_COUNT; i++) {
      _restartDrop(i);
    }
    
  }

  bool cares(int x, int y) {
    return _drops[x].surrounds(y);
  }

  uint32_t colorFor(int x, int y) {
    return _color;
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

  void _restartDrop(int index) {
    int startPosition = random(PIXEL_COUNT, PIXEL_COUNT * 2);
    int height        = random(3, 8);
    float velocity    = random(30, _speed * 10) * 1.0 / 1000;
    // float velocity    = 5 * 1.0 / 1000;

    _drops[index].configure(startPosition, height, velocity, _currentTime);
  }

  uint32_t _color;
  int _speed;
  RainDrop _drops[REED_COUNT];
};
