#include "interactiveEffect.h"
#include "application.h"

#define DURATION 4000
#define HALF_DURATION (DURATION / 2)

#define MAX_BUBBLE_RADIUS (PIXEL_COUNT / 2)
#define BUBBLE_HEIGHT     (PIXEL_COUNT / 2)

class Bubble {
public:
  Bubble(long st, int xo) {
    startTime = st;
    xOffset = xo;
  }

  void update(long currentTime) {
    float percentagePassed;

    int timePassed = (currentTime - startTime) % DURATION;

    if (timePassed < HALF_DURATION) {
      percentagePassed = _mapFloat(timePassed, 0, HALF_DURATION, 0.2, 1.0);
    } else {
      percentagePassed = _mapFloat(timePassed, HALF_DURATION, DURATION, 1.0, 0.2);
    }

    _radius = percentagePassed * MAX_BUBBLE_RADIUS;
  }

  bool surrounds(int x, int y) {
    float distance = _distanceBetween(x, y, xOffset, BUBBLE_HEIGHT);

    return _radius >= distance;
  }

  long startTime;
  int xOffset;
private:
  float _radius;

  float _distanceBetween(int x1, int y1, int x2, int y2) {
    int aSquaredPlusBSquared = pow(x2 - x1, 2) + pow(y2 - y1, 2);

    return pow(aSquaredPlusBSquared, 0.5);
  }

  float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
};

class Bubbles : public InteractiveEffect {
public:
  Bubbles(int id, long startTime, int r, int g, int b) : InteractiveEffect(id, startTime) {
    _color = _rgbToColor(r, g, b);
  }

  bool cares(int x, int y) {
    for (int i = 0; i < _activeMovements; i++) {
      if (_bubbles[i]->surrounds(_xOffset + x, y)) {
        return true;
      }
    }

    return false;
  }

  uint32_t colorFor(int x, int y) {
    return _color;
  }

private:
  void _update() {
    for (int i = 0; i < _activeMovements; i++) {
      _bubbles[i]->update(_currentTime);
    }
  }

  void _movementOn(long currentTime, int xOffset, int nodeId) {
    // cout << "_movementOn " << identifier << " at " << currentTime << " x: " << xOffset << " node: " << nodeId << endl;
    _bubbles[_activeBubbles++] = new Bubble(currentTime, xOffset);
  }

  void _movementOff(int xOffset, int nodeId) {
    for (int i = 0; i < _activeBubbles; i++) {
      if (_bubbles[i]->xOffset == xOffset) {
        delete _bubbles[i];

        for (int j = i; j < _activeBubbles - 1; j++) {
          _bubbles[j] = _bubbles[j + 1];
        }

        _activeBubbles -= 1;

        return;
      }
    }
  }

  uint32_t _color;
  Bubble * _bubbles[NODE_COUNT];
  int _activeBubbles = 0;
};

