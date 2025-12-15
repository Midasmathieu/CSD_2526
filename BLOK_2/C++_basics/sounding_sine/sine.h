#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Sine : public Oscillator{
public:
  Sine(float frequency, float samplerate = 44100);
  ~Sine();
  // void setSamplerate(float samplerate);
  // //return current sample
  // float getSample();
  // //next sample
  // void tick();
// protected:
  void calculate();
  
  // void print();
  //
  // void setFrequency(float frequency);
  // float getFrequency();




private:

  // float samplerate;
  // float sample;
  // float frequency;
  // float amplitude { 0.25f };
  // float phase;
};

#endif
