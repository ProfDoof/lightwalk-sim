#include "pir.h"

Pir::Pir() {
  pinMode(PIR_PIN, INPUT);

  _resetInterval();

  // give the sensor a couple seconds to wake up
  _intervalStart = millis() + 5000;
}

void Pir::update() {
  _resetMovementVariables();
  _makeReading();

  if (millis() > _intervalStart + READING_INTERVAL) {
    _analyzeInterval();
    _resetInterval();
  }
}

void Pir::_resetMovementVariables() {
  movementOn = false;
  movementOff = false;
}

void Pir::_makeReading() {
  int pirReading = analogRead(PIR_PIN);

  if (pirReading < _pirLow)  _pirLow = pirReading;
  if (pirReading > _pirHigh) _pirHigh = pirReading;
}

void Pir::_analyzeInterval() {
  int difference = _pirHigh - _pirLow;

  if (!_seesMovement) {
    if (difference > MOVEMENT_THRESHOLD) {
      logger.log("Movement START");
      movementOn = true;
      _seesMovement = true;
      _lastSustainingMeasurement = millis();
    }
  } else {
    if (difference > SUSTAIN_BUFFER) {
      logger.log(".");
      _lastSustainingMeasurement = millis();
    } else {
      if (millis() > _lastSustainingMeasurement + SUSTAIN_BUFFER) {
        logger.log("Movement STOP");
        movementOff = true;
        _seesMovement = false;
      }
    }
  }
}


void Pir::_resetInterval() {
  _pirLow  = 4096;
  _pirHigh = 0;

  _intervalStart = millis();
}
