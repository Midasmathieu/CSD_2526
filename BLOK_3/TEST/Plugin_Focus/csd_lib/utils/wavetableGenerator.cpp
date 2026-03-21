#include "wavetableGenerator.h"
#include "math.h"

void WavetableGenerator::generateWaveform(float* buffer, int bufSize,
  WaveformType waveformType) {
  Oscillator* osc;
  float freq = 1.0;
  switch(waveformType) {
    case WaveformType::SINE:
    {
      osc = new Sine(freq, bufSize);
      break;
    }
    case WaveformType::SAW:
    {
      osc = new Saw(freq, bufSize);
      break;
    }
    case WaveformType::SQUARE:
    {
      // TODO: alter calculation of to create a non-aliasing square,
      // similar to the calculation within the Saw class
      osc = new Square(freq, bufSize);
      break;
    }
    default:
      throw "WavetableGenerator::WavetableGenerator - incorrect waveformType.";
      break;
  }

  for(int i = 0; i < bufSize; i++) {
    buffer[i] = osc->getSample();
    osc->tick();
  }
  // release dynamically allocated oscillator object
  delete osc;
  osc = nullptr;
}

// generates an s-curve in the range [-1, 1], based arctangent function
// k: influences the curve,
//    k < 1, mimics linear function
//    k = 1, nearly linear
//    k > 1, more 'curvy'
//    k > 100, "square-like"
void WavetableGenerator::generateSCurve(float* buffer, int bufSize, float k)
{
  float normalizeFactor = 1.0f / atan(k);
  for(int i = 0; i < bufSize; i++) {
    // calculate s-curve with arctangent
    // calculate x in range [-1.0f, 1.0f]
    float x = map((float)i, 0, bufSize, -1.0f, 1.0f);
    // formula: Pirkle 2013, "Designing Audio Effect Plug-ins in C++" p. 497
    buffer[i] = normalizeFactor * atan(k * x);
    std::cout << "buffetje " << buffer[i] << std::endl;
  }
}

float WavetableGenerator::map(const float value, float fromLow, float fromHigh, float toLow,
 float toHigh)
{
  // formula for lin interpolation from https://en.wikipedia.org/wiki/Interpolation

  float diffFHL = fromHigh - fromLow;
  float diffTHL = toHigh - toLow;
  float rc = diffTHL / diffFHL;
  float output = (value - fromLow) * rc + toLow;
  // std::cout << "proportions: " << output << std::endl;
  return output;
}

float WavetableGenerator::mapLin(float normValue, float low, float high)
{
  if(normValue < 0 || normValue > 1) {
    throw "WavetableGenerator::mapLin - value is not a normalized value";
  }
  // low + (high - low) * valueBehindComma
  float first  = low * normValue;
  float second = high * (1-normValue);
  return (first + second) * 0.5f;
}
