#include "audiocomponent.h"
//  Daan Schrier
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "melody.h"
#include "kickSynth.h"

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
                outputChannels[channel][sample] = //sine.getSample() * envelope.getAmplitude() + 
                                                  kickSynth.proccesKick() * envelope.getAmplitude();
                sine.tick();
                melody.tick();
                
                sine.calculateSample();
                float freqi = melody.getFrequency();
                float freq = kickSynth.mtof(freqi);
                bool onOffNote = melody.getNoteOnOff();
                //std::cout<<onOffNote<<std::endl;
                envelope.tick(onOffNote);
                sine.setFrequency(freq/16*-100*envelope.getAmplitude());
                kickSynth.setFrequency(freq);
            }
        }
    }

private:
  Sine sine;
  // Saw saw;
  // Square square;
  Melody melody;
  KickSynth kickSynth;
  Envelope envelope;
  // float freq = kickSynth.mtof(40);
};
