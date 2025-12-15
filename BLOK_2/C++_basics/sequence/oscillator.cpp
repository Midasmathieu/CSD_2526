#include "oscillator.h"
#include "math.h"

Oscillator::Oscillator(){}

Oscillator::Oscillator (float frequency, float samplerate)
  : frequency(frequency),
    amplitude(1.0f),
    phase(0),
    sample(0),
    samplerate(samplerate) {
  std::cout << "oscillator just got completely constructed\n";
    }

Oscillator::~Oscillator(){
  std::cout << "yeah fuck that oscillator\n";
}

void Oscillator::setSamplerate(float samplerate){
  this->samplerate = samplerate;
}

float Oscillator::getSample(){
  // std::cout << sample;
  return sample;
}

void Oscillator::setFrequency(float frequency){
  this->frequency = frequency;
}

float Oscillator::getFrequency(){
  return frequency;
}

void Oscillator::tick(){
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
}
