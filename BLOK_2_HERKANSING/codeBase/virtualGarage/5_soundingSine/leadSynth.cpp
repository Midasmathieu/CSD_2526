#include "leadSynth.h"
LeadSynth::LeadSynth()
{
  std::cout << "LeadSynth constructor" << std::endl;
  sawKick.setFrequency(50.0f);
}

LeadSynth::~LeadSynth()
{
  std::cout << "LeadSynth destructor" << std::endl;
}

float LeadSynth::proccesKick()
{
  sawKick.tick();
  sawKick.calculateSample();
  volEnv.tick(m_noteOnOff);
  // pitchEnv.tick(m_noteOnOff);
  float amp = volEnv.getAmplitude();
  // m_freqMod = pitchEnv.getAmplitude();
  return sawKick.getSample() * amp;
}

void LeadSynth::setFrequency(float frequency)
{
  int kickFreq = frequency *2  + 500.0f * m_freqMod * frequency;
  //std::cout << kickFreq << std::endl;
  sawKick.setFrequency(frequency);
}

bool LeadSynth::setNoteOnOff(bool noteOnOff)
{
  m_noteOnOff = noteOnOff;
}
