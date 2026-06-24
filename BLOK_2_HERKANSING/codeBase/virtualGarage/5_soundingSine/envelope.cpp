#include "envelope.h"

Envelope::Envelope(float attackMs, float decayMs,
                   float sustainPct, float releaseMs)
                   : m_attackMs(attackMs), m_decayMs(decayMs),
                     m_sustainPct(sustainPct), m_releaseMs(releaseMs)
{
  std::cout << "Envelope constructor" << std::endl;
  allocateEnvelope();
  m_attackSamples = calculateMsToBuf(attackMs);
  m_decaySamples = calculateMsToBuf(decayMs);
  m_releaseSamples = calculateMsToBuf(releaseMs);
  m_sustainAmp = sustainPct * 0.01;

  std::cout << "adsr: " << m_attackSamples << ", " << m_decaySamples << ", " << m_sustainAmp << ", " << m_releaseSamples <<std::endl;

  createEnvelope();
  for(int i = 0; i < 100; i++)
  {
    std::cout << m_envelope[i*10] << std::endl;
  }
}

Envelope::Envelope(float init, float attackMs, float decayMs,
                   float sustainPct, float releaseMs)
                   : m_initPct(init), m_attackMs(attackMs), m_decayMs(decayMs),
                     m_sustainPct(sustainPct), m_releaseMs(releaseMs)
{
  std::cout << "Envelope constructor" << std::endl;
  allocateEnvelope();
  m_init = m_initPct * 0.01;
  m_attackSamples = calculateMsToBuf(attackMs);
  m_decaySamples = calculateMsToBuf(decayMs);
  m_releaseSamples = calculateMsToBuf(releaseMs);
  m_sustainAmp = sustainPct * 0.01;

  std::cout << "adsr: " << m_attackSamples << ", " << m_decaySamples << ", " << m_sustainAmp << ", " << m_releaseSamples <<std::endl;

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

void Envelope::prepare(int sampleRate)
{
  std::cout << sampleRate << std::endl;
  m_sampleRate = sampleRate;
}

float Envelope::calculateMsToBuf(float number)
{
  return number * m_millisToBuf;
}

void Envelope::setAttack(float attackMs)
{
  m_attackMs = attackMs;
  m_attackSamples = calculateMsToBuf(attackMs);
  createEnvelope();
}

void Envelope::setDecay(float decayMs)
{
  m_decayMs = decayMs;
  m_decaySamples = calculateMsToBuf(decayMs);
  createEnvelope();
}

void Envelope::setSustain(int sustainPct)
{
  m_sustainPct = sustainPct;
  m_sustainAmp = sustainPct * 0.01;
  createEnvelope();
}

void Envelope::setRelease(float releaseMs)
{
  m_releaseMs = releaseMs;
  m_releaseSamples = calculateMsToBuf(releaseMs);
  createEnvelope();
}

void Envelope::setInit(float init)
{
  m_initPct = init;
  m_init = init * 0.01;
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
  if(buffIndex <= m_attackSamples + m_decaySamples)
  {
    buffIndex += scale;
    if(buffIndex >= 1024)
    {
      buffIndex -= buffIndex;
    }
  }
  if(m_prevNoteOnOff - noteOnOff == 1 | m_prevNoteOnOff - noteOnOff == -1)
  {
    buffIndex -= buffIndex;
  }
  m_prevNoteOnOff = m_noteOnOff;
  m_noteOnOff = noteOnOff;
}

float Envelope::getAmplitude()
{
  int lowIndex = (int) buffIndex;
  int highIndex = lowIndex + 1;
  float normVal = buffIndex - lowIndex;
  if(m_noteOnOff == 1)
  {
    float output = mapLin(normVal, m_envelope[lowIndex], m_envelope[highIndex]);
    return output;
  }
  if(m_noteOnOff == 0)
  {
    float output = mapLin(normVal, m_envelopeRelease[lowIndex], m_envelopeRelease[highIndex]);
    return output;
  }
  else { float output = 0; return output; }
}

float Envelope::mapLin(float normVal, float low, float high)
{
  float difference = high - low;
  float mappedVal = low + difference * normVal;
  return mappedVal;
}
