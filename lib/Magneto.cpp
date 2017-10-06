#include "interactiveEffect.h"
#include "application.h"
#include <ctime>
#include <chrono>

/*
keep track of new movementOn to know whether I am now the boss and shouldn't draw an arrow
*/
class Arrow
{
public:
  Arrow(long st, int dir, int id, int masterOfAll, int duration)
  {
    startTime = st;
    direction = dir;
    identifier = id;
    target = masterOfAll;
    _duration = duration;
  }

  void update(long currentTime)
  {
    float percentagePassed;
    // cout << " Arrow update " << currentTime << "  start " << startTime << " _duration " << _duration;

    int timePassed = (currentTime - startTime) % _duration;
    _midNow = _mapFloat(timePassed, 0, _duration, 0.0, 11.0);

    // cout << "   mid " << _midNow << endl;
  }

    void setTarget( int nodeId) {
      target = nodeId;
      if (identifier == nodeId)
        direction = 0;
        else {
          direction = (nodeId > identifier) ? 1 : -1;
        }

    }


  bool onLine(int x, int y, float near)
  {
    // if (identifier == 2)
    //   cout << "onLine " << x << "," << y << " mid " << _midNow << " dir " << direction << " ";
    // -1 left, 0, +1 right
    // how about thicker when nearer?
    //
    // cout << "onLine x " << x << " y " << y << "  near " << near << endl;
    const int arrowHeight = 10;
    const int arrowWidth = 8;

    if (direction < 0)
    {
      int x1 = 10 - _midNow;
      int x2 = x1 + arrowWidth;
      return (
          (_lineDistance(x1, arrowHeight, x2, arrowHeight * 2, x, y) < near) ||
          (_lineDistance(x1, arrowHeight, x2, 0,               x, y) < near));
    }
    else
    {
      int x1 = _midNow - arrowWidth;
      int x2 = x1 + arrowWidth;
      return (
          (_lineDistance(x1, 0,               x2, arrowHeight, x, y) < near) ||
          (_lineDistance(x1, arrowHeight * 2, x2, arrowHeight, x, y) < near));
    }
  }

  long startTime;
  int direction = 0;
  int identifier = 0; // not to be confused with the Node's id
  int target = 0;

private:
  int _midNow = 0;
  int _duration = 4000;

  float _lineDistance(float x1, float y1, float x2, float y2, float pointX, float pointY)
  {
    float diffX = x2 - x1;
    float diffY = y2 - y1;
    if ((diffX == 0) && (diffY == 0))
    {
      diffX = pointX - x1;
      diffY = pointY - y1;
      return sqrt(diffX * diffX + diffY * diffY);
    }

    float t = ((pointX - x1) * diffX + (pointY - y1) * diffY) / (diffX * diffX + diffY * diffY);

    if (t < 0)
    {
      //point is nearest to the first point i.e x1 and y1
      diffX = pointX - x1;
      diffY = pointY - y1;
    }
    else if (t > 1)
    {
      //point is nearest to the end point i.e x2 and y2
      diffX = pointX - x2;
      diffY = pointY - y2;
    }
    else
    {
      //if perpendicular line intersect the line segment.
      diffX = pointX - (x1 + t * diffX);
      diffY = pointY - (y1 + t * diffY);
    }
    return sqrt(diffX * diffX + diffY * diffY);
  }

  float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
  {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
};

// ====================================================================================
// Magneto
// ====================================================================================
class Magneto : public InteractiveEffect
{
public:
  Magneto(int id, long startTime, int r, int g, int b, int v) : InteractiveEffect(id, startTime)
  {
    _color = _rgbToColor(r, g, b);
    _r = r;
    _g = g;
    _b = b;
    _activeArrows = 0;
    _duration = 4000 - (v * 300);
  }

  ~Magneto () {
    for (int i = 0; i < _activeArrows; i++) {
      delete _arrows[i];
    }
  } 

  bool cares(int x, int y)
  {
    // if (_nodeId == 2)
    //   if (_activeMovements > 0)
    //     cout << "cares id: " << _nodeId << " x " << x << " y " << y
    //          << "  movements " << _activeMovements << endl;

    // focus is just blank
    if (_nodeId == _focus)
      return (( y < 24) && ( (rand() % 10) > 8));

    float nearness = max( 0.5, (2.5 - (0.3 * (min (5.0, abs(_nodeId - _focus) ) ) ) ) ); 

      for (int i = 0; i < min(_activeMovements, 1); i++) //
    {
      // cout << "cares id " << _nodeId << " movement: " << i << " of "
      //      << _activeMovements << ". x " << x << " y " << y << " " << endl;

      if (_arrows[i]->onLine(x, y, nearness))
      {
        return true;
      }
    }
    return false;
  }

  uint32_t colorFor(int x, int y)
  {
    return _color;
  }

private:
  void _update()
  {
    // cout << "_update min(0,activeM " <<  min(0, _activeMovements) << endl;
    for (int i = 0; i < min(_activeMovements, 1); i++)
    {
      _arrows[i]->update(_currentTime);
    }
  }

  void _movementOn(long currentTime, int xOffset, int nodeId)
  {
    _focus = nodeId; // new center of attention

    for (int a=0; a < _activeArrows; a++)
      _arrows[a]->setTarget(nodeId);

    // cout << "_movementOn " << _nodeId << " at " << currentTime << " x: "
    //      << xOffset << " node: " << nodeId << " movements " << _activeMovements
    //      << " arrows " << _activeArrows;

    int direction;
    direction = (nodeId > _nodeId) ? 1 : -1;

    if (_activeArrows > 0)
    {
      _arrows[0]->direction = direction;
    }
    else
    {
      _arrows[_activeArrows++] = new Arrow(currentTime, direction, _nodeId, nodeId, _duration); 
    }
    // cout << "  arrows now: " << _activeArrows << endl;

//  now recalculate brightness.  Far away is 25%T);
    float delta = max( nodeId, (11 - nodeId));
    float step = .80 / delta;
    float bright = max(.15, (1.0 - ( abs(nodeId - _nodeId) * step)));
    // cout << "id " << setw(2) << _nodeId << " delta " << delta << " step " << step << " bright " << bright << endl;

    _color = _rgbToColor( (int) (bright * _r), (int) (bright * _g), (int) (bright * _b) );
  }

  void _movementOff(int xOffset, int nodeId)
  {
    // don't care.  only new movements matter.
  }

  uint32_t _color;
  Arrow *_arrows[NODE_COUNT];
  int _activeArrows = 0;
  int _focus = 0;
  int _r=0;
  int _g=0;
  int _b=0;
  int _duration=0;
};
