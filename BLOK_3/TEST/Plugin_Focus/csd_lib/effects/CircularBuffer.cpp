#include "CircularBuffer.h"
#include <iostream>
#include <cstring>


CircularBuffer::CircularBuffer()
{
  std::cout << "Buffer constructor" << std::endl;
  allocateBuffer();
}

CircularBuffer::~CircularBuffer()
{
  std::cout << "buffer destructor" << std::endl;
  releaseBuffer();
}

void CircularBuffer::allocateBuffer()
{
  m_buffer = (float*)malloc(m_size * sizeof(float));
  memset(m_buffer, 0, m_size * sizeof(float));
  std::cout << " allocate buffer \n";
}

void CircularBuffer::releaseBuffer()
{
  std::cout << " release buffer \n";
  free(m_buffer);
}

void CircularBuffer::tick()
{
  calculateReadH();
  incrWriteH();
  incrPhase();
}

float CircularBuffer::read()
{
  return m_buffer[m_readH] * calculateAmp(m_headPhase) + m_buffer[m_readH2] * calculateAmp(m_headPhase2);
  std::cout << "readH2:  " << m_readH2 << std::endl;
  std::cout << "read\n";
}

void CircularBuffer::write(float input)
{
  m_buffer[m_writeH] = input;
}

void CircularBuffer::resetSize(unsigned int size)
{
  m_size = size - sizeof(float);
  releaseBuffer();
  allocateBuffer();
}

void CircularBuffer::setDistanceRW(unsigned int distanceRW)
{
  m_distanceRW = distanceRW;
  std::cout << "setDistanceRW\n";
}

float CircularBuffer::getDistanceRW()
{
  return m_distanceRW;
}

void CircularBuffer::m_calculatePhaseStep()
{
  m_phaseStep = 1.0/static_cast<float>(m_phaseDur);
  std::cout << "goyly shit we got phaseStep:  " << m_phaseStep << std::endl;
}

void CircularBuffer::setGrainSize(int grainSize)
{
  m_grainSize = grainSize;
}

void CircularBuffer::generateEnvelope()
{
  std::cout << "making envelope..." << std::endl;
  m_envelope = (float*)malloc(1024 * sizeof(float));
  memset(m_envelope, 0, sizeof(float)*1024);
  int rampTime = 512;
  float rc = 1.0/rampTime;

  for (int i = 0; i < 512; i++) {
    int j = i + 512;
    float attack  = i * rc;
    float release = i * -rc + 1.0;
    m_envelope[i] = attack;
    m_envelope[j] = release;
  }
}

float CircularBuffer::calculateAmp(float phase)
{
  int index =  phase * 1024;
  return m_envelope[index];
}

void CircularBuffer::calculateReadH()
{
  float backward  = m_headPhase * static_cast<float>(m_grainSize)*2;
  float backward2 = m_headPhase2 * static_cast<float>(m_grainSize)*2;
  int m_intReadH  = static_cast<int>(m_writeH) - static_cast<int>(m_distanceRW) - static_cast<int>(backward);
  int m_intReadH2 = static_cast<int>(m_writeH) - static_cast<int>(m_distanceRW) - static_cast<int>(backward2);
  revWrapH(m_intReadH);
  revWrapH(m_intReadH2);
  m_readH  = static_cast<unsigned int>(m_intReadH);
  m_readH2 = static_cast<unsigned int>(m_intReadH2);
  wrapH(m_readH);
  wrapH(m_readH2);
}

void CircularBuffer::incrWriteH()
{
  m_writeH++;
  wrapH(m_writeH);
}

void CircularBuffer::incrPhase()
{
  m_headPhase  += m_phaseStep;
  m_headPhase2 += m_phaseStep;
  if (m_headPhase  > 1.0) { m_headPhase  -= 1.0; std::cout << "phasereset"  << std::endl;}
  if (m_headPhase2 > 1.0) { m_headPhase2 -= 1.0; std::cout << "phasereset2" << std::endl;}
}

void CircularBuffer::wrapH(unsigned int& head)
{
  if (head > m_size) { head -= m_size;
  // std::cout << " here we go: wrap: " << head << std::endl;
  }
}

void CircularBuffer::revWrapH(int& head)
{
   if (head < 0) { head = head + m_size; // std::cout << "wrapreverse\n";
   }
}
