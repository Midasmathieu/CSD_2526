#include "waveShaper.h"
#include <iostream>
#include "wavetableGenerator.h"
// #include "wavetableGenerator.cpp"

#define useWavetable 1
WaveShaper::WaveShaper(float dryWet) : Effect(dryWet) {
#if useWavetable
  WavetableGenerator::generateSCurve(buffer, BUFFER_SIZE, 2.0f);
#endif
}

WaveShaper::~WaveShaper() {}


void WaveShaper::applyEffect(const float &input, float &output)
{
  float sample = input;
  if(sample > 1.0f)  sample = 1.0f;
  if(sample < -1.0f)  sample = -1.0f;
#if useWavetable
  float indexFloat = WavetableGenerator::map(sample, -1.0f, 1.0f, 0.0f, (float) (BUFFER_SIZE - 1));
  int index = (int) indexFloat;
  float normValue = indexFloat - index;
  // std::cout << "normaalvalue:;  " <<  index << ", " << indexFloat << ", " << normValue << std::endl;
  // TODO - interpolate
  output = WavetableGenerator::mapLin(normValue, buffer[index], buffer[index+1]);
  std::cout << "this is the output: " << buffer[index] << ", " << output << std::endl;
  // output = buffer[index];
#else
  static float k = 10.0f;
  static float normalizeFactor = 1.0f / atan(k);
  output = normalizeFactor * atan(k * input);
#endif

}
