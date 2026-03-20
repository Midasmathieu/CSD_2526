#include "CircularBuffer.h"
#include <iostream>
#include <cstring>
#define EPSILON 0.000001



CircularBuffer::CircularBuffer()
{
  std::cout << "Buffer constructor" << std::endl;
  allocateBuffer();
  m_grainSize.jumpToValue(24000);
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

void CircularBuffer::resetSize(int size)
{
  m_size = size - sizeof(float);
  releaseBuffer();
  allocateBuffer();
}

void CircularBuffer::setDistanceRW(int distanceRW)
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
  float tempGrainSize = getGrainSize();
  std::cout << getGrainSize() << std::endl;
  m_phaseStep = 1.0/static_cast<float>(tempGrainSize);
  std::cout << "goyly shit we got phaseStep:  " << m_phaseStep << std::endl;
}

// void CircularBuffer::setGrainSize(int grainSize)
// {
//   m_grainSize = grainSize;
//   m_calculatePhaseStep();
// }
float CircularBuffer::getGrainSize()
{
  return m_grainSize.getValue();
}

// void CircularBuffer::setGrainSize(float m_grainSize, bool interpolateChange)
// {
//   std::cout << "ChangeableDelay.setGrainSize, new m_grainSize: " << m_grainSize << std::endl;
//   setActualGrainSize(m_grainSize);
// }

void CircularBuffer::setGrainSize(float grainSize, bool interpolateChange)
{
  // if new  new distance between R & W heads and update rhead position
  if (grainSize < m_grainSize.getValue() - EPSILON ||
      grainSize > m_grainSize.getValue() + EPSILON)
  {
    // validate new num delay samples
    if (grainSize > 0 && grainSize <= m_size) {
      std::cout << "ChangeableDelay::m_grainSize - setting new grainsize: "<< grainSize << std::endl;
      std::cout << "ChangeableDelay::m_grainSize - interpolateChange: "<< interpolateChange << std::endl;
      if (interpolateChange) {
        m_grainSize.moveToValue(grainSize, 1.0f);
        m_calculatePhaseStep();
        std::cout << "ChangeableDelay::m_grainSize - calling moveToValue" << std::endl;
      } else {
        m_grainSize.jumpToValue(grainSize);
        m_calculatePhaseStep();
      }
    } else {
      throw "ChangeableDelay::m_grainSize - grainSize is out of range";
    }
  }
}

void CircularBuffer::generateEnvelope()
{
  std::cout << "making envelope..." << std::endl;
  m_envelope = (float*)malloc(1024 * sizeof(float));
  int rampTime = 512;
  float rc = 1.0/rampTime;
  for (int i = 0; i < 1025; i++) {
    std::cout << "envelp " << i << ": " << m_envelope[i] << std::endl;
  }

  for (int i = 0; i < 512; i++) {
    int j = i + 512;
    float attack  = i * rc;
    float release = i * -rc + 1.0;
    m_envelope[i] = attack;
    m_envelope[j] = release;
  }
  for (int i = 0; i < 1025; i++) {
    std::cout << "envelp " << i << ": " << m_envelope[i] << std::endl;
  }
}

float CircularBuffer::calculateAmp(float phase)
{
  int index =  phase * 1024;
  return m_envelope[index];
}

void CircularBuffer::calculateReadH()
{
  float backward  = m_headPhase * static_cast<float>(getGrainSize())*2;
  float backward2 = m_headPhase2 * static_cast<float>(getGrainSize())*2;
  m_readH  = m_writeH - m_distanceRW - backward;
  m_readH2 = m_writeH - m_distanceRW - backward2;
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

void CircularBuffer::wrapH(int& head)
{
  if (head > m_size) { head -= m_size; }
  else if (head < 0) { head += m_size; //std::cout << "minuminus" << head;
  }
}

// void CircularBuffer::revWrapH(int& head)
// {
//    if (head < 0) { head = head + m_size; // std::cout << "wrapreverse\n";
//    }
// }
