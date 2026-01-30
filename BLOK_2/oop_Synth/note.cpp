#include "note.h"

Note::Note(int midiNoteNumber, float quarterNoteDur = 1.0)
  : midiNoteNumber(midiNoteNumber), quarterNoteDuration(quarterNoteDuration)
{}

int Note::getMidiNoteNumber(){
  return midiNoteNumber;
}

float Note::getQuarterNoteDur(){
  return quarterNoteDur;
}
