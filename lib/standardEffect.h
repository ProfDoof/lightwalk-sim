#ifndef StandardEffect_h
#define StandardEffect_h

#include "effect.h"

class StandardEffect : public Effect {
public:
  StandardEffect(int id, long startTime) : Effect(id, startTime) {}

  bool interactive() {
    return false;
  }

  // bnr
  virtual ~StandardEffect() {}

  void movementOn(long currentTime, int xOffset, int nodeId) {}
  void movementOff(int xOffset, int nodeId) {}
};

#endif
