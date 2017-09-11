#include <iostream>

using namespace std;

// $ codesign -f -s  "gdb-cert"  <gnat_install_prefix>/bin/gdb

#include "Reed.h"

int main() {
  Reed *r1 = new Reed(3);
  r1->setColor(0, 1,2,3);
  r1->setColor(1, 4,5,6);
  r1->at(0).pp();
  cout << "Reed " << r1->pp();

}
