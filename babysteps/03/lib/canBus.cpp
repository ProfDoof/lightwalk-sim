#include "canBus.h"

CanBus::CanBus(CANChannel &bus) {
  _bus = &bus;
  _bus->begin(CAN_BAUD);

  messageTx.len = 8;
}

void CanBus::read() {
  newMessage = false;

  while (_bus->available()){
    if (_bus->receive(message)) {
      logger.log("Receiving!");
      logger.log("0: " + String(message.data[0]));
      logger.log("1: " + String(message.data[1]));
      logger.log("2: " + String(message.data[2]));
      logger.log("3: " + String(message.data[3]));
      logger.log("4: " + String(message.data[4]));
      logger.log("5: " + String(message.data[5]));
      logger.log("6: " + String(message.data[6]));
      logger.log("7: " + String(message.data[7]));

      newMessage = true;
      return;
    }
  }
}

void CanBus::send(int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7) {
  logger.log("Sending!");
  logger.log("0: " + String(d0));
  logger.log("1: " + String(d1));
  logger.log("2: " + String(d2));
  logger.log("3: " + String(d3));
  logger.log("4: " + String(d4));
  logger.log("5: " + String(d5));
  logger.log("6: " + String(d6));
  logger.log("7: " + String(d7));

  messageTx.data[0] = d0;
  messageTx.data[1] = d1;
  messageTx.data[2] = d2;
  messageTx.data[3] = d3;
  messageTx.data[4] = d4;
  messageTx.data[5] = d5;
  messageTx.data[6] = d6;
  messageTx.data[7] = d7;

  _bus->transmit(messageTx);
}

void CanBus::send(int d0, int d1, int d2, int d3, int d4, int d5, int d6) {
  send(d0, d1, d2, d3, d4, d5, d6, 0);
}

void CanBus::send(int d0, int d1, int d2, int d3, int d4, int d5) {
  send(d0, d1, d2, d3, d4, d5, 0, 0);
}

void CanBus::send(int d0, int d1, int d2, int d3, int d4) {
  send(d0, d1, d2, d3, d4, 0, 0, 0);
}

void CanBus::send(int d0, int d1, int d2, int d3) {
  send(d0, d1, d2, d3, 0, 0, 0, 0);
}

void CanBus::send(int d0, int d1, int d2) {
  send(d0, d1, d2, 0, 0, 0, 0, 0);
}

void CanBus::send(int d0, int d1) {
  send(d0, d1, 0, 0, 0, 0, 0, 0);
}

void CanBus::send(int d0) {
  send(d0, 0, 0, 0, 0, 0, 0, 0);
}

void CanBus::send(int data[8]) {
  send(
    data[0],
    data[1],
    data[2],
    data[3],
    data[4],
    data[5],
    data[6],
    data[7]
  );
}
