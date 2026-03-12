#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <iostream>
#include <cstring>

class CircularBuffer {
public:
  CircularBuffer() {
    std::cout << "Buffer constructor" << std::endl;
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
    m_size = size;
    releaseBuffer();
    allocateBuffer();
    // std::cout << "resetSize\n";
  }

  void setDistanceRW(unsigned int distanceRW) {
    m_distanceRW = distanceRW;
    m_readH = m_writeH - distanceRW + m_size;
    wrapH(m_readH);
    std::cout << "setDistanceRW\n";

  }

  float getDistanceRW() {
    return m_distanceRW;
  }


private:
  inline void incrReadH() {
    m_readH++;
    wrapH(m_readH);
    // std::cout << m_buffer[m_readH] << std::endl;
  }

  inline void incrWriteH() {
    m_writeH++;
    wrapH(m_writeH);
  }

  inline void wrapH(unsigned int& head) {
    if (head >= m_size) { head -= m_size; }
  }

  float* m_buffer;
  unsigned int m_size;
  unsigned int m_readH;
  unsigned int m_writeH;
  unsigned int m_distanceRW;
};


#endif
