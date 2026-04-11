
#include <iostream>
#include "math.h"
#include "effect.h"
#pragma once

class Biquad : public Effect
{
 public:

   void prepare(float samplerate) {
     m_sampleRate = samplerate;
   }

// calculates the biquad output, audio flow based on the transposed canonical form
  void applyEffect(const float& input, float& output)
  {
    // y[n] = b0X[n] + b1X[n-1] + b2X[n-2] - a1Y[n-1] - a2Y[n-2]
    output = input * b0 + sample1;
    sample1 = sample2 + input * b1 - output * a1;
    sample2 = input * b2 - output * a2;
  }

// calculates the coefficients of the biquad based on the frequency and q factor
  void calculateCoefficients(float f0, float q) {
    float w0 = 2.0f*M_PI*f0/m_sampleRate;
    float d = 1/q;
    float sinW0 = sin(w0);
    float b = 0.5*(1-(d/2)*sinW0)/(1+(d/2)*sinW0);
    float y = (0.5+b)*cos(w0);
    b1 = 0.5+b-y;
    b0 = 0.5*b1;
    b2 = b0;
    a1 = -2.0f*y;
    a2 = 2*b;
  }

private:
  float a1 = { 0.0f };
  float a2 = { 0.0f };
  float b0 = { 0.0f };
  float b1 = { 0.0f };
  float b2 = { 0.0f };
  float sample1 = { 0.0f };
  float sample2 = { 0.0f };
  float m_sampleRate;
};
