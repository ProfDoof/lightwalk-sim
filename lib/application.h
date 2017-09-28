#ifndef APPLICATION_H_
#define APPLICATION_H_

//#include <iostream>
#include <random>
//#include <algorithm>

/*
int random (int highest) { 
  std::random_device rd;  //Will be used to obtain a seed for the random number engine 
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd() 
  std::uniform_int_distribution<> dis(0, highest); 
   
  return dis(gen);
}
*/

int random (int from, int daEnd) { 
  //  std::cout << "random " << from << ", " << daEnd << std::endl; 
  std::random_device rd;  //Will be used to obtain a seed for the random number engine 
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd() 
  std::uniform_int_distribution<> dis(from, daEnd); 
  //  std::cout << "random returning." << std::endl; 
  return dis(gen); 
}

int min( int n1, int n2) {
  return std::min(n1, n2);
}


#endif /* APPLICATION_H_ */
