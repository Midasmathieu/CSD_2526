#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <iostream>
#include <cstring>

class CircularBuffer {
public:
  CircularBuffer() {
    std::cout << "Buffer constructor" << std::endl;
    allocateBuffer();
  }

  ~CircularBuffer() {
    std::cout << "Buffer destructor" << std::endl;
    releaseBuffer();
  }


  void allocateBuffer() {
    m_buffer = (float*)malloc(m_size * sizeof(float));
    memset(m_buffer, 0, m_size * sizeof(float));
  }

  void releaseBuffer() {
    free(m_buffer);
  }

  inline void tick() {
    calculateReadH();
    incrWriteH();
    // std::cout << "test" << std::endl;
    incrPhase();
    // std::cout << m_headPhase << std::endl;
    // readH0.incrH();
  }

  inline float read() {
    return m_buffer[m_readH];
    std::cout << "read\n";

  }

  inline void write(float input) {
    m_buffer[m_writeH] = input;
    // std::cout << "write\n";
  }

  void resetSize(unsigned int size) {
    m_size = size - sizeof(float);
    // readH0.setSize(m_size);
    releaseBuffer();
    allocateBuffer();
    std::cout << m_size << std::endl;
  }

  void setDistanceRW(unsigned int distanceRW) {
    m_distanceRW = distanceRW;
    // m_readH = m_writeH - m_distanceRW + m_size;
    // wrapH(m_readH);
    std::cout << "setDistanceRW\n";
  }

  float getDistanceRW() {
    return m_distanceRW;
  }

  void m_calculatePhaseStep() {
    // m_phaseStep = 1.0/(static_cast<float>(m_sampleRate) * static_cast<float>(m_phaseDurMillis));
    m_phaseStep = 1.0/static_cast<float>(m_phaseDur);

    std::cout << "goyly shit we got phaseStep:  " << m_phaseStep << std::endl;
  }

  void setGrainSize(int grainsize){
    m_grainSize = grainsize;
  }

private:

  inline void calculateReadH() {
    float backward = m_headPhase * static_cast<float>(m_grainSize)*2;
    // m_readH = m_writeH - static_cast<int>(backward);
    int m_intReadH = static_cast<int>(m_writeH) - static_cast<int>(m_distanceRW) - static_cast<int>(backward);
    // std::cout << "reqad head prev wrap: " << m_readH << "headPhase : " << m_headPhase << std::endl;
    revWrapH(m_intReadH);
    m_readH = static_cast<unsigned int>(m_intReadH);
    wrapH(m_readH);
    // std::cout << "backward: " << backward << "    head: " << m_readH << std::endl;
    std::cout << "reqad head: " <<  m_readH << std::endl; //" m_distanceRW:  " << m_distanceRW << "backward:    "  << backward << std::endl;
  }

  inline void incrWriteH() {
    m_writeH++;
    wrapH(m_writeH);
    std::cout << "writhead :  " << m_writeH << std:: endl;
  }

  inline void incrPhase() {
    m_headPhase += m_phaseStep;
    if(m_headPhase > 1.0) { m_headPhase -= 1.0; std::cout << "phasereset" << std::endl;}
    // std::cout << m_headPhase << std::endl;
  }

  inline void wrapH(unsigned int& head) {
    if (head > m_size) { head -= m_size;
    std::cout << " here we go: wrap: " << head << std::endl; }
  }

  inline void revWrapH(int& head) {
    if (head < 0) { head = head + m_size; std::cout << "wrapreverse\n";}
  }


  // ReadH readH0;
  unsigned int m_size = 48000;
  unsigned int m_readH;
  unsigned int m_writeH = 0;
  unsigned int m_distanceRW;
  unsigned int m_timer = { 0 };
  int m_grainSize =  48000;
  int m_phaseDur = 48000;
  float m_headPhase = 0.0;
  int m_sampleRate = 48000;
  float m_phaseStep; //= 1/(m_sampleRate * m_grainSize);
  float* m_buffer;

};


#endif
