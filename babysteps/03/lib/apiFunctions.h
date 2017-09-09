#ifndef ApiFunctions_h
#define ApiFunctions_h

#include "application.h"
#include "canBus.h"

class ApiFunctions {
public:
  ApiFunctions() {
    Particle.function("config", &ApiFunctions::_setConfig, this);
    Particle.function("read", &ApiFunctions::_readConfig, this);
    Particle.function("restart", &ApiFunctions::_restart, this);
  }

  void initialize(CanBus &canBus) {
    // keep a bus reference in order to broadcast messages
    _canBus = &canBus;
  }

private:
  int _setConfig(String command) {
    // expects command to be in format `id:value`
    int seperatorIndex = command.indexOf(":");

    int id         = atoi(command.substring(0, seperatorIndex));
    uint16_t value = atoi(command.substring(seperatorIndex + 1));

    EEPROM.put(id, value);

    return value;
  }

  int _readConfig(String command) {
    uint16_t value;

    EEPROM.get(atoi(command), value);

    return value;
  }

  Timer restartTimer = Timer(100, &ApiFunctions::_restartDevice, *this);

  int _restart(String command) {
    if (command.equals("all")) {
      _canBus->send(RESTART);
    }

    restartTimer.start();
    return 1;
  }

  void _restartDevice() {
    System.reset();
  }

  CanBus *_canBus;
};

#endif
