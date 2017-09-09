#ifndef EffectsManager_h
#define EffectsManager_h

#include "application.h"
#include "constants.h"
#include "canBus.h"
#include "loggger.h"

// BEGIN effect definitions
#define RAINBOW_RAIN 1
#define ACID_RAIN 2
#define WAVE_UP 3
#define BUBBLES 4

#include "effects/standard/rainbow-rain.h"
#include "effects/standard/acid-rain.h"
#include "effects/standard/wave-up.h"
#include "effects/interactive/bubbles.h"
// END effect definitions

#define MAX_EFFECTS 50

#define REMOVE_ALL 1

#define BACKGROUND 0
#define FOREGROUND 1

class EffectsManager {
public:
  EffectsManager(int position);
  void initialize(CanBus &canBus);
  void addEffect(CANMessage message);
  void removeEffect(CANMessage message);
  void clearAll();
  void movementOn(CANMessage message);
  void movementOff(CANMessage message);
  void update();
  bool cares(int x, int y);
  uint32_t colorFor(int x, int y);

  int activeEffects = 0;

private:
  CanBus *_canBus;

  Effect *_effects[MAX_EFFECTS];
  int _position;

  int _handleAdd(String command);
  int _handleRemove(String command);
  void _parseCommand(String command, int args[7]);
  int _checksum(int args[7]);

  int _fakePirOn(String command);
  int _fakePirOff(String command);

  Loggger logger = Loggger(INACTIVE, "EffectsManager");
};

#endif
