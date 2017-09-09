#ifndef Pir_h
#define Pir_h

#include "application.h"
#include "loggger.h"

#define PIR_PIN A7

#define READING_INTERVAL   250
#define SUSTAIN_BUFFER     750
#define MOVEMENT_THRESHOLD 2500
#define SUSTAIN_THRESHOLD  1000

class Pir {
public:
  Pir();

  void update();

  bool movementOn  = false;
  bool movementOff = false;

private:
  void _resetMovementVariables();
  void _makeReading();
  void _analyzeInterval();
  void _resetInterval();

  long _intervalStart;
  long _lastSustainingMeasurement;

  int _pirLow;
  int _pirHigh;

  bool _seesMovement = false;

  Loggger logger = Loggger(ACTIVE, "PIR");
};

#endif
