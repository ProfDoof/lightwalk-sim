#ifndef Reed_h
#define Reed_h
// Reed.h
// (c) Brent Neal Reeves
// lightwalk test harness
// needs:
#include "Led.h"
#include <sstream>

class Reed {
public:
  Reed(int height) {
    _leds = NULL;
    _leds = new Led[_height];
  }
  int height() {return _height;};

  void setBrightness (int height, int b) {
    _leds[height].setBrightness( b );
  }

  void setColor (int height, int r, int g, int b) {
    _leds[height].setColor(r, g, b);
  }

  Led at(int height) {
    return _leds[height];
  }

  string pp() {
    std::stringstream ss;
    for (int i=0; i<_height; i++) {
      ss << _leds[i].hex() << ", ";
    }
    string str = ss.str();
    return str;
  }

private:
  int _height;
  Led* _leds;
};

#endif
