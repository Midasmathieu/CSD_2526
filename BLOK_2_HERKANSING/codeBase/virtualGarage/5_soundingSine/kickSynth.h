#ifndef _KICKSYNTH_H_
#define _KICKSYNTH_H_
#include "oscillator.h"
#include "saw.h"
#include "synth.h"
#include "envelope.h"
#include <iostream>

class KickSynth : public Synth
{
 public:
  KickSynth();
  ~KickSynth();
  Saw sawKick;
  float proccesKick();
  void setFrequency(float frequency);
//  Envelope envelope;
};


#endif
