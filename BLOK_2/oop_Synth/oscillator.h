#ifndef _Oscillator_H_
#define _Oscillator_H_
#include <iostream>

class Oscillator {
public:
  Oscillator(float frequency, float samplerate);
  ~Oscillator();
  void setSamplerate();
  float getFrequency();
  float getSample();
  void setFrequency();
  void tick();


protected:
  virtual void calculate() = 0;
  float frequency;
  float sample;
  float samplerate;
  float phase;
  float amplitude { 0.25f };
};

#endif
