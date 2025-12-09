#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate) : frequency(frequency),
  amplitude(1.0), phase(0), sample(0), samplerate(samplerate)
{
  std::cout << "sine constructor\n";
}

Sine::~Sine(){
  std::cout << "fuck that sine\n";
}

void Sine::setSamplerate(float samplerate){
  this->samplerate = samplerate;
}

float Sine::getSample(){
  return sample;
}

void Sine::tick() {
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  sample = sin(pi * 2 * phase) * amplitude;
}

void Sine::setFrequency(float frequency)
{
  this->frequency = frequency;
}

float Sine::getFrequency(){
  return frequency;
}
