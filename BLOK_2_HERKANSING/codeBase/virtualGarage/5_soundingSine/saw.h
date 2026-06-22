#ifndef _SAW_H_
#define _SAW_H_
#include "oscillator.h"
#include <iostream>
#include <cmath>

class Saw : public Oscillator
{
public:
  //Constructor and destructor
  Saw();
  ~Saw();
  //return the current sample
  float getSample();
  // go to next sample
  void calculateSample();

  //getters and setters
  
private:
  const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
  float amplitude;
  // sample contains the current sample
  float sample;
};

#endif
