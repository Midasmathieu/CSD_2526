#include "audiocomponent.h"
// Daan Schrier
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
        lfo.setFrequency(440 + mod2 * 1000);
        float mod = lfo.getSample();
        sine.setFrequency(440 + mod * 1000);
        sine.tick();
        lfo.tick();
        lfo2.tick();
      }
    }
  }

private:
  Sine lfo2{440};
  Sine lfo{440};
  Sine sine{440};
};
