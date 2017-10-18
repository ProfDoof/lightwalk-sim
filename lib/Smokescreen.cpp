#include "standardEffect.h"
#include "application.h"
#include <math.h>

//PerlinNoiseCpp by Chris Litle from:
//https://github.com/captainhead/PerlinNoiseCpp
#include "NoiseGen/Perlin.h"
#include "NoiseGen/Perlin.cpp"


class Smokescreen : public StandardEffect {
public:
  Smokescreen(int id, long startTime, int r, int g, int b, int sp) : StandardEffect(id, startTime) {
    _r = r;
    _g = g;
    _b = b;

    int speedDiff = _mapFloat(sp, 1, 10, 0, 10000);
    _duration = 20000 - speedDiff;

	//fadein at beginning?
  }

  bool cares(int x, int y) {
    return true;
  }

  uint32_t colorFor(int x, int y) {
  	float tempX = _mapFloat(x, 1, 10, 0, 1.5);
  	float tempY = _mapFloat(y, 1, PIXEL_COUNT, 1, 7);

  	//Can I get it to wobble back and forth as well?
  	//float wobbleX = _mapFloat(p.noise(x, y + .5, 1), -1, 1, -100, 100);
  	//Doesn't matter too much if rods are not all straight up

  	float _intensity = _mapFloat(p.noise(tempX + _xOffset, tempY + count, 1), -1, 1, 0, 1);

	// tweek contrast
  	if (_intensity <= .5)
		_intensity = _mapFloat(_intensity, 0, .5, 0, .25);
	else
		_intensity = _mapFloat(_intensity, .5, 1, .35, 1);

	if (_intensity >= .45)
		_intensity = _mapFloat(_intensity, .5, 1, .6, 1);

    int relativeR = _r * _intensity;
    int relativeG = _g * _intensity;
    int relativeB = _b * _intensity;

    return _rgbToColor(relativeR, relativeG, relativeB);
  }

private:
  void _update() {

  	int timePassed = (_currentTime - _startTime) % _duration;
  	count = _mapFloat(timePassed, 0, _duration, PIXEL_COUNT, 0);
  	//When gets to 0, jumps back to PIXEL_COUNT, and therefore the image "jitters"
  }

  Perlin p;
  int _r;
  int _g;
  int _b;
  float count = PIXEL_COUNT;
  int _duration;
};