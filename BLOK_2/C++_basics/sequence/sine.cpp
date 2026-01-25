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



void Sine::calculate(){
  sample = sin(pi * 2 * phase) * amplitude;
}
