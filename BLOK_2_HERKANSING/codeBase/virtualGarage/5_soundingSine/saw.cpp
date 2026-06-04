#include "saw.h"
#include "math.h"

Saw::Saw(float frequency, float samplerate) : frequency(frequency),
  amplitude(1.0), phase(0), sample(0), samplerate(samplerate)
{
  std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
  std::cout << "Saw - destructor\n";
}

void Saw::setSamplerate(float samplerate) {
  this->samplerate =samplerate;
}

float Saw::getSample() {
  return sample;
}

void Saw::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  sample = phase*2.0-1.0;
}

//getters and setters
void Saw::setFrequency(float frequency)
{
  // TODO add check to see if parameter is valid
  this->frequency = frequency;
}

float Saw::getFrequency()
{
  return frequency;
}
