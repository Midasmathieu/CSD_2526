//
// Created by Dean on 02/12/2023.
//

#include "audiocomponent.h"
#include <iostream>
#include <oscillator.h>
#include <saw.h>
#include "Filters.h"
#include "deltasequence.h"
#include "math.h"


struct CustomCallback : AudioCallback {
    explicit CustomCallback(double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {
    }

    void prepare(int sampleRate, int blockSize) override {
        saw.prepare(sampleRate);
        std::cout << sampleRate << std::endl;
        saw.setFrequency(110.0f);
        lfo.prepare(sampleRate);
        lfo.setFrequency(0.3f);



    }

    void process(AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;


        for (auto sample = 0u; sample < numFrames; ++sample) {
            saw.tick();
            lfo.tick();
            float w0 = (2.0f*M_PI*3000.0f+lfo.getSample()*1000)/static_cast<float>(48000);
            float cosW0 = cos(w0);
            float sinW0 = sin(w0);
            // std::cout << w0 << ", " << sinW0 << std::endl;
            float alfa = sinW0/(2.0f*1.0f);
            float b1 = 1.0f-cosW0;
            float b0 = b1/2.0f;
            float b2 = b0;
            float a0 = 1.0f+alfa;
            float a1 = -2.0f*cosW0;
            float a2 = 1.0f-alfa;
            // std::cout << "check deze: " << a1 << ", " << a2 << ", " << b0 << ", " << b1 << ", " << b2 << std::endl;
            filter.setA1Coefficient(a0);
            filter.setA1Coefficient(a1);
            filter.setA2Coefficient(a2);
            filter.setB0Coefficient(b0);
            filter.setB1Coefficient(b1);
            filter.setB2Coefficient(b2);
            const float oscSample = saw.getSample() * 0.2f;
            float filteredOutput = filter.process(oscSample);
            if(filteredOutput >= 1.0) { filteredOutput = 1.0; std::cout << "clipping \n";
            } else if(filteredOutput <= -1.0) { filteredOutput = -1.0; std::cout << "-clipping \n";}
            for(auto channel = 0u; channel < numOutputChannels; ++channel) {
                outputChannels[channel][sample] = filteredOutput;
            }
        }
    }


    Saw saw {200};
    Saw lfo {0.5};
    Biquad filter;
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
