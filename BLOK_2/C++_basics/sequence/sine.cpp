#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate)
: Oscillator(frequency, samplerate)
 // phase(0), sample(0), samplerate(samplerate)
{
  std::cout << "sine constructor\n";
}

Sine::~Sine(){
  std::cout << "fuck that sine\n";
}

// void Sine::print(){
//   std::cout << "frequency: " << frequency << std::endl;
// }

// void Sine::setSamplerate(float samplerate){
//   this->samplerate = samplerate;
// }
//
// float Sine::getSample(){
//   return sample;
// }
//
// void Sine::tick() {
//   phase += frequency / samplerate;
//   if(phase > 1.0f) {
//     phase -= 1.0f;
//   }
// }

void Sine::calculate(){
  sample = sin(pi * 2 * phase) * amplitude;
}

// void Sine::setFrequency(float frequency)
// {
//   this->frequency = frequency;
// }
//
// float Sine::getFrequency(){
//   return frequency;
// }
