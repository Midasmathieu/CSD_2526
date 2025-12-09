#include <iostream>

class Note {
public:
  Note();
  void play();
  int getVelocity();
  int midiNoteValue;
  int velocity;
};

//Hier definieer je de NoteConstructor
Note::Note() {
  std::cout << "NoteConstructor\n";
  midiNoteValue = 0;
  velocity = 0;
}

void Note::play() {
  std::cout << "midiNoteValue: " << midiNoteValue
    << "velocity: " << velocity << std::endl;
}

// deze bithc returnd de velocity ik snap niet waarom
// de note niet hoeft te worden gereturnd
int Note::getVelocity() {
  std::cout << "wereturningthatshit\n";
  return velocity;
}

int main() {
  Note aNote;
  aNote.midiNoteValue = 69; //440hz omg
  aNote.velocity = 127;
  aNote.play();
}
