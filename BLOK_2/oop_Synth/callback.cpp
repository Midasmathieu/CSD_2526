#include "callback.h"

CustomCallback::CustomCallback(float samplerate)
  : AudioCallback(samplerate), sine(100, samplerate), second(150, samplerate), mod(0.25f, samplerate) {
}

void CustomCallback::prepare (int samplerate) {
  sine.setSamplerate();
  second.setSamplerate();
  mod.setSamplerate();
  std::cout << "samplerate: " << samplerate << std::endl;
}

void CustomCallback::process(AudioBuffer buffer) {
  auto [inputChannels,
        outputChannels,
        numInputChannels,
        numOutputChannels,
        numFrames] = buffer;
  for(int channel = 0u; channel < numOutputChannels; ++channel) {
    for(int frame = 0u; frame < numFrames; ++frame) {
      outputChannels[channel][frame] = 0.0f;
      outputChannels[channel][frame] = (sine.getSample() + second.getSample()) * (mod.getSample() + 0.25f);
      second.tick();
      mod.tick();
      sine.tick();
    }
  }
}
