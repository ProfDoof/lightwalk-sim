#ifndef InteractiveEffect_h
#define InteractiveEffect_h

#include "effect.h"

struct Movement {
  long startTime = 0;
  int xOffset = 0;
  int nodeId = 0;
};

class InteractiveEffect : public Effect {
public:
  InteractiveEffect(int id, long startTime) : Effect(id, startTime) {}

  bool interactive() {
    return true;
  }

  void movementOn(long currentTime, int xOffset, int nodeId) {
    // Can't add more movements than there are nodes
    if (_activeMovements == NODE_COUNT) return;

    _movements[_activeMovements].startTime = currentTime;
    _movements[_activeMovements].xOffset   = xOffset;
    _movements[_activeMovements].nodeId    = nodeId;

    _activeMovements += 1;
    _movementOn(currentTime, xOffset, nodeId);
  }

  void movementOff(int xOffset, int nodeId) {
    for (int i = 0; i < _activeMovements; i++) {
      if (_movements[i].nodeId == nodeId) {
        for (int j = i; j < _activeMovements - 1; j++) {
          _movements[j].startTime = _movements[j + 1].startTime;
          _movements[j].xOffset   = _movements[j + 1].xOffset;
          _movements[j].nodeId    = _movements[j + 1].nodeId;
        }

        _activeMovements -= 1;
        _movementOff(xOffset, nodeId);

        return;
      }
    }
  }

private:
  virtual void _movementOn(long currentTime, int xOffset, int nodeId) = 0;
  virtual void _movementOff(int xOffset, int nodeId) = 0;

protected:
  Movement _movements[NODE_COUNT];
  int _activeMovements = 0;
};

#endif
