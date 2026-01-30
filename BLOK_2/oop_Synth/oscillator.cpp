#include "oscillator.h"
#include "math.h"

//overloaded constructor:
Oscillator::Oscillator(float frequency, float samplerate)
  : frequency (frequency),
    amplitude (0.25f),
    phase (0),
    sample (0),
    samplerate(samplerate) {
  std::cout << "Oscillator constructor" << std::endl;
}

Oscillator::~Oscillator(){
  std::cout << "Oscillator destructor" << std::endl;
}

float Oscillator::getFrequency() { return frequency; }

float Oscillator::getSample() { return sample; }

void Oscillator::setSamplerate() {
  this->samplerate = samplerate;
}

void Oscillator::setFrequency() {
  this ->frequency = frequency;
}

void Oscillator::tick() {
  phase += frequency / samplerate;
  if (phase > 1) { phase -= 1.0f;}

  calculate();
}
