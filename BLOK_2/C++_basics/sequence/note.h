#ifndef NOTE_H
#define NOTE_H
#include <cmath>

#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_devices/juce_audio_devices.h"

class Note {
public:
  Note(int midiNoteNumber, float quarterNoteDuration = 1.0f);

  int getMidiNoteNumber();
  float getQuarterNoteDuration();
  float getPitch();

  static float mtof(int midiNoteNumber);

private:
  int midiNoteNumber;
  float quarterNoteDuration;
};

#endif
