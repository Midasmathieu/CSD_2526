#include "audiocomponent.h"
//  Daan Schrier
#include "sine.h"
#include "square.h"
#include "saw.h"
#include "melody.h"
#include "kickSynth.h"
#include "integrator.h"
#include "sawToTri.h"
#include "triToSin.h"
//#include "leadSynth.h"

struct CustomCallback : AudioCallback {
    explicit CustomCallback (double Fs) : AudioCallback(Fs) {

    }

    ~CustomCallback() override {

    }

    void prepare (int sampleRate) override {
      //envelope.prepare(sampleRate);
      //saw.setFrequency(100);
      integrator.setFrequency(100);
      //saw.setSamplerate(48000);
      // saw.setFrequency(100);
      // saw.setSamplerate(48000);
    }

    void process (AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;

        for (int channel = 0u; channel < numOutputChannels; ++channel) {
            for (int sample = 0u; sample < numFrames; ++sample) {
                // write sample to buffer at channel 0, amp = 0.25
                outputChannels[channel][sample] = triToSin.applyShaper(triOut);
                  //integrator.getSample(); //saw.getSample();
                //saw.tick();
                // kickSynth.process(); 
                   // 0.05 * leadSynth.process();
                sawVout = integrator.getVout();
                triOut = sawToTri.applyShaper(sawVout);

                //melody.tick();
                integrator.tick();
                
                //saw.tick();
                //saw.calculateSample();
                //float freqi = melody.getFrequency();
                //float freq = kickSynth.mtof(freqi);
                //float freq2 = leadSynth.mtof(freqi); 
                //bool onOffNote = melody.getNoteOnOff();
                //kickSynth.setNoteOnOff(onOffNote);
                // leadSynth.setNoteOnOff(onOffNote);
               // leadSynth.setFrequency(freq);
            }
        }
    }

 private:
  // Sine sine { 1.0f };
  // Saw saw;
  Integrator integrator;
  SawToTri sawToTri;
  TriToSin triToSin;
  float sawVout = 0;
  float triOut = 0;
  // Square square;
  //Melody melody;
  //KickSynth kickSynth;
  //LeadSynth leadSynth;
  //Envelope envelope {100, 200, 50, 300};
  // float freq = kickSynth.mtof(40);
};
