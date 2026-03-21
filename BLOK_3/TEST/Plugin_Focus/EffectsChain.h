#pragma once
#include <iostream>
#include "waveShaper.h"
#include "CircularBuffer.h"
#include "Filters.h"
#include <juce_audio_processors/juce_audio_processors.h>

class EffectsChain {
 public:
    EffectsChain() {}
    void prepareToPlay(float sampleRate, int numSamplesPerBlock){
        std::cout << sampleRate << std::endl;
        circularBuffer.resetSize(192000);
        circularBuffer.setDistanceRW(200);
        circularBuffer.m_calculatePhaseStep();
        circularBuffer.generateEnvelope();
        circularBuffer.setGrainSize(24000);
        filter.calculateCoefficients(2000.0f, 6.0f);
    }


    void getNextBlock(juce::AudioBuffer<float>& buffer){
        // Your DSP goes here
        // for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputChannel = buffer.getReadPointer(0);
            auto* outputChannel = buffer.getWritePointer(0);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample){
                circularBuffer.tick();
                circularBuffer.smoothGrain();
                float tempInput = inputChannel[sample];
                circularBuffer.write(tempInput * 0.5 + shapedOutput * 0.01);
                // std::cout << tempInput << std::endl;
                sampletje = circularBuffer.read();
                // filteredOutput = filter.process(sampletje);
                filteredOutput = filter.process(tempInput);
                waveShaper.applyEffect(tempInput, shapedOutput);
                outputChannel[sample] = shapedOutput;
                // outputChannel[sample] = filteredOutput;
                // std::cout << sampletje << std::endl;
            }
        }
    // }

    void setParameter(float parameter){
        if(prevParameter != parameter){
          int delayTime = parameter * 95000.0 + 2000.0;
          std::cout << "grainsize:::::: " << delayTime << std::endl;
          circularBuffer.calculateGrainStep(delayTime);
          float frequency = parameter * -4000.0f + 4700.0f;
          float que = parameter * 4.0f + 4.0f;
          filter.calculateCoefficients(frequency, que);

        }

        prevParameter = parameter;
      }

 private:
  float  prevParameter = -1;
  float sampletje;
  float filteredOutput;
  WaveShaper waveShaper;
  float tempSample;
  CircularBuffer circularBuffer;
  PirkleBiquad filter;
  float feedback;
  float shapedOutput;
};
