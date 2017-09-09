#ifndef Loggger_h
#define Loggger_h

#include "application.h"

#define ACTIVE true
#define INACTIVE false

class Loggger {
public:
  Loggger(bool active, String name) {
    _active = active;
    _name   = name;

    if (_active) {
      Serial.begin(9600);
    }
  }

  void log(String message) {
    if (_active) {
      Serial.print("[" + String(_name) + "] ");
      Serial.println(message);
    }
  }

private:
  bool _active;
  String _name;
};

#endif
