// blee2.cpp
#include <iostream>
using namespace std;


int f1 (int v1) { return v1; };

//int pFunc1 (int v1);
auto pFunc1 = f1;


struct myEEPROM {
  int read;
  int get;
} EEPROM;

int main ( int argc, char * argv[] ) {
  EEPROM.read = 1;
  cout << "read " << EEPROM.read << endl;

  int result = pFunc1(11);
  cout << "result " << result << endl;
  return 0;
}
