#include "envelope.h"

Envelope::Envelope()
{
  std::cout << "Envelope constructor" << std::endl;
  allocateEnvelope();
  createEnvelope();
  for(int i = 0; i < 100; i++)
  {
    std::cout << m_envelope[i*10] << std::endl;
  }
}

Envelope::~Envelope()
{
  std::cout << "Envelope constructor" << std::endl;
  releaseEnvelope();
}

void Envelope::setAttack(float attackMs)
{
  m_attackMs = attackMs;
  m_attackSamples = attackMs * 48;
}

void Envelope::setDecay(float decayMs)
{
  m_decayMs = decayMs;
  m_decaySamples = decayMs * 48;
}

void Envelope::setSustain(int sustainPct)
{
  m_sustainPct = sustainPct;
  m_sustainAmp = sustainPct * 0.01;
}

void Envelope::setRelease(float releaseMs)
{
  m_releaseMs = releaseMs;
  m_releaseSamples = releaseMs * 48;
}

void Envelope::allocateEnvelope()
{
  m_envelope = (float*)malloc(1024*sizeof(float)); 
  m_envelopeRelease = (float*)malloc(1024*sizeof(float));
  memset(m_envelope, 0, 1024 * sizeof(float)); 
  memset(m_envelopeRelease, 0, 1024 * sizeof(float));
}

void Envelope::releaseEnvelope()
{
  free(m_envelope);
  free(m_envelopeRelease);
}

//void Envelope::createEnvelope()
//{
//  for(int i = 0; i < 1024; i++)
//  {
//    m_envelope[i] = 0.5;
//  }

//  for(int i = 0; i < 100; i++) 
//  {
//    m_envelope[i] = i * 0.01;
//    int j = i + 100;
//    m_envelope[j] = i * -0.005 + 1;
//  }
//  for(int i = 0; i < 400; i++)
//  {
//    int j = i + 624;
//    m_envelope[j] = 0.5 + i * -0.00125;
//  }
//}

void Envelope::createEnvelope()
{ 
  int attackDecay = m_attackSamples + m_decaySamples;
  float attackRc = (m_peak - m_init) / m_attackSamples;
  float decayRc = (m_sustainAmp - m_peak) / m_decaySamples;
  float releaseRc = (m_end - m_sustainAmp) / m_releaseSamples;
  std::cout << "decay RC: " << decayRc << std::endl;
  for(int i = 0; i < 1024; i++)
  {
    if(i <= m_attackSamples)
    {
      m_envelope[i] = i * attackRc + m_init;
    } else if(i >= m_attackSamples && i <= attackDecay)
    {
      m_envelope[i] = (i - m_attackSamples) * decayRc + m_peak;
    }
    if(i <= m_releaseSamples)
    {
      m_envelopeRelease[i] = i * releaseRc + m_sustainAmp;
    }
  }
}

void Envelope::tick(bool noteOnOff)
{
  if(phase <= m_attackSamples + m_releaseSamples)
  {
    phase += scale;
    if(phase >= 1024)
    {
      phase -= phase;
    }
  }
  if(m_prevNoteOnOff - noteOnOff == 1)
  {
    phase -= phase;
  }
  m_prevNoteOnOff = m_noteOnOff;
  m_noteOnOff = noteOnOff;
}

float Envelope::getAmplitude()
{
  if(m_noteOnOff == 1)
  {
    int intPhase = static_cast<int>(phase);
    return m_envelope[intPhase];
  }
  if(m_noteOnOff == 0)
  {
    int intPhase = static_cast<int>(phase);
    return m_envelopeRelease[intPhase];
  }
}
