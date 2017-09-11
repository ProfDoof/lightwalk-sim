#include <iostream>

using namespace std;

#include "Led.h"

int main() {
  Led *l1 = new Led (1,2,3,4);
  cout << "Led " << l1->r() << "," << l1->g() << "," << l1->b() << ", " << l1->brightness() << endl;;
  cout << l1->pp() << endl;
  cout << l1->hex() << endl;

  l1->setColor(5,6,7);
  cout << l1->pp() << endl;
  cout << l1->hex() << endl;

  l1->setBrightness(255);
  cout << l1->pp() << endl;
  cout << l1->hex() << endl;

  l1->setColor(0,1,255);
  cout << l1->pp() << endl;
  cout << l1->hex() << endl;

  l1->setColor(255,0,1);
  cout << l1->pp() << endl;
  cout << l1->hex() << endl;

  
  //  for (int i=0; i<255; i++) { cout << std::dec << i << " " << std::hex << i << endl;  }
}
