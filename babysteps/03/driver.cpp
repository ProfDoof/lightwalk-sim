#include <iostream>
using namespace std;

#include "constants.h"

#include "lib/leds.h"
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
define RUNS 1000

main ()
{
  leds.initialize();

  //  WaveUp(int id, long startTime, int r, int g, int b, int v) : StandardEffect(id, startTime) {
  effect = new WaveUp(1, 0.1, 1, 0, 0, 1);
  // now test the Effect

  effect.setup();
  
  // drive an effect
  for (int i=0; i<RUNS; i++) {
    effect.loop();
    display();
  }
}

void display() {
  leds.show();
}
