#pragma once
#include <iostream>
#include "waveShaper.h"
#include "CircularBuffer.h"
#include "Filters.h"
#include <juce_audio_processors/juce_audio_processors.h>

class EffectsChain
{
 public:
  EffectsChain() {}
  void prepareToPlay(float sampleRate, int numSamplesPerBlock){
    m_sampleRate = sampleRate;
    std::cout << sampleRate << std::endl;
    circularBuffer[0].prepare(sampleRate);
    circularBuffer[1].prepare(sampleRate);

    circularBuffer[0].resetSize(4*m_sampleRate);
    circularBuffer[1].resetSize(4*m_sampleRate);

    circularBuffer[0].setDistanceRW(200);
    circularBuffer[1].setDistanceRW(200);

    // circularBuffer.m_calculatePhaseStep();
    circularBuffer[0].generateEnvelope();
    circularBuffer[1].generateEnvelope();

    // circularBuffer.setGrainSize(24000);
    filter[0].calculateCoefficients(2000.0f, 6.0f);
    filter[1].calculateCoefficients(2000.0f, 6.0f);

    // circularBuffer[0].setDryWet(0.0f);
    // circularBuffer[1].setDryWet(0.0f);

    filter[0].prepare(sampleRate);
    filter[1].prepare(sampleRate);
}


  // void getNextBlock(juce::AudioBuffer<float>& buffer)
  // {
  //   // Your DSP goes here
  //   //for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
  //   auto* inputChannel = buffer.getReadPointer(0);
  //   auto* outputChannel = buffer.getWritePointer(0);
  //   for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
  //   {
  //     // float tempInput = inputChannel[sample];
  //     // // circularBuffer.write(tempInput * 0.5 + shapedOutput * 0.01);
  //     // circularBuffer.write(shapedOutput * 0.3);
  //     // // std::cout << tempInput << std::endl;
  //     // sampletje = circularBuffer.read();
  //     // // filteredOutput = filter.process(sampletje);
  //     // filteredOutput = filter.process(sampletje * 0.5 + tempInput * 0.5);
  //
  //
  //     waveShaper.processFrame(inputChannel[sample]+outputDelay*0.5, outputWaveShaper);
  //     filter.processFrame(outputWaveShaper*0.3, outputFilter);
  //     circularBuffer.processFrame(outputFilter, outputDelay);
  //
  //     outputChannel[sample] = outputFilter;
  //     //outputChannel[sample] = shapedOutput + tempInput;
  //     // outputChannel[sample] = shapedOutput;
  //     // std::cout << sampletje << std::endl;
  //     }
  //   }
// }



void getNextBlock(juce::AudioBuffer<float>& buffer){
        // Your DSP goes here
//TODO: fix dual mono!
        for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
            auto* inputChannel = buffer.getReadPointer(channel);
            auto* outputChannel = buffer.getWritePointer(channel);
            for (int sample = 0; sample < buffer.getNumSamples(); ++sample){
              waveShaper.processFrame(inputChannel[sample]+outputDelay[channel]*0.5, outputWaveShaper[channel]);
              filter[channel].processFrame(outputWaveShaper[channel]*0.3, outputFilter[channel]);
              circularBuffer[channel].processFrame(outputFilter[channel], outputDelay[channel]);
              outputChannel[sample] = outputFilter[channel];
            }
        }


    }

  void setParameter(float parameter)
  {
    if(prevParameter != parameter)
    {
      float delayTime = parameter * m_sampleRate + m_sampleRate/2;
      int grainSizetje = static_cast<int>(delayTime);
      float frequency = (1-parameter) * (1-parameter) *  4000.0f + 400.0f;
      float que = parameter * parameter * 2.0f + 1.0f;
      float k = parameter * -2.5f + 6.0f;
      circularBuffer[0].setGrainReadDestination(delayTime);
      circularBuffer[1].setGrainReadDestination(delayTime);
      filter[0].calculateCoefficients(frequency, que);
      filter[1].calculateCoefficients(frequency, que);
      waveShaper.changeCurveK(k);
    }
    prevParameter = parameter;
  }

 private:
  WaveShaper waveShaper;
  CircularBuffer circularBuffer[2];
  Biquad filter[2];
  float  prevParameter = -1;
  float sampletje;
  float tempSample;
  float feedback;
  float m_sampleRate;
  float outputWaveShaper[2];
  float filteredOutput[2];
  float outputDelay[2];
  float outputFilter[2];
};
