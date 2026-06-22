#include "sine.h"
#include "square.h"
#include "saw.h"
#include <iostream>
#ifndef _SYNTH_H_
#define _SYNTH_H_

class Synth 
{
 public:
  Synth();
  ~Synth();
  float mtof(float midiNote);
};

#endif
