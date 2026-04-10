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
    std::cout << sampleRate << std::endl;
    circularBuffer.resetSize(192000);
    circularBuffer.setDistanceRW(200);
    // circularBuffer.m_calculatePhaseStep();
    circularBuffer.generateEnvelope();
    // circularBuffer.setGrainSize(24000);
    filter.calculateCoefficients(2000.0f, 6.0f);
    circularBuffer.setDryWet(0.0f);
}


  void getNextBlock(juce::AudioBuffer<float>& buffer)
  {
    // Your DSP goes here
    // for(int channel = 0; channel < buffer.getNumChannels(); ++channel){
    auto* inputChannel = buffer.getReadPointer(0);
    auto* outputChannel = buffer.getWritePointer(0);
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
      // circularBuffer.smoothGrain();
      // circularBuffer.tick();
      // float tempInput = inputChannel[sample];
      // // circularBuffer.write(tempInput * 0.5 + shapedOutput * 0.01);
      // circularBuffer.write(shapedOutput * 0.3);
      //
      // // std::cout << tempInput << std::endl;
      // sampletje = circularBuffer.read();
      // // filteredOutput = filter.process(sampletje);
      // filteredOutput = filter.process(sampletje * 0.5 + tempInput * 0.5);
      // waveShaper.applyEffect(filteredOutput, shapedOutput);
      circularBuffer.processFrame(inputChannel[sample], outputChannel[sample]);


      //outputChannel[sample] = shapedOutput + tempInput;
      // outputChannel[sample] = shapedOutput;
      // std::cout << sampletje << std::endl;
      }
    }
// }

  void setParameter(float parameter)
  {
    if(prevParameter != parameter)
    {
      float delayTime = parameter * 48000.0 + 24000.0;
      int grainSizetje = static_cast<int>(delayTime);
      circularBuffer.calculateGrainStep(delayTime);
      float frequency = (1-parameter) * (1-parameter) *  4000.0f + 400.0f;
      float que = parameter * parameter * 2.0f + 1.0f;
      filter.calculateCoefficients(frequency, que);
      float k = parameter * -2.5f + 6.0f;
      waveShaper.changeCurveK(k);
      circularBuffer.setDryWet(parameter);
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
