#include <iostream>
#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

class Envelope 
{
 public:
  Envelope();
  ~Envelope();
  void setAttack(float attackMs);
  void setDecay(float decayMs);
  void setSustain(int sustainPct);
  void setRelease(float releaseMs);
  void tick(bool noteOnOff);
  float getAmplitude();

 private:
  void allocateEnvelope();
  void releaseEnvelope();
  void createEnvelope();
  
  float phase = 0;
  int sampleRate = 48000;

  float m_attackMs = 50;
  float m_decayMs = 200;
  int m_sustainPct = 70;
  float m_releaseMs = 200;
  int m_attackSamples = 511;
  int m_decaySamples = 5;
  float m_sustainAmp = 0.5f;
  int m_releaseSamples = 511;
  float m_init = 0.0f;
  float m_peak = 1.0f;
  float m_end = 0.0f;
  float m_millisToBuf = 1024.0f/6000.0f;
  float scale = 1024.0f / (sampleRate * 6);
  bool m_noteOnOff;
  bool m_prevNoteOnOff = 1;
  
  
  float* m_envelope;
  float* m_envelopeRelease;
};

#endif
