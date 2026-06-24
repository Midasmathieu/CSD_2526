#ifndef _LEADSYNTH_H_
#define _LEADSYNTH_H_
#include "oscillator.h"
#include "saw.h"
#include "synth.h"
#include "envelope.h"
#include <iostream>

class LeadSynth : public Synth
{
 public:
  LeadSynth();
  ~LeadSynth();
  Saw sawKick;
  float proccesKick();
  void setFrequency(float frequency);
  //Envelope pitchEnv {5, 500, 0, 1};
  Envelope volEnv {150, 300, 70, 300};
  bool setNoteOnOff(bool noteOnOff);
  bool m_noteOnOff = 0;
  float m_freqMod;
};


#endif
