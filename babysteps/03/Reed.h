#ifndef Reed_h
#define Reed_h
// Reed.h
// (c) Brent Neal Reeves
// lightwalk test harness
// needs:
#include "Led.h"
#include <sstream>
#define MAXLEDS 37

class Reed {
public:
  Reed(int height) {
	  _height = height;
//	  _leds = NULL;
//	  _leds = new Led[height];

  }
  int height() {return _height;};

  void setBrightness (int y, int b) {
    _leds[ min(y, MAXLEDS) ].setBrightness( b );
  }

  void setColor (int y, int r, int g, int b) {

    _leds[ min(y, MAXLEDS) ].setColor(r, g, b);
  }

  Led at(int y) {
    return _leds[ min(y, MAXLEDS)];
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
  Led _leds[MAXLEDS];
};

#endif
