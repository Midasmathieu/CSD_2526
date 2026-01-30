#ifndef _Sine_H_
#define _Sine_H_
#include "oscillator.h"

class Sine : public Oscillator {
public:
  Sine (float frequency = 0, float samplerate = 44100);

protected:
  void calculate();
};

#endif
