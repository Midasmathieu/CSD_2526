#ifndef _MELODY_H_
#define _MELODY_H_
#include "note.h"
#include <iostream>
#include <cmath>

class Melody {
 public:
  Melody();
  ~Melody();
  void tick();
  void wrap();
  int getFrequency();
  bool getNoteOnOff();
 private:
  int clock = 0;
  int noteIndex = 0;
  Note notes[6] = {
    Note(69.0f, 24000.0f, 1), Note(69.0f, 24000.0f, 0),
    Note(73.0f, 24000.0f, 1), Note(73.0f, 24000.0f, 0),
    Note(77.0f, 24000.0f, 1), Note(77.0f, 24000.0f, 0)};
//  int notes[7] = {4900, 5000, 9600, 17000, 9900, 5000, 4000};
};

#endif
