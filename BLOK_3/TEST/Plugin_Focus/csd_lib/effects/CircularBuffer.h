#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H


#include <iostream>
#include <cstring>

class CircularBuffer {
 public:
  CircularBuffer();
  ~CircularBuffer();

  void allocateBuffer();

  void releaseBuffer();

  void tick();

  float read();

  void write(float input);

  void resetSize( int size);

  void setDistanceRW( int distanceRW);

  float getDistanceRW();

  void m_calculatePhaseStep();

  void setGrainSize(int grainSize);

  void generateEnvelope();

  float calculateAmp(float phase);

  void smoothGrain();

  void calculateGrainStep(int parameterGrainSize);

 private:
  void calculateReadH();
  void incrWriteH();
  void incrPhase();
  void wrapH(int& head);
  // void revWrapH(int& head);

  int m_size = 48000;
  int m_readH;
  int m_readH2;
  int m_writeH = 0;
  int m_distanceRW = 0;
  int m_timer = { 0 };
  bool move = false;
  int incrValue = 0;
  int parameterGrainSize;
  // int m_parameterGrainSize;
  int m_grainSize =  48000;
  float m_headPhase = 0.0;
  float m_headPhase2 = 0.5f;
  int m_sampleRate = 48000;
  float m_phaseStep; //= 1/(m_sampleRate * m_grainSize);
  float* m_buffer;
  float* m_envelope;
};


#endif
