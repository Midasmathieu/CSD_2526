#include "waveShaper.h"
#include <iostream>
#include "wavetableGenerator.h"
// #include "wavetableGenerator.cpp"

#define useWavetable 1
WaveShaper::WaveShaper(float dryWet) : Effect(dryWet) {
#if useWavetable
  WavetableGenerator::generateSCurve(buffer, BUFFER_SIZE, 10.0f);
#endif
}

WaveShaper::~WaveShaper() {}

void WaveShaper::changeCurveK(float k) {
  WavetableGenerator::generateSCurve(buffer, BUFFER_SIZE, k);
}

void WaveShaper::applyEffect(const float &input, float &output)
{
  float sample = input;
  if(sample > 1.0f)  sample = 1.0f;
  if(sample < -1.0f)  sample = -1.0f;
#if useWavetable
  float indexFloat = WavetableGenerator::map(sample, -1.0f, 1.0f, 0.0f, (float) (BUFFER_SIZE - 1));
  int index = (int) indexFloat;
  int indexPlusOne = index + 1;
  float normValue = indexFloat - index;
  output = WavetableGenerator::mapLin(normValue, buffer[index], buffer[indexPlusOne]);
#else
  static float k = 10.0f;
  static float normalizeFactor = 1.0f / atan(k);
  output = normalizeFactor * atan(k * input);
#endif

}
