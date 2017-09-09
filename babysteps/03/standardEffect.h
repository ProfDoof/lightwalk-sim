#ifndef StandardEffect_h
#define StandardEffect_h

#include "effects/effect.h"

class StandardEffect : public Effect {
public:
  StandardEffect(int id, long startTime) : Effect(id, startTime) {}

  bool interactive() {
    return false;
  }

  void movementOn(int xOffset, long currentTime) {}
  void movementOff(int xOffset) {}
};

#endif
