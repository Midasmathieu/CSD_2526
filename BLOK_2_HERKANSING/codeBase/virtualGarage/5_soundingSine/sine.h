#ifndef _SINE_H_
#define _SINE_H_
#include "oscillator.h"
#include <iostream>
#include <cmath>

class Sine : public Oscillator
{
public:
  //Constructor and destructor
  Sine();//float frequency, float samplerate = 44100);
  ~Sine();
  //void setSamplerate(float samplerate);
  //return the current sample
  float getSample();
  void calculateSample();
  // go to next sample
  //void tick();

  //getters and setters
  //void setFrequency(float frequency);
  //float getFrequency();
  //float samplerate;
  //float frequency;
private:
  const float pi = acos (-1);  //atan(1) * 4; <-- vak van Pieter.
  float amplitude;
  //float phase;
  // sample contains the current sample
  float sample;
  
};

#endif
