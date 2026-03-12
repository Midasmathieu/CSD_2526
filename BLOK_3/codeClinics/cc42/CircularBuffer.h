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
  }

  inline float read() {
    return m_buffer[m_readH];
  }

  void resetSize(unsigned int size) {
    m_size = size;
    releaseBuffer();
    allocateBuffer();
  }


private:

  inline void incrReadH() {
    m_readH++;
    wrapH(m_readH);
  }

  inline void wrapH(unsigned int& head) {
    if (head >= m_size) { head -= m_size; std::cout << head << std::endl; }
  }

  float* m_buffer;
  unsigned int m_size = 48000;
  unsigned int m_readH;
  // unsigned int m_writeH;
};


#endif
