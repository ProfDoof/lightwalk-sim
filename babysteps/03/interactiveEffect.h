#ifndef InteractiveEffect_h
#define InteractiveEffect_h

#include "effects/effect.h"

struct Movement {
  int xOffset = 0;
  long startTime = 0;
};

class InteractiveEffect : public Effect {
public:
  InteractiveEffect(int id, long startTime) : Effect(id, startTime) {}

  bool interactive() {
    return true;
  }

  void movementOn(int xOffset, long currentTime) {
    // Can't add more movements than there are nodes
    if (_activeMovements == NODE_COUNT) return;

    _movements[_activeMovements].xOffset   = xOffset;
    _movements[_activeMovements].startTime = currentTime;

    _activeMovements += 1;
    _movementUpdate();
  }

  void movementOff(int xOffset) {
    for (int i = 0; i < _activeMovements; i++) {
      if (_movements[i].xOffset == xOffset) {
        for (int j = i; j < _activeMovements - 1; j++) {
          _movements[j].xOffset = _movements[j + 1].xOffset;
          _movements[j].startTime = _movements[j + 1].startTime;
        }

        _activeMovements -= 1;
        _movementUpdate();

        return;
      }
    }
  }

private:
  virtual void _movementUpdate() = 0;

protected:
  Movement _movements[NODE_COUNT];
  int _activeMovements = 0;
};

#endif
