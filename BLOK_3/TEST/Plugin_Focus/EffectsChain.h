#pragma once
#include <iostream>
#include "waveShaper.h"
#include "delay.h"
#include "CircularBuffer.h"
#include <juce_audio_processors/juce_audio_processors.h>

class EffectsChain {
public:
    EffectsChain() {}
    void prepareToPlay(float sampleRate, int numSamplesPerBlock){
        std::cout << sampleRate << std::endl;
        circularBuffer.resetSize(192000);
        circularBuffer.setDistanceRW(200);
        circularBuffer.m_calculatePhaseStep();
    }


    void getNextBlock(juce::AudioBuffer<float>& buffer){
        // Your DSP goes here
        // for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputChannel = buffer.getReadPointer(0);
            auto* outputChannel = buffer.getWritePointer(0);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample){
                circularBuffer.tick();
                float tempInput = inputChannel[sample];

                circularBuffer.write(tempInput);
                // std::cout << tempInput << std::endl;
                sampletje = circularBuffer.read();
                outputChannel[sample] = sampletje;
                // std::cout << sampletje << std::endl;
            }
        }
    // }

    void setParameter(float parameter){

        // delay.setFeedback(parameter*0.9);


        if(prevParameter != parameter){
          //static_cast fuckt dingen op in classes gebruik iets anders
          std::cout << parameter << std::endl;
          unsigned int delayTime = parameter * 95000.0 + 1000.0;
        }

        prevParameter = parameter;
      }

private:
  float  prevParameter = -1;
  float sampletje;
  WaveShaper waveShaper;
  Delay delay;
  float tempSample;
  CircularBuffer circularBuffer;
  float feedback;
};
