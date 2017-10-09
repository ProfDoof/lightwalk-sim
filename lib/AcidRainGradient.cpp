#include "standardEffect.h"
#include "application.h"
#include "gradient.h"

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

class AcidRainGradient : public StandardEffect {
public:
  AcidRainGradient(int id, long startTime, int r1, int g1, int b1, int r2, int g2, int b2, int sp) : StandardEffect(id, startTime) {
    _gradient.configure(r1, g1, b1, r2, g2, b2);
    _speed = sp;

    for (int i = 0; i < REED_COUNT; i++) {
      _restartDrop(i);
    }
    
  }

  bool cares(int x, int y) {
    return _drops[x].surrounds(y);
  }

  uint32_t colorFor(int x, int y) {
    float localPercentage = y * 1.0 / PIXEL_COUNT;
    return _gradient.calculateColor(localPercentage);
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

  Gradient _gradient;
  int _speed;
  RainDrop _drops[REED_COUNT];
};
