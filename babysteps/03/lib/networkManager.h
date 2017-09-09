#ifndef NetworkManager_h
#define NetworkManager_h

#include "application.h"
#include "constants.h"
#include "canBus.h"
#include "loggger.h"

#define HEARTBEAT 0
#define CANDIDATE 1

class NetworkManager {
public:
  NetworkManager(int nodeCount);
  void initialize(CanBus &canBus);
  void processMessage(CANMessage message);
  void update();

  bool isMaster = false;

private:
  void _cleanPromotionList();
  void _beginMasterSearch();
  void _finishMasterSearch();
  void _heardFromMaster(int masterId);
  void _masterSearchCleanup();
  void _promoteSelfToMaster();
  void _demoteSelf();
  void _sendHeartbeat();

  CanBus *_canBus;

  long _lastBroadcasted;
  int  _broadcastDelay = 250;

  long _lastHeardMaster;
  int  _heardMasterDelay = 2000;

  bool _masterSearch = false;
  long _masterSearchStart;
  int  _searchDelay = 2000;

  int _nodeId = EEPROM.read(NODE_ID_ADDRESS);
  int _forPromotion[NODE_COUNT + 10]; // a couple extra for good measure
  int _promotionIndex = 0;

  int _nodeCount;

  Loggger logger = Loggger(INACTIVE, "NetworkMaster");
};

#endif
