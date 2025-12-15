#ifndef MELODY_H
#define MELODY_H

#include <iostream>

#define NUM_NOTES 6

class Melody {
public:
  Melody();
  ~Melody();

  void prepare(int samplerate);

  bool tick();

  Note getCurrentNote();

private:
  void updateCurrentNoteFrameDur();

  Note melody[NUM_NOTES] = {
    Note(60, 1.0f), Note(64, 0.5f), Note(67, 0.25f),
    Note(71, 0.25f), Note(67, 0.25f), Note(64, 0.25f)
  };

  int currentNoteFrameDuration;

  const float bpm = 120.0f;

  float quarterNoteFrameDur;

  int noteIndex = 0;
  int frameCount = 0;
};

#endif
