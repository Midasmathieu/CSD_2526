//
// Created by Dean on 02/12/2023.
//

#include "audiocomponent.h"
#include <iostream>
#include <oscillator.h>
#include <saw.h>
#include "Filters.h"
#include "CircularBuffer.h"
#include "deltasequence.h"
#include "math.h"


struct CustomCallback : AudioCallback {
    explicit CustomCallback(double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {
    }

    void prepare(int sampleRate, int blockSize) override {
      saw.prepare(sampleRate);
      saw.setFrequency(110.0f);
      lfo.prepare(sampleRate);
      lfo.setFrequency(550.0f);
      filter.calculateCoefficients(200.0f, 0.1f);
      circularBuffer.allocateBuffer();
      circularBuffer.resetSize(96000);



    }

    void process(AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;


        for (auto sample = 0u; sample < numFrames; ++sample) {
            saw.tick();
            lfo.tick();
            circularBuffer.tick();
            filter.calculateCoefficients(800.0f+lfo.getSample()*300.0f, 17.2f);
            const float oscSample = saw.getSample() * 0.1f;
            float filteredOutput = filter.process(oscSample);
            if(filteredOutput >= 1.0) { filteredOutput = 1.0; std::cout << "clipping \n";
            } else if(filteredOutput <= -1.0) { filteredOutput = -1.0; std::cout << "-clipping \n";}
            for(auto channel = 0u; channel < numOutputChannels; ++channel) {
                outputChannels[channel][sample] = circularBuffer.read();
            }
        }
    }


    Saw saw {200};
    Saw lfo {0.5};
    PirkleBiquad filter;
    CircularBuffer circularBuffer;
};

#define Delta_Sequence 0

int main() {


#if Delta_Sequence
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource(48000);
    DeltaSequence::run(audioSource.filter);
#else
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource(48000);
    JUCEModule juceModule(audioSource);
    juceModule.init(2, 2);


    std::cout << "Press q Enter to quit..." << std::endl;
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
                break;
        }
    }
#endif
    return 0;
}
