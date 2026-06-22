#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "oscillator.h"
#include <iostream>
#include <cmath>

class Square : public Oscillator
{
public:
  //Constructor and destructor
  Square();
  ~Square();
  //return the current sample
  float getSample();
  // go to next sample
  void calculateSample();

private:
  const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
  float amplitude;
  // sample contains the current sample
  float sample; 
};

#endif
