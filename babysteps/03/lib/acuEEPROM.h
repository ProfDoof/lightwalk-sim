#ifndef acuEEPROM_h
#define acuEEPROM_h
// EEPROM.h
// Particle.io EEPROM stub
// (c) 2017 Brent Neal Reeves
//
int fget (int v1, uint16_t& v2) { return 1; };
void fread (int v1, int v2) {  };

struct myEEPROM {
  int (*get)(int addr, uint16_t&) = fget;
  void (*read)(int addr, int v2) = fread;
} EEPROM;

#endif
