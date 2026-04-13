#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
#include "effect.h"


#include <iostream>
#include <cstring>

class CircularBuffer : public Effect
{
 public:
  CircularBuffer();
  ~CircularBuffer();
  void applyEffect(const float& input, float& output);
  void resetSize(int size);
  void prepare(float samplerate);
  void setDistanceRW(int distanceRW);
  void setGrainSize(int grainSize);
  void generateEnvelope();
  void setGrainReadDestination(int parameterGrainSize);


 private:
  void calculateReadH(float& phase, int& head);
  void incrWriteH();
  void incrPhase(float& phase);
  void wrapH(int& head);
  void write(float input);
  void m_calculatePhaseStep();
  void smoothGrain();
  void allocateBuffer();
  void releaseBuffer();
  void tick();

  float calculateAmp(float phase);
  float read();

  int m_size = 48000;
  int m_readH;
  int m_readH2 = 0;
  int m_writeH = 0;
  int m_distanceRW = 0;
  int m_timer = { 0 };
  bool move = false;
  int incrValue = 0;
  int m_grainSize = 24000;
  int m_tempGrainSize = m_grainSize;
  float m_headPhase = 0.0;
  float m_headPhase2 = 0.5f;
  float m_grainPhase = 0.0f;
  float stepValue;
  int m_difference = 0;
  int m_sampleRate;
  float m_phaseStep;
  float* m_buffer;
  float* m_envelope;
};


#endif
