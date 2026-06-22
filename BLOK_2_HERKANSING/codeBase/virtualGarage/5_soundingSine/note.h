#ifndef _NOTE_H_
#define _NOTE_H_
#include <iostream>

class Note
{
 public:
  Note(float midiNoteNumber, float midiNoteLength,
      bool noteOnOff);
  ~Note();
  float getMidiNoteNumber();
  bool getNoteOnOff();
 private:
  float m_midiNoteNumber;
  //float velocity;
  float m_midiNoteLength;
  bool m_noteOnOff = 1;
};


#endif
