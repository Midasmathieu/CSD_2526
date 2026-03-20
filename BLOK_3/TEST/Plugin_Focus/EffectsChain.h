#pragma once
#include <iostream>
#include "waveShaper.h"
#include "delay.h"
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
        filter.calculateCoefficients(2000.0f, 120.0f);
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
                circularBuffer.write(tempInput * 0.5 + filteredOutput * 2.0);
                // std::cout << tempInput << std::endl;
                sampletje = circularBuffer.read();
                filteredOutput = filter.process(sampletje);
                filteredOutput = sampletje * 0.5 + tempInput * 0.5;
                outputChannel[sample] = filteredOutput;
                // std::cout << sampletje << std::endl;
            }
        }
    // }

    void setParameter(float parameter){
        if(prevParameter != parameter){
          // static_cast fuckt dingen op in classes gebruik iets anders
          int delayTime = parameter * 95000.0 + 2000.0;
          std::cout << "grainsize:::::: " << delayTime << std::endl;
          circularBuffer.calculateGrainStep(delayTime);
        }

        prevParameter = parameter;
      }

 private:
  float  prevParameter = -1;
  float sampletje;
  float filteredOutput;
  // WaveShaper waveShaper;
  // Delay delay;
  float tempSample;
  CircularBuffer circularBuffer;
  PirkleBiquad filter;
  float feedback;
};
