// Shimmer.cpp
// An effect for ACU's Lightwalk
// Created by Cole Spears (cxs13b)

#include "standardEffect.h"
#include "application.h"

#define DURATION 4000

class Shimmer : public StandardEffect {
public:
  Shimmer(int id, long startTime, int r, int g, int b) : StandardEffect(id, startTime) {
    _color = _rgbToColor(r, g, b);
    count = 0;
    _updateRodsOn();  // init array
  }

  bool cares(int x, int y) {
    if (!_rodsOn[x])
      return true;
    return false;
  }

  uint32_t colorFor(int x, int y) {
    return _color;
  }

private:
  void _update() {
    if (count++ % 25 == 0){
      _updateRodsOn();
    }
  }

  void _updateRodsOn(){
    for (int i = 0; i < REED_COUNT; i++){
      _rodsOn[i] = random(0,7);
    }
  }

  uint32_t _color;
  int count;
  int _rodsOn[REED_COUNT];
};