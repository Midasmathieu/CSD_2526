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
    incrReadH();
    incrWriteH();
    // std::cout << "test" << std::endl;
    incrTimer();
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
    releaseBuffer();
    allocateBuffer();
    std::cout << m_size << std::endl;
  }

  void setDistanceRW(unsigned int distanceRW) {
    m_distanceRW = distanceRW;
    m_readH = m_writeH - m_distanceRW + m_size;
    wrapH(m_readH);
    std::cout << "setDistanceRW\n";
  }

  float getDistanceRW() {
    return m_distanceRW;
  }


private:
  inline void incrReadH() {
    m_readH--;
    wrapH(m_readH);
    revWrapH(m_readH);
    // std::cout << "readH: " << m_readH << std::endl;
  }

  inline void incrWriteH() {
    m_writeH++;
    wrapH(m_writeH);
  }

  inline void incrTimer() {
    m_timer++;
    if(m_timer >= m_distanceRW){
      m_timer = m_timer - m_distanceRW;
      m_readH = m_readH + m_distanceRW * 2;
      wrapH(m_readH);
      revWrapH(m_readH);
    }
  }


  inline void wrapH(unsigned int& head) {
    if (head >= m_size) { head = head - m_size;
    std::cout << " here we go: wrap\n"; }
  }

  inline void revWrapH(unsigned int& head) {
    if (head <= 0) { head = head + m_size; std::cout << "wrapreverse\n";}
  }

  unsigned int m_size = 48000;
  unsigned int m_readH;
  unsigned int m_writeH;
  unsigned int m_distanceRW;
  unsigned int m_timer = { 0 };
  float* m_buffer;


};


#endif
