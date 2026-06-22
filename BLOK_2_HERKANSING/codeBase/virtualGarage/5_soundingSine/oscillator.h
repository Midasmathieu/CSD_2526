#ifndef _OSCILLATOR_H_
#define _OSCILLATOR_H_
#include <iostream>
#include <cmath>

class Oscillator
{
 public:
  Oscillator();
  ~Oscillator();
  void tick();
  void setFrequency(float frequency);
  void setSamplerate(float samplerate);
  float samplerate = 48000.0f;
  float frequency = 0;
  float phase = 0;
};

#endif
