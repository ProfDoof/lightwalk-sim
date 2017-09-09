#ifndef Heartbeat_h
#define Heartbeat_h

#include "application.h"
#include "constants.h"
#include "networkManager.h"
#include "dht.h"

#define HEARTBEAT 0
#define CANDIDATE 1

class Heartbeat {
public:
  Heartbeat() {};

  void initialize(NetworkManager &networkManager, int nodeId, int xOffset) {
    _networkManager = &networkManager;
    _nodeId         = nodeId;
    _xOffset        = xOffset;

    _beat();
    _timer = millis();
  }

  void update() {
    if (millis() > _timer + HEARTBEAT_INTERVAL) {
      _beat();
      _timer = millis();
    }
  }

private:
  void _beat() {
    _dht.read();

    String data = String::format(
      "{\"id\":%d,\"xo\":%d,\"fv\":%d,\"fm\":%d,\"ss\":%d,\"im\":%d,\"te\":%.2f,\"hu\":%.2f}",
      _nodeId,
      _xOffset,
      FIRMWARE_VERSION,
      System.freeMemory(),
      WiFi.RSSI(), // signal strength
      _networkManager->isMaster,
      _dht.temperature,
      _dht.humidity
    );

    Particle.publish("heartbeat", data);
  }

  long _timer;
  DHT _dht;
  NetworkManager * _networkManager;
  int _nodeId;
  int _xOffset;
};

#endif
