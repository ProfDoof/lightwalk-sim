#include "xbee.h"

void Xbee::initialize() {
  Serial1.begin(115200);
}

void Xbee::read() {
  receivedChars = "";
  char endMarker = '\n';
  char rc;

  newMessage = false;

  while (Serial1.available() > 0) {
    rc = Serial1.read();

    if (rc == endMarker) {
      newMessage = true;
      return;
    } else {
      receivedChars = receivedChars + String(rc);
    }
  }
}

void Xbee::send(int d0) {
  Serial1.println(d0);
}
