#ifndef _Callback_H_
#define _Callback_H_

#include "audiocomponent.h"
#include "oscillator.h"
#include "sine.h"

class CustomCallback : public AudioCallback {
public:
  CustomCallback(float samplerate);
  void prepare(int rate) override;
  void process(AudioBuffer buffer) override;

private:
  Sine sine;
  Sine second;
  Sine mod;
};



#endif
