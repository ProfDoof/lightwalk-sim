#include "effectsManager.h"

EffectsManager::EffectsManager(int position) {
  _position = position;

  if (position == BACKGROUND) {
    Particle.function("addBEffect", &EffectsManager::_handleAdd, this);
    Particle.function("rmBEffect", &EffectsManager::_handleRemove, this);
  } else {
    Particle.function("addFEffect", &EffectsManager::_handleAdd, this);
    Particle.function("rmFEffect", &EffectsManager::_handleRemove, this);
  }

  Particle.function("pirOn", &EffectsManager::_fakePirOn, this);
  Particle.function("pirOff", &EffectsManager::_fakePirOff, this);
}

void EffectsManager::initialize(CanBus &canBus) {
  // keep a bus reference in order to broadcast messages
  // incoming messages will be passed in individually
  _canBus = &canBus;
}

void EffectsManager::addEffect(CANMessage message) {
  // Can't add effects if we're already at the limit
  if (activeEffects == MAX_EFFECTS) return;

  switch(message.data[1]) {
    // BEGIN effect triggers
    case RAINBOW_RAIN:
      _effects[activeEffects++] = new RainbowRain(RAINBOW_RAIN, millis());
      break;

    case ACID_RAIN:
      _effects[activeEffects++] = new AcidRain(ACID_RAIN, millis(), message.data[2], message.data[3], message.data[4], message.data[5]);
      break;

    case WAVE_UP:
      _effects[activeEffects++] = new WaveUp(WAVE_UP, millis(), message.data[2], message.data[3], message.data[4], message.data[5]);
      break;

    case BUBBLES:
      _effects[activeEffects++] = new Bubbles(BUBBLES, millis(), message.data[2], message.data[3], message.data[4]);
      break;

    // END effect triggers
  }
}

void EffectsManager::removeEffect(CANMessage message) {
  // Can't remove effects if we don't have any
  if (activeEffects == 0) return;

  int effectId = message.data[1];

  for (int i = 0; i < activeEffects; i++) {
    if (_effects[i]->identifier == effectId) {
      // starting at this index, slide all the effects down in the _effects array,
      // overwriting the effect we're removing
      for (int j = i; j < activeEffects - 1; j++) {
        _effects[j] = _effects[j + 1];
      }

      activeEffects -= 1;

      if (message.data[2] == REMOVE_ALL) {
        // Decrement for loop index to inspect the new effect that
        // just took the place of the one we removed
        i -= 1;
      } else {
        // Just removing one, break out of the function before removing any others
        return;
      }
    }
  }
}

void EffectsManager::clearAll() {
  activeEffects = 0;
}

void EffectsManager::movementOn(CANMessage message) {
  int xOffset = message.data[1] * 2;

  for (int i = 0; i < activeEffects; i++) {
    if (_effects[i]->interactive()) {
      _effects[i]->movementOn(xOffset, millis());
    }
  }
}

void EffectsManager::movementOff(CANMessage message) {
  int xOffset = message.data[1] * 2;

  for (int i = 0; i < activeEffects; i++) {
    if (_effects[i]->interactive()) {
      _effects[i]->movementOff(xOffset);
    }
  }
}

void EffectsManager::update() {
  long currentTime = millis();

  for (int i = 0; i < activeEffects; i++) {
    _effects[i]->update(currentTime);
  }
}

bool EffectsManager::cares(int x, int y) {
  for (int i = 0; i < activeEffects; i++) {
    if (_effects[i]->cares(x, y)) {
      return true;
    }
  }

  return false;
}

uint32_t EffectsManager::colorFor(int x, int y) {
  uint32_t color = 0;

  for (int i = 0; i < activeEffects; i++) {
    if (_effects[i]->cares(x, y)) {
      color = _effects[i]->colorFor(x, y);
    }
  }

  return color;
}

int EffectsManager::_handleAdd(String command) {
  // Can't add effects if we're already at the limit
  if (activeEffects == MAX_EFFECTS) return 0;

  int args[7];
  _parseCommand(command, args);

  int addKey = (_position == BACKGROUND) ? ADD_BACKGROUND_EFFECT : ADD_FOREGROUND_EFFECT;

  _canBus->send(
    addKey,
    args[0],
    args[1],
    args[2],
    args[3],
    args[4],
    args[5],
    args[6]
  );

  // Since transmitted messages are not processed by the transmitter,
  // we must process the message ourselves.
  addEffect(_canBus->messageTx);

  return _checksum(args);
}

int EffectsManager::_handleRemove(String command) {
  int args[7];
  _parseCommand(command, args);

  int removeKey = (_position == BACKGROUND) ? REMOVE_BACKGROUND_EFFECT : REMOVE_FOREGROUND_EFFECT;

  _canBus->send(
    removeKey,
    args[0],
    args[1],
    args[2],
    args[3],
    args[4],
    args[5],
    args[6]
  );

  // Since transmitted messages are not processed by the transmitter,
  // we must process the outgoing message ourselves.
  removeEffect(_canBus->messageTx);

  return _checksum(args);
}

void EffectsManager::_parseCommand(String command, int args[7]) {
  int index = 0;

  int lastPosition = -1;
  int commaPosition = command.indexOf(",");

  while (commaPosition > -1) {
    args[index++] = atoi(command.substring(lastPosition + 1, commaPosition));

    lastPosition = commaPosition;
    commaPosition = command.indexOf(",", commaPosition + 1);
  }
  args[index] = atoi(command.substring(lastPosition + 1));

  // Write the remaining arg values with 0s for an accurate checksum
  for (int i = index + 1; i < 7; i++) {
    args[i] = 0;
  }
}

int EffectsManager::_checksum(int args[7]) {
  int sum = 0;

  for (int i = 0; i < 7; i++) {
    logger.log("Adding " + String(args[i]));
    sum += args[i];
  }

  logger.log("Sum is: " + String(sum));

  return sum;
}

int EffectsManager::_fakePirOn(String command) {
  _canBus->send(MOVEMENT_ON, atoi(command));
  movementOn(_canBus->messageTx);

  return 0;
}

int EffectsManager::_fakePirOff(String command) {
  _canBus->send(MOVEMENT_OFF, atoi(command));
  movementOff(_canBus->messageTx);

  return 0;
}
