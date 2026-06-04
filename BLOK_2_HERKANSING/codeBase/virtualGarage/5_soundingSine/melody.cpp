#include "melody.h"

Melody::Melody()
{
  std::cout << "Melody::Melody constructor" << std::endl;
}

Melody::~Melody()
{
  std::cout << "Melody::~Melody destructor" << std::endl;
}

void Melody::tick()
{
  clock++;
  wrap();
}

void Melody::wrap() 
{
  if(clock >= 24000) 
  { 
    clock = clock - 24000;
    noteIndex = noteIndex + 1;
    if(noteIndex >= 7) {noteIndex = 0;}
    std::cout << noteIndex << std::endl;
  }
}

int Melody::getFrequency()
{
  return notes[noteIndex];
}
