#include "interactiveEffect.h"
#include "application.h"
//#include <iomanip>
// Brent Neal Reeves
// Fall 2017

//Name: Power
//Arguments:
//- Main Color
//  - Type: color
//- Velocity: 1 is slow, 9 is fast.
//  - Range: 1 - 9

// ====================================================================================
// Power
// ====================================================================================
class Power : public InteractiveEffect
{
public:
  Power(int id, long startTime, int r, int g, int b, int v) : InteractiveEffect(id, startTime)
  {
    _color = _rgbToColor(r, g, b);

    _FRACTION = 4;
    _DURATION = 3000 - (v * 300);

    _step = _DURATION / _FRACTION;
    _nth = _DURATION / _step;

    timePassed = 0;
    _offset = 0;
    _prevTime = -1;
    _focus = NODE_COUNT / 2;
    _delta = abs(_focus - id);
    _myPixels = 1;
    _midY = PIXEL_COUNT / 2;
    _adjustMe ( _focus );
  }

  bool cares(int x, int y)
  {
    // if ((x == 0) && (y == 0)) {
    //   cout << "cares " << _nodeId << "  delta: " << _delta << "  /7 " << (_delta % 7) << "  _offset: " << _offset << endl;
    // }
    // maxAt = (NODE_COUNT - _focus)
    int delta = abs( y - _midY );
    return (((_delta % _FRACTION) == _offset) &&
	    ( y > ( _midY - _myPixels)) &&
	    ( y < ( _midY + _myPixels)));
  }

  uint32_t colorFor(int x, int y)
  {
    return _color;
  }

private:
  void _update()
  {
    // cout.setf(ios::floatfield,ios::fixed);
    // cout << " _effectLength: " << _DURATION << "  1/7th: " << seventh << "  step: " << step << endl;
    int aTime = (_currentTime - _startTime);
    _offset = (int)(((_currentTime - _startTime) % _DURATION) / _step);
  }

  void _adjustMe (int target) {
    int midNode = NODE_COUNT / 2;
    _focus = target; // new center of attention
    _delta = abs(_focus - _nodeId); // how far away am I
    _myPixels = (_delta / ( 1.0 *  abs(midNode  - target) + midNode )) * _midY;
    //    cout << "_movementOn " << setw(2) << _nodeId << " at " << _currentTime  << " node: " << target <<  "  _delta: " << _delta << " myPlace: " <<  _myPixels << endl;
  }


  void _movementOn(long currentTime, int xOffset, int nodeId)
  {
    _adjustMe ( nodeId );
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

  int _colorOffset = 0;
  int _showing = false;

  int _DURATION = 1000;
  int _FRACTION = 7;
  int _step = 1;
  int _nth = 1;
  int timePassed = 0;
  int _offset = 0;
  int _delta = 1;
  int _prevTime = -1;
  int _myPixels=1;
  int _midY=0;
};
