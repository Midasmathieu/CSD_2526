#include "audiocomponent.h"
//  Daan Schrier
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "melody.h"

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {

    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                // write sample to buffer at channel 0, amp = 0.25
                outputChannels[channel][sample] = 0.33*sine.getSample()+0.33*square.getSample()+fifth.getSample()*0.33;
                sine.tick();
                square.tick();
                melody.tick();
                fifth.tick();
                int freq = melody.getFrequency();
                square.setFrequency(freq);
                fifth.setFrequency(freq/1.5);
                sine.setFrequency(freq/2);
            }
        }
    }

private:
  Sine sine{440};
  Saw square {220};
  Square fifth {330};
  Melody melody;  
};
