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
  volEnv.tick(m_noteOnOff);
  pitchEnv.tick(m_noteOnOff);
  float amp = volEnv.getAmplitude();
  m_freqMod = pitchEnv.getAmplitude();
  return sawKick.getSample() * amp;
}

void KickSynth::setFrequency(float frequency)
{
  int kickFreq = frequency + 500.0f * m_freqMod * frequency;
  //std::cout << kickFreq << std::endl;
  sawKick.setFrequency(kickFreq);
}

bool KickSynth::setNoteOnOff(bool noteOnOff)
{
  m_noteOnOff = noteOnOff;
}
