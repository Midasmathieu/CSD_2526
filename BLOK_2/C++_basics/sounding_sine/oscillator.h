#ifndef _Oscillator_H_
#define _Oscillator_H_
#include <iostream>


class Oscillator {
public:
  Oscillator();
  Oscillator(float frequency, float samplerate = 44100);
  ~Oscillator();

  void setSamplerate(float samplerate);

  float getSample();

  void setFrequency(float frequency);
  float getFrequency();

  void tick();

protected:
  virtual void calculate() = 0;
  const float pi = acos (-1);
  float frequency;
  float amplitude { 1.0f };
  float phase;
  float sample;
  float samplerate;
};

#endif
