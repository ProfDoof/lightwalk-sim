#include <iostream>
using namespace std;

struct myEEPROM {
  int read;
  int get;
} EEPROM;

int main ( int argc, char * argv[] ) {
  EEPROM.read = 1;
  cout << "read " << EEPROM.read << endl;
  return 0;
}
