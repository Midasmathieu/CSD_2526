#include <iostream>
#ifndef _ENVELOPE_H_
#define _ENVELOPE_H_

class Envelope 
{
 public:
  Envelope(float attackMs, float decayMs,
           float sustainPct, float releaseMs);

  Envelope(float init, float attackMs, float decayMs,
           float sustainPct, float releaseMs);
  ~Envelope();
  void prepare(int sampleRate);
  float calculateMsToBuf(float number);
  void setAttack(float attackMs);
  void setDecay(float decayMs);
  void setSustain(int sustainPct);
  void setRelease(float releaseMs);
  void setInit(float initPct);
  void tick(bool noteOnOff);
  float getAmplitude();

 private:
  void allocateEnvelope();
  void releaseEnvelope();
  void createEnvelope();
  float mapLin(float normVal, float low, float high);
  
  float buffIndex = 0;
  int m_sampleRate = 48000;
  float m_attackMs = 50;
  float m_decayMs = 200;
  int m_sustainPct = 70;
  float m_releaseMs = 200;
  int m_initPct = 0;
  int m_attackSamples = 100;
  int m_decaySamples = 50;
  float m_sustainAmp = 0.5f;
  int m_releaseSamples = 200;
  float m_init = 0.0f;
  float m_peak = 1.0f;
  float m_end = 0.0f;
  float m_millisToBuf = 1024.0f/6000.0f;
  float scale = 1024.0f / (m_sampleRate * 6);
  bool m_noteOnOff;
  bool m_prevNoteOnOff = 1;
   
  float* m_envelope;
  float* m_envelopeRelease;
};

#endif
