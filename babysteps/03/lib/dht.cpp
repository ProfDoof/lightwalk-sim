#include "dht.h"

DHT::DHT() {
  pinMode(DHT_PIN, INPUT);
  digitalWrite(DHT_PIN, HIGH);
}

void DHT::read() {
  uint8_t lastState = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0, i = 0;
  unsigned long currentTime;

  currentTime = millis();
  if (currentTime < _lastReadTime) {
    // there was a rollover
    _lastReadTime = 0;
  }

  if (!_firstReading && ((currentTime - _lastReadTime) < 2000)) {
    return;
  }

  _firstReading = false;
  _lastReadTime = millis();

  _data[0] = _data[1] = _data[2] = _data[3] = _data[4] = 0;

  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, LOW);
  delay(20);
  noInterrupts();
  digitalWrite(DHT_PIN, HIGH);
  delayMicroseconds(40);
  pinMode(DHT_PIN, INPUT);

  // read in timings
  for (i = 0; i < DHT_TIMINGS; i++) {
    counter = 0;

    while (digitalRead(DHT_PIN) == lastState) {
      counter++;
      delayMicroseconds(1);

      if (counter == 255) {
        break;
      }
    }

    lastState = digitalRead(DHT_PIN);

    if (counter == 255) {
      break;
    }

    // ignore first 3 transitions
    if ((i >= 4) && (i%2 == 0)) {
      // shove each bit into the storage bytes
      _data[j/8] <<= 1;

      if (counter > DHT_COUNT) {
        _data[j/8] |= 1;
      }

      j++;
    }
  }

  interrupts();

  // check we read 40 bits and that the checksum matches
  if ((j >= 40) && (_data[4] == ((_data[0] + _data[1] + _data[2] + _data[3]) & 0xFF))) {
    humidity = _data[0];
    humidity *= 256;
    humidity += _data[1];
    humidity /= 10;

    temperature = _data[2] & 0x7F;
    temperature *= 256;
    temperature += _data[3];
    temperature /= 10;
    // negative temperature
    if (_data[2] & 0x80) {
      temperature *= -1;
    }
  }

  // put DHT_PIN back into default state
  digitalWrite(DHT_PIN, HIGH);
}
