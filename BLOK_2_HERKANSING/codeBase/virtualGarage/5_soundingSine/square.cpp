#include "square.h"
#include "math.h"

Square::Square(float frequency, float samplerate) : frequency(frequency),
  amplitude(1.0), phase(0), sample(0), samplerate(samplerate)
{
  std::cout << "Square - constructor\n";
}

Square::~Square() {
  std::cout << "Square - destructor\n";
}

void Square::setSamplerate(float samplerate) {
  this->samplerate =samplerate;
}

float Square::getSample() {
  return sample;
}

void Square::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  if(phase >= 0.5)  {sample = -1;} else {sample = 1;}
}

//getters and setters
void Square::setFrequency(float frequency)
{
  // TODO add check to see if parameter is valid
  this->frequency = frequency;
}

float Square::getFrequency()
{
  return frequency;
}
