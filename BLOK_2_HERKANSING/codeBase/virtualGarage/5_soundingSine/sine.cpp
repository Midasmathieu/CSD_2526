#include "sine.h"
#include "math.h"

Sine::Sine() : amplitude(1.0), sample(0)
{
  std::cout << "Sine - constructor\n";
}

Sine::~Sine() 
{
  std::cout << "Sine - destructor\n";
}

float Sine::getSample()
{
  return sample;
}

void Sine::calculateSample() {
  sample = sin(pi * 2 * phase) * amplitude;
}
