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

void CircularBuffer::applyEffect(const float& input, float& output)
{
  write(input);
  output = read();
  tick();
  smoothGrain();
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
  calculateReadH(m_headPhase, m_readH);
  calculateReadH(m_headPhase2, m_readH2);
  incrWriteH();
  incrPhase(m_headPhase);
  incrPhase(m_headPhase2);
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
}


void CircularBuffer::m_calculatePhaseStep()
{
  m_phaseStep = 1.0/static_cast<float>(m_grainSize);
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
  }

  for (int i = 0; i < 512; i++) {
    int j = i + 512;
    float attack  = i * rc;
    float release = i * -rc + 1.0;
    m_envelope[i] = attack;
    m_envelope[j] = release;
  }
  for (int i = 0; i < 1025; i++) {
  }
}

float CircularBuffer::calculateAmp(float phase)
{
  int index =  phase * 1024;
  return m_envelope[index];
}


void CircularBuffer::calculateGrainStep(int parameter)
{
  difference = parameter - m_grainSize;
  stepValue = 0.00005;
  m_tempGrainSize = m_grainSize;
  m_grainPhase = 0;
  move = true;
}

void CircularBuffer::smoothGrain()
{
  if (move) {
    m_grainPhase += stepValue;
    m_grainSize = m_tempGrainSize + m_grainPhase * difference;
    m_calculatePhaseStep();
    if (m_grainPhase >= 1.0) {
      m_grainPhase = 0;
      move = false;
    }
  }
}

void CircularBuffer::incrGrainPhase(float& phase, float stepValue)
{
  phase += stepValue;
}

void CircularBuffer::calculateReadH(float& phase, int& head)
{
  float backward  = phase * static_cast<float>(m_grainSize)*2;
  head  = m_writeH - m_distanceRW - (float) backward;
  wrapH(head);
}

void CircularBuffer::incrWriteH()
{
  m_writeH++;
  wrapH(m_writeH);
}

void CircularBuffer::incrPhase(float& phase)
{
  phase  += m_phaseStep;
  if (phase  > 1.0) { phase  -= 1.0; }
}

void CircularBuffer::wrapH(int& head)
{
  if (head > m_size) { head -= m_size; }
  else if (head < 0) { head += m_size; }
}
