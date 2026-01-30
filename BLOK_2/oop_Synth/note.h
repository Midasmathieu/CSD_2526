#ifndef _Note_H_
#define _Note_H_


class Note {
public:
  Note(int midiNoteNumber, float quarterNoteDur = 1.0);
  int getMidiNoteNumber();
  float getQuarterNoteDur();


private:
  int midiNoteNumber;
  float quarterNoteDur;
}

#endif
