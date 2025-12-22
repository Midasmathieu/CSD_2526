#ifndef CALLBACK_H
#define CALLBACK_H

#include "audiocomponent.h"
#include "sine.h"
#include "melody.h"

class Callback : public AudioCallback {
public:
  explicit Callback (float sampleRate);
  void prepare (int rate) override;
  void process (AudioBuffer buffer) override;

  double mtof(float mPitch);
  void updatePitch(Melody& melody, Sine& sine);

private:
  double samplerate;
  Sine sine;
  Sine overtone1;
  Sine overtone2;
  Sine overtone3;
  Sine overtone4;
  Sine overtone5;
  Sine overtone6;
  Sine lfo;
  double amplitude = 0.5;
  Melody melody;
  int frameCounts = 0;

  /* instead of using bpm and specifying note lenghts we'll make every note
   * equal length and specify the delay between notes in terms of the samplerate
   *
   * A note of say 500 msec or 0.5 sec, takes 0.5*samplerate samples to be played
   */
  double noteDelayFactor = 0.1;
};

#endif  //CALLBACK_H
