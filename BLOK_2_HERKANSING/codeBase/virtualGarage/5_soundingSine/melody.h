#ifndef _MELODY_H_
#define _MELODY_H_
#include <iostream>
#include <cmath>

class Melody {
 public:
  Melody();
  ~Melody();
  void tick();
  void wrap();
  int getFrequency();
 private:
  int clock = 0;
  int noteIndex = 0;
  int notes[7] = {440, 660, 110, 220, 880, 88, 88};
};

#endif
