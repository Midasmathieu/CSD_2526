#ifndef ADDITIVESYNTH_H
#define ADDITIVESYNTH_H

#include "sine.h"
#include "melody.h"

class AdditiveSynth {
public:
  AdditiveSynth();
  void setFrequencys();
  void tickAll();
  void calculateAll();
  int getSample();
  void setFrequency2();
};


#endif
