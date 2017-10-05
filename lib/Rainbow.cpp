#include "interactiveEffect.h"
#include "application.h"

// ====================================================================================
// Magneto
// ====================================================================================
class Rainbow : public InteractiveEffect
{
public:
  Rainbow(int id, long startTime) : InteractiveEffect(id, startTime)
  {
    _color = _rgbToColor(0, 0, 0);
  }

  bool cares(int x, int y)
  {
      return (_showing);
  }

  uint32_t colorFor(int x, int y)
  {
    return _color;
  }

private:
  void _update()
  {
    // don't really care about time
  }


  void _movementOn(long currentTime, int xOffset, int nodeId)
  {
    _focus = nodeId; // new center of attention

    // cout << "_movementOn " << _nodeId << " at " << currentTime << " x: "
    //      << xOffset << " node: " << nodeId << endl;

    _direction = (nodeId < _nodeId) ? 1 : -1;
    int delta = abs(_focus - _nodeId);
    if ((delta <= _blankspace) || (delta > (_blankspace + 7))) {
      _showing = false;
      return;
    }

    _colorOffset = abs( delta - (_blankspace + 1)); // factor blankspace into colors 0-6

    // cout << "id " << setw(2) << _nodeId << "  delta: " << delta << "  direction: " << _direction 
    // << " colorOffset: " << _colorOffset << endl;

      _showing = true;
      _color = _rgbToColor((int)(colors[_colorOffset][0]), 
      (int)(colors[_colorOffset][1]), 
      (int)(colors[_colorOffset][2]));
  }

  void _movementOff(int xOffset, int nodeId)
  {
    // don't care.  only new movements matter.
  }
  // ROYGBIV ish
  int colors[7][3] = {
      {255, 0, 0},
      {192, 51, 0},
      {255, 255, 0},
      {0, 255, 0},
      {0, 0, 255},
      {75, 0, 130},
      {127, 0, 255}};

  uint32_t _color;
  int _focus = 0;

  int _blankspace = 2;
  int _colorOffset = 0;
  int _showing = false;
  int _direction = 1;
};
