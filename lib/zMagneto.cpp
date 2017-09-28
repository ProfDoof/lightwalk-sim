#include "interactiveEffect.h"
#include "application.h"

#define DURATION 4000

#define V_WIDTH 6
#define V_HEIGHT 12

class Magneto : public InteractiveEffect
{
public:
  Magneto(int id, long startTime, int r, int g, int b) : InteractiveEffect(id, startTime)
  {
    _color = _rgbToColor(r, g, b);
  }

  bool cares(int x, int y)
  {
    int arrowHead = (int)_mapFloat(timePassed, 0, DURATION, 4, 10);
    // If y > middle, then
  }

uint32_t colorFor(int x, int y)
{
  return _color;
}

private:
bool inArrow(int x, int y)
{
  assert(x >= 0);
  assert(x < 4);
  assert(y >= 0);
  assert(y < 7);
  return (arrow[(6 - y)].at(x) == 'x');
}

void _update() {
  float percentagePassed;

  int timePassed = (_currentTime - _startTime) % DURATION;

  if (timePassed < HALF_DURATION) {
    percentagePassed = _mapFloat(timePassed, 0, HALF_DURATION, 0.2, 1.0);
  } else {
    percentagePassed = _mapFloat(timePassed, HALF_DURATION, DURATION, 1.0, 0.2);
  }

  _radius = percentagePassed * MAX_BUBBLE_RADIUS;
}


int timePassed = (currentTime - startTime) % DURATION;

float _mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void _movementOn(long currentTime, int xOffset, int nodeId)
{
  // cout << "_movementOn " << identifier << " at " << currentTime << " x: " << xOffset << " node: " << nodeId << endl;
  // aim arrows to this new target

  _bubbles[_activeBubbles++] = new Bubble(currentTime, xOffset);
}

void _movementOff(int xOffset, int nodeId)
{
  // that node is no longer the boss, but then who is?
  return;
}

uint32_t _color;
bool left = true;
std::string _arrow[7] = {
    "---x",
    "---x",
    "--x-",
    "--x-",
    "-x--",
    "-x--",
    "x---"};

  }
;
