#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Sine : public Oscillator{
public:
  Sine(float frequency = 100.0f, float samplerate = 44100);
  ~Sine();

  void calculate();






private:


};

#endif
