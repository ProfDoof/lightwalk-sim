#ifndef CanBus_h
#define CanBus_h

#include "application.h"
#include "constants.h"
#include "loggger.h"

class CanBus
{
  public:
    CanBus(CANChannel &bus);

    void read();
    void send(int d0, int d1, int d2, int d3, int d4, int d5, int d6, int d7);
    void send(int d0, int d1, int d2, int d3, int d4, int d5, int d6);
    void send(int d0, int d1, int d2, int d3, int d4, int d5);
    void send(int d0, int d1, int d2, int d3, int d4);
    void send(int d0, int d1, int d2, int d3);
    void send(int d0, int d1, int d2);
    void send(int d0, int d1);
    void send(int d0);
    void send(int data[8]);

    bool newMessage = false;
    CANMessage message;
    CANMessage messageTx;

  private:
    CANChannel *_bus;

    Loggger logger = Loggger(INACTIVE, "CAN BUS");
};

#endif
