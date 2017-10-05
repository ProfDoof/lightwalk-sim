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

int random (int daEnd) {
  return random ( 0, daEnd );
}

int min( int n1, int n2) {
  return std::min(n1, n2);
}

// float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
// {
//   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

// int map (int i1, int aFrom, int aTo, int bFrom, int bTo) {
//   return mapFloat(i1, aFrom, aTo, bFrom, bTo);
// }
// map(moleTime, 0, 4000, 0, PIXEL_COUNT);


#endif /* APPLICATION_H_ */
