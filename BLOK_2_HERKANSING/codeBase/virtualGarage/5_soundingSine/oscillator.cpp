#include "oscillator.h"

Oscillator::Oscillator()
{
  std::cout << "Oscillator constructor" << std::endl;
}

Oscillator::~Oscillator()
{
  std::cout << "Oscillator destructor" << std::endl;
}

void Oscillator::tick()
{
  phase += frequency / samplerate;
  if(phase >= 1.0f) 
  { 
    phase -= 1.0f;
    void calculateSample();
    //std::cout << "tick";
    //TODO: let tick of oscillator call calculate sample of child class
  }
}

void Oscillator::setFrequency(float frequency)
{
  this->frequency = frequency;
}

void Oscillator::setSamplerate(float samplerate)
{
  this->samplerate = samplerate;
}

