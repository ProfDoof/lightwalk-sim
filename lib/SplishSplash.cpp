#include "standardEffect.h"
#include "application.h"
#include <list>

class RainDrop
{
public:
  RainDrop() {}

  void configure(int id, int sp, int h, float v, long st)
  {
    // cout<<"configure id: "<< id << " sp: " << sp<< " h: " << h << " v: " << v << " st: " << st << endl;
    position = sp;
    _height = h;
    _startPosition = sp;
    _velocity = v;
    _startTime = st;
    _id = id;
  }

  void update(long currentTime)
  {
    int oldPosition = position;
    position = _startPosition - (currentTime - _startTime) * _velocity;
  }

  bool surrounds(int y)
  {
    return position >= y && (position - _height) < y;
  }

  int position;

private:
  int _height;
  int _startPosition;
  float _velocity;
  long _startTime;
  int _id;

};

class SplishSplash : public StandardEffect
{
public:
  SplishSplash(int id, long startTime, int r, int g, int b, int sp) : StandardEffect(id, startTime)
  {
    _color = _rgbToColor(r, g, b);
    _speed = sp;

    for (int i = 0; i < REED_COUNT; i++)
    {
      if ((i % 2) == 0)
        _restartDrop(i);
    }
  }

  bool cares(int x, int y)
  {
    if (_drops[x].surrounds(y))
    {
      return true;
    }

    if (y > 8) // highest splash
      return false;

    // int turningPoint = - _splatter_length;
    int splashRadius = 2;

    int xFrom = x - splashRadius;
    if (xFrom < 0)
      xFrom = 0;

    int xTo = x + splashRadius + 1;
    if (xTo > REED_COUNT)
      xTo = REED_COUNT;

    //    cout << "cares " << x << "," << y << " check " << xFrom << " to " << xTo << endl;
    for (int x2 = xFrom; x2 < xTo; x2++)
    {
      // cout << "  checking " << x2 << " at " << _drops[x2].position << endl;
      // if (x == x2)
      //   continue;
      int xDelta = abs(x - x2);
      int y2 = _drops[x2].position;
      if (y2 < 0)
      {
        int newy = (y + xDelta);
        // ( (turningPoint - static_cast<int>( abs(i + turningPoint))) / 4)

        int daPoint = ( (_turningPoint - static_cast<int>( abs(y2 + _turningPoint))) / 4);
        // cout << "  neg " << x << " at " << y << " got " << x2 << " " << y2 << " turn " << turningPoint << " daPoint " << daPoint << endl;
        if (y2 < (0 - (2 * _turningPoint)))
          return false;
        if (newy == daPoint)
        {
          // cout << "splash 1 x: " << x << " from " << x2 << " at " << y2 << endl;
          // if (random(1, 5) > 4.0)
            return true;
        }
      }
    }

    return false;
  }

  float distance(int x, int y, int x2, int y2)
  {
    return ceil(sqrt(
        (abs(abs(x) - abs(x2)) ^ 2) +
        (abs(abs(y) - abs(y2)) ^ 2)));
  }

  uint32_t colorFor(int x, int y)
  {
    return _color;
  }

  int positionOf(int x)
  {
    return _drops[x].position;
  }

  string positions()
  {
    std::stringstream ss;
    for (int i = 0; i < REED_COUNT; i = i + 1)
    {
      ss << setw(3) << _drops[i].position;
    }
    return ss.str();
  }

private:
  void _update()
  {
    for (int i = 0; i < REED_COUNT; i++)
    {
      // only run evens
      if ((i % 2) != 0)
        continue;

      _drops[i].update(_currentTime);
      if (_drops[i].position < (0 - (2 * _turningPoint)))
      {
        _restartDrop(i);
      }
    }
  }

  void _restartDrop(int index)
  {
    // cout << "restart " << index << " y: " << _drops[index].position << endl;
    // int startPosition = random(PIXEL_COUNT, PIXEL_COUNT * 2);
    int startPosition = 50;
    // int height = random(1, 2);
    int height = 2;
    float velocity = random(30, _speed * 30) * 1.0 / 1000;
    // float velocity = (_speed * 20) * 1.0 / 1000;

    _drops[index].configure(index, startPosition, height, velocity, _currentTime);
    // cout << "restartDrop startPosition: " << startPosition << " h: " << height << " v: " << velocity << " time: " << _currentTime << endl;
  }

  uint32_t _color;
  int _speed;
  int _turningPoint = 20;
  RainDrop _drops[REED_COUNT];
};
