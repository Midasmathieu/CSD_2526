#include "saw.h"
#include "math.h"

Saw::Saw() : amplitude(1.0), sample(0)
{
  std::cout << "Saw - constructor\n";
}

Saw::~Saw() {
  std::cout << "Saw - destructor\n";
}

float Saw::getSample() {
  return sample;
}

void Saw::calculateSample() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  sample = phase*2.0-1.0;
}

//getters and setters
//void Saw::setFrequency(float frequency)
//{
//  // TODO add check to see if parameter is valid
//  this->frequency = frequency;
//}

//float Saw::getFrequency()
//{
//  return frequency;
//}
