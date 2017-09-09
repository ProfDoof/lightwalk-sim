#include "networkManager.h"

NetworkManager::NetworkManager(int nodeCount) {
  _nodeCount = nodeCount;
}

void NetworkManager::initialize(CanBus &canBus) {
  // keep a bus reference in order to broadcast messages
  // incoming messages will be passed in individually
  _canBus = &canBus;

  _cleanPromotionList();

  // wait a bit before raising missing master flags
  _lastHeardMaster = millis();
}

void NetworkManager::processMessage(CANMessage message) {
  if (message.data[1] == HEARTBEAT) {
    // received heartbeat from master
    _heardFromMaster(message.data[2]);
  }

  if (message.data[1] == CANDIDATE) {
    // received a new possible master id
    if (!_masterSearch) _beginMasterSearch();

    _forPromotion[_promotionIndex++] = message.data[2];
  }
}

void NetworkManager::update() {
  if (isMaster) {
    if (millis() > _lastBroadcasted + _broadcastDelay) _sendHeartbeat();
  } else {
    if (_masterSearch) {
      if (millis() > _masterSearchStart + _searchDelay) _finishMasterSearch();
    } else {
      if (millis() > _lastHeardMaster + _heardMasterDelay) _beginMasterSearch();
    }
  }
}

void NetworkManager::_beginMasterSearch() {
  logger.log("Begin master search");

  _masterSearch = true;
  _masterSearchStart = millis();

  _canBus->send(NETWORK_CALL, CANDIDATE, _nodeId);
}

void NetworkManager::_finishMasterSearch() {
  logger.log("Finish master search");
  logger.log("nodeId:          " + String(_nodeId));

  bool shouldPromoteSelf = true;
  for (int i = 0; i < _nodeCount; i++) {
    logger.log("forPromotion[" + String(i) + "]: " + String(_forPromotion[i]));

    // check if there's a lower _nodeId up for promotion
    if (_forPromotion[i] < _nodeId) shouldPromoteSelf = false;
  }

  _masterSearchCleanup();

  if (shouldPromoteSelf) {
    _promoteSelfToMaster();
  } else {
    // give the new master a chance to broadcast
    _lastHeardMaster = millis();
  }
}

void NetworkManager::_heardFromMaster(int masterId) {
  logger.log("Heard from master: " + String(masterId));

  _lastHeardMaster = millis();

  // if you're the master, step on down
  if (isMaster) _demoteSelf();

  // if searching for master, give that up
  if (_masterSearch) _masterSearchCleanup();
}

void NetworkManager::_masterSearchCleanup() {
  logger.log("Master search cleanup");

  _masterSearch = false;

  if (_promotionIndex != 0) {
    _cleanPromotionList();
  }
}

void NetworkManager::_cleanPromotionList() {
  _promotionIndex = 0;

  for (int i = 0; i < _nodeCount; i++) {
    _forPromotion[i] = 255;
  }
}

void NetworkManager::_promoteSelfToMaster() {
  logger.log("Promoting self to master");

  Particle.publish("master", "true");
  isMaster = true;
}

void NetworkManager::_demoteSelf() {
  logger.log("Demoting self");

  Particle.publish("master", "false");
  isMaster = false;
}

void NetworkManager::_sendHeartbeat() {
  logger.log("Sending heartbeat");

  _lastBroadcasted = millis();

  _canBus->send(NETWORK_CALL, HEARTBEAT, _nodeId);
}
