#include "kickSynth.h"
KickSynth::KickSynth()
{
  std::cout << "KickSynth constructor" << std::endl;
  sawKick.setFrequency(50.0f);
}

KickSynth::~KickSynth()
{
  std::cout << "KickSynth destructor" << std::endl;
}

float KickSynth::proccesKick()
{
  sawKick.tick();
  sawKick.calculateSample();
  return sawKick.getSample();
}

void KickSynth::setFrequency(float frequency)
{
  sawKick.setFrequency(frequency);
}
