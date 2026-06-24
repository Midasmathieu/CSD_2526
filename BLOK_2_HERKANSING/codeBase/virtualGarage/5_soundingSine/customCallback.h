#include "audiocomponent.h"
//  Daan Schrier
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "melody.h"
#include "kickSynth.h"
#include "leadSynth.h"

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {
      envelope.prepare(sampleRate);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                // write sample to buffer at channel 0, amp = 0.25
                outputChannels[channel][sample] = kickSynth.proccesKick() + 0.2 * leadSynth.proccesKick();
                melody.tick();
                float freqi = melody.getFrequency();
                float freq = kickSynth.mtof(freqi);
                //float freq2 = leadSynth.mtof(freqi); 
                bool onOffNote = melody.getNoteOnOff();
                kickSynth.setNoteOnOff(onOffNote);
                leadSynth.setNoteOnOff(onOffNote);
                leadSynth.setFrequency(freq);
            }
        }
    }

 private:
  Sine sine;
  // Saw saw;
  // Square square;
  Melody melody;
  KickSynth kickSynth;
  LeadSynth leadSynth;
  Envelope envelope {100, 200, 50, 300};
  // float freq = kickSynth.mtof(40);
};
