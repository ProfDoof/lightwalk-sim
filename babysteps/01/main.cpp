#include <iostream>
#include "lib/aculib.h"
using namespace std;

int main()
{
  cout << "Hello from main.cpp" << endl;
  float x;
  x = _mapFloat(5, 1,10, 10.0, 20.0);
  cout << "_mapFloat() " << x;
}

 
