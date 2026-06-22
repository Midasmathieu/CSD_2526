#include "note.h"

Note::Note(float midiNoteNumber, float midiNoteLength, bool noteOnOff) : 
  m_midiNoteNumber(midiNoteNumber), m_midiNoteLength(midiNoteLength),
    m_noteOnOff(noteOnOff)
{
  std::cout << "Note constructor" << std::endl;
}

Note::~Note()
{
  std::cout << "Note destructor" <<std::endl;
}

float Note::getMidiNoteNumber()
{
  return m_midiNoteNumber;
}

bool Note::getNoteOnOff()
{
  return m_noteOnOff;
}
