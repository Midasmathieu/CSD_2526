#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include <cmath>

class Sine
{
public:
  Sine(float frequency, float samplerate = 44100);
  ~Sine();
  void setSamplerate(float samplerate);
  //return current sample
  float getSample();
  //next sample
  void tick();

  void setFrequency(float frequency);
  float getFrequency();




private:
  const float pi = acos (-1);
  float samplerate;
  float sample;
  float frequency;
  float amplitude;
  float phase;
};

#endif
