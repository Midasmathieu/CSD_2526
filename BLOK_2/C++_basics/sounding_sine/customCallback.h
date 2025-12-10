#include "audiocomponent.h"
// Daan Schrier
#include "oscillator.h"
#include "sine.h"


struct CustomCallback : AudioCallback {
  explicit CustomCallback (double Fs) : AudioCallback(Fs) {

  }

  ~CustomCallback() override {

  }

  void prepare (int sampleRate) override {

  }

  void process(AudioBuffer buffer) override {
    auto[inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

    for (int channel = 0u; channel < numOutputChannels; ++channel) {
      for (int sample = 0u; sample < numFrames; ++sample) {

        outputChannels[channel][sample] = sine.getSample();
        float mod2 = lfo2.getSample();
        lfo.setFrequency(2 + mod2 * 3);
        float mod = lfo.getSample();
        sine.setFrequency(660 + mod * 9999 + mod2 * -400);
        sine.tick();
        lfo.tick();
        lfo2.tick();
        sine.calculate();
        lfo.calculate();
        lfo2.calculate();
      }
    }
    // sine.print();
  }

private:
  Sine lfo2{0.5};
  Sine lfo{0.5};
  Sine sine{440};
};
