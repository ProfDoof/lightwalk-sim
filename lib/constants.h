#ifndef CONSTANTS_h
#define CONSTANTS_h

#define FIRMWARE_VERSION 51

#define NODE_COUNT 35

// CANbus data[0] message type identifiers
#define ADD_BACKGROUND_EFFECT    0
#define REMOVE_BACKGROUND_EFFECT 1
#define ADD_FOREGROUND_EFFECT    2
#define REMOVE_FOREGROUND_EFFECT 3
#define CLEAR_ALL                4
#define MOVEMENT_ON              200
#define MOVEMENT_OFF             201
#define RESTART                  254
#define NETWORK_CALL             255

#define CAN_BAUD 250000

#define xxREED_COUNT 10
#define xxPIXEL_COUNT 37

#define BRIGHTNESS 100

// max 'x' value on the x/y spectrum
#define MAX_WIDTH 350

// Heartbeat interval
#define HEARTBEAT_INTERVAL 60000

// EEPROM memory addresses
// skipping every other address so we can store
// 16 bit values (1 address jump = 8 bits)
#define NODE_ID_ADDRESS 0
#define OFFSET_ADDRESS  2

#define MAXEFFECTS 2

#define REED_COUNT 10
#define PIXEL_COUNT 37

#endif
