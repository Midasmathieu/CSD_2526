#include "synth.h"
#include <cmath>
#include <iostream>
Synth::Synth()
{
  std::cout << "Synth constructor" << std::endl;
}

Synth::~Synth() 
{
  std::cout << "Synth destructor" << std::endl;
}

float Synth::mtof(float midiNote)
{
  float power = (midiNote - 69)/12;
  float frequency = 440 * pow(2, power);
  return frequency;
}
