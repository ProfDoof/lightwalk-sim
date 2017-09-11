#include <iostream>
using namespace std;

#include "stubs.h"

#include "constants.h"

#include "standardEffect.h"
#include "lib/leds.h"
#include "WaveUp.cpp"

//#include "EEPROM.h"
//#include "lib/canBus.h"
//#include "lib/apiFunctions.h"
//#include "lib/heartbeat.h"
//#include "lib/networkManager.h"
//#include "lib/effectsManager.h"
//#include "lib/pir.h"

//SYSTEM_MODE(SEMI_AUTOMATIC);
//STARTUP(WiFi.selectAntenna(ANT_EXTERNAL));

//ApiFunctions apiFunctions;

//Heartbeat heartbeat;

// ApplicationWatchdog * wifiWatchdog;
// ApplicationWatchdog * bigWatchdog;
// ApplicationWatchdog * littleWatchdog;

// CANChannel bus(CAN_D1_D2, 100, 100);
// CanBus canBus(bus);

// EffectsManager backgroundEffectsManager(BACKGROUND);
// EffectsManager foregroundEffectsManager(FOREGROUND);

// NetworkManager networkManager(NODE_COUNT);

Leds leds;

//Pir pir;

uint16_t _nodeId;
uint16_t _xOffset;

// Effect (int id, long startTime)
//   update(long currentTime)
//     _update();

#define RUNS 10

#include "Led.h"

class Node {
private:
  int reeds
}

class LightWalk {
  public LightWalk( int nodes, int reeds, int pixels, Effect effect ) {
    for (int i=0, i<nodes, i++) {
      // 
    }
  }
  private nodes
}

// effect(id, startTime)
//   update(long newtime)
//     _currentTime = newtime
//     _update()
//
//   _mapFloat
//   _rgbToColor(r,g,b)
//  _xOffset, _startTime, _currentTime

// StandardEffect adds interactive() false, and movementOn(offset, time), movementOff(offset)
//
  
void display() {
  leds.show();
}

main ()
{
  leds.initialize();

  //  WaveUp(int id, long startTime, int r, int g, int b, int v) : StandardEffect(id, startTime) {
  StandardEffect *effect = new WaveUp(1, 0.1, 1, 0, 0, 1);
  
  // drive an effect
  for (int i=0; i<RUNS; i++) {
    effect->update(i);
    display();
  }
}


