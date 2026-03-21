#include "CircularBuffer.h"
#include <iostream>
#include <cstring>
#include <cmath>


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
  m_phaseStep = 1.0/static_cast<float>(m_grainSize);
  // std::cout << "goyly shit we got phaseStep:  " << m_phaseStep << std::endl;
}

void CircularBuffer::setGrainSize(int grainSize)
{
  m_grainSize = grainSize;
  m_calculatePhaseStep();
}

void CircularBuffer::generateEnvelope()
{
  std::cout << "making envelope..." << std::endl;
  m_envelope = (float*)malloc(1024 * sizeof(float));
  int rampTime = 512;
  float rc = 1.0/rampTime;
  for (int i = 0; i < 1025; i++) {
    // std::cout << "envelp " << i << ": " << m_envelope[i] << std::endl;
  }

  for (int i = 0; i < 512; i++) {
    int j = i + 512;
    float attack  = i * rc;
    float release = i * -rc + 1.0;
    m_envelope[i] = attack;
    m_envelope[j] = release;
  }
  for (int i = 0; i < 1025; i++) {
    // std::cout << "envelp " << i << ": " << m_envelope[i] << std::endl;
  }
}

float CircularBuffer::calculateAmp(float phase)
{
  int index =  phase * 1024;
  return m_envelope[index];
}

// void CircularBuffer::calculateGrainStep2(int parameter)
// {
//   parameterGrainSize = parameter;
//   int difference = parameterGrainSize - m_grainSize;
//   incrValue = difference * 0.0005;
//   move = true;
//   std::cout << "incrvalue::: " << incrValue << std:: endl;
// }

void CircularBuffer::calculateGrainStep(int parameter)
{
  // int parameterGrainSize = parameter;
  difference = parameter - m_grainSize;
  stepValue = 1.0/1000.0;
  move = true;
  std::cout << "incrvalue::: " << difference << std:: endl;
}

void CircularBuffer::smoothGrain()
{
  if (move) {
    m_grainPhase += stepValue;
    std::cout << "phaaseee::::: " << m_grainPhase << std::endl;
    // std::cout << "test1";
    m_grainSize += m_grainPhase * difference;
    // std::cout << "test2";
    m_calculatePhaseStep();
    // std::cout << "test3";
    // std::cout << m_grainSize << ", ";

    // std::cout << "absolute::::::::::::: " << variable2 << std::endl;
    if (m_grainPhase >= 1.0) {
      m_grainPhase -= 1.0;
      move = false;
      std::cout << std::endl;
      std::cout << "moved grainSize!!!" << m_grainSize << std::endl << std::endl;
    }
  }
  // setGrainSize(parameterGrainSize);
}

void CircularBuffer::incrGrainPhase(float& phase, float stepValue)
{
  phase += stepValue;
  std::cout << phase << ", ";
}


// void CircularBuffer::smoothGrain2()
// {
//   if (move) {
//     m_grainSize += incrValue;
//     m_calculatePhaseStep();
//     // std::cout << m_grainSize << ", ";
//     int variable1 = parameterGrainSize - m_grainSize;
//     int variable2 = abs(variable1);
//     // std::cout << "absolute::::::::::::: " << variable2 << std::endl;
//     if (variable2 < 10) {
//       move = false;
//       std::cout << "moved grainSize!!!" << m_grainSize << std::endl << std::endl;
//     }
//   }
//   // setGrainSize(parameterGrainSize);
// }


void CircularBuffer::calculateReadH()
{
  float backward  = m_headPhase * static_cast<float>(m_grainSize)*2;
  float backward2 = m_headPhase2 * static_cast<float>(m_grainSize)*2;
  m_readH  = m_writeH - m_distanceRW - backward;
  m_readH2 = m_writeH - m_distanceRW - backward2;
  wrapH(m_readH);
  wrapH(m_readH2);
  std::cout << "readheads: " << m_readH << ", " << m_readH2 << std::endl;
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
  if (m_headPhase  > 1.0) { m_headPhase  -= 1.0; std::cout << "phasereset_________________________________"  << std::endl;}
  if (m_headPhase2 > 1.0) { m_headPhase2 -= 1.0; std::cout << "phasereset2________________________________" << std::endl;}
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
