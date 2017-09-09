#ifndef Xbee_h
#define Xbee_h

#include "application.h"

class Xbee
{
  public:
    Xbee() {};

    void initialize();
    void read();
    void send(int d0);

    String receivedChars;
    bool newMessage = false;
};

#endif
