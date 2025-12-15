#include <melody.h>

Melody::Melody() {}
Melody::~Melody() {}

void Melody::prepare(int samplerate) {
  quarterNoteFrameDur = 60.0f / bpm * samplerate;
  updateCurrentNoteFrameDur();
}


Note Melody::getCurrentNote() {
  return melody[noteIndex];
}

bool Melody::tick() {
  frameCount++;

  if (frameCount >= currentNoteFrameDuration) {
    noteIndex++;
    if(noteIndex >= NUM_NOTES) {
      noteIndex = 0;
    }
    updateCurrentNoteFrameDur();

    frameCount = 0;
    return true;
  }
  return false;
}

void Melody::updateCurrentNoteFrameDur() {
  currentNoteFrameDuration =
    melody[noteIndex].getQuarterNoteDuration() * quarterNoteFrameDur;
}
