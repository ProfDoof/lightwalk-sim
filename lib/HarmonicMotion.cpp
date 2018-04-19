#include "standardEffect.h"
#include "application.h"
#include <math.h>


class HarmonicBlip{
  public:
    HarmonicBlip() {}

    void configure(int index, bool flag){
      currentY = PIXEL_COUNT;
      velocity = 1 - (index * .025);
      isFill = flag;
    }

    void update(){
      float localPercent = cos(cosineVal);
      currentY = int(_mapFloat(localPercent, -1, 1, PIXEL_COUNT, 0));
      cosineVal += (velocity/200);
    }

    int getCurrentYBlip() {
      return currentY;
    }

    bool surrounds(int y) {
      if (isFill) {
        if (y <= getCurrentYBlip())
          return true;
      }
      else {
        if (y == getCurrentYBlip())
          return true;
      }
      return false;
    }

    float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

  private:
    float velocity;
    int currentY;
    float cosineVal = 0;
    bool isFill;
};

class HarmonicMotion : public StandardEffect {
public:
  HarmonicMotion(int id, long startTime, int r, int g, int b) : StandardEffect(id, startTime) {
    _color = _rgbToColor(r, g, b);
    bool flag = false;
    for (int i = 0; i < REED_COUNT; i++) {
      _blips[i].configure(i, flag);
    }
  }

  bool cares(int x, int y) {
    if (_blips[x].surrounds(y) )
      return true;
    return false;
  }

  uint32_t colorFor(int x, int y) {
    return _color;
  }

private:
  void _update() {
    for (int i = 0; i < REED_COUNT; i++) {
      _blips[i].update();
    }
  }

  uint32_t _color;
  int _velocity;
  HarmonicBlip _blips[REED_COUNT];
};
