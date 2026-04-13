#pragma once
#include "effect.h"

#define BUFFER_SIZE 512

class WaveShaper : public Effect{
public:
  WaveShaper(float dryWet = 1.0);
  ~WaveShaper();
  void changeCurveK(float k);

  // override base class method
  void applyEffect(const float& input, float& output) override;

private:
  float buffer[BUFFER_SIZE];
};
