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

void CircularBuffer::prepare(float samplerate) {
  m_sampleRate = samplerate;
}

// applies effect
void CircularBuffer::applyEffect(const float& input, float& output)
{
  write(input);
  output = read();
  tick();
  smoothGrain();
}

// allocates buffer in memory
void CircularBuffer::allocateBuffer()
{
  m_buffer = (float*)malloc(m_size * sizeof(float));
  memset(m_buffer, 0, m_size * sizeof(float));
  std::cout << " allocate buffer \n";
}

// releases memory reserved for buffer
void CircularBuffer::releaseBuffer()
{
  std::cout << " release buffer \n";
  free(m_buffer);
}

// ticks writeH and readH every samplerate
void CircularBuffer::tick()
{
  calculateReadH(m_headPhase, m_readH);
  calculateReadH(m_headPhase2, m_readH2);
  incrWriteH();
  incrPhase(m_headPhase);
  incrPhase(m_headPhase2);
}

//applies envelopes on readheads, adds them and returns it.
float CircularBuffer::read()
{
  return m_buffer[m_readH] * calculateAmp(m_headPhase) + m_buffer[m_readH2] * calculateAmp(m_headPhase2);
}

//writes input in buffer
void CircularBuffer::write(float input)
{
  m_buffer[m_writeH] = input;
}


void CircularBuffer::resetSize(int size)
{
  // makes shure buffer is not longer than 10 seconds
  if(size < 0 || size > 10*m_sampleRate) {
    throw "CircularBuffer::resetSize - size value is not in range [0, 480000]";
  }
  m_size = size - sizeof(float);
  releaseBuffer();
  allocateBuffer();
}


void CircularBuffer::setDistanceRW(int distanceRW)
{
  if(distanceRW < 0 || distanceRW > m_size) {
    throw "CircularBuffer::setDistanceRW - distanceRW value is not in range [0, m_size]";
  }
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

// makes an envelope for the amplitude and saves it in a buffer (ramp up and down)
void CircularBuffer::generateEnvelope()
{
  std::cout << "making envelope..." << std::endl;
  m_envelope = (float*)malloc(1024 * sizeof(float));
  int rampTime = 512;
  float rc = 1.0/rampTime;

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

// cycles through envelope for the amplitude of the two delay grains (windowing)
float CircularBuffer::calculateAmp(float phase)
{
  int index =  phase * 1024;
  return m_envelope[index];
}


// calculates the values to smoothly move to new read destination
void CircularBuffer::setGrainReadDestination(int parameter)
{
  if(parameter < 0 || parameter > m_size) {
    throw "CircularBuffer::setDistanceRW - distanceRW value is not in range [0, m_size]";
  }
  m_difference = parameter - m_grainSize;
  stepValue = 0.00005;
  m_tempGrainSize = m_grainSize;
  m_grainPhase = 0;
  move = true;
}

// smoothly moves to new read destination
void CircularBuffer::smoothGrain()
{
  if (move) {
    m_grainPhase += stepValue;
    m_grainSize = m_tempGrainSize + m_grainPhase * m_difference;
    m_calculatePhaseStep();
    if (m_grainPhase >= 1.0) {
      m_grainPhase = 0;
      move = false;
    }
  }
}

// calculates position for head given to method
void CircularBuffer::calculateReadH(float& phase, int& head)
{
  float backward  = phase * static_cast<float>(m_grainSize)*2;
  head  = m_writeH - m_distanceRW - (float) backward;
  wrapH(head);
}

// increments writeH
void CircularBuffer::incrWriteH()
{
  m_writeH++;
  wrapH(m_writeH);
}

// increments phase
void CircularBuffer::incrPhase(float& phase)
{
  phase  += m_phaseStep;
  if (phase  > 1.0) { phase  -= 1.0; }
}

// wraps values given to method to make shure heads stay in buffer
void CircularBuffer::wrapH(int& head)
{
  if (head > m_size) { head -= m_size; }
  else if (head < 0) { head += m_size; }
}
