#include "additiveSynth.h"

AdditiveSynth::AdditiveSynth() {
  Sine sine;
  Sine overtone1;
  Sine overtone2;
  // Sine overtone3;
  // Sine overtone4;
  // Sine overtone5;
  // Sine overtone6;
  // Sine lfo;
}

void setFrequencys(){
  sine.setFrequency(currentNote.getPitch());
  overtone1.setFrequency(currentNote.getPitch()*3);
  overtone2.setFrequency(currentNote.getPitch()*5);
}

void tickAll(){
  sine.tick();
  overtone1.tick();
  overtone2.tick();
}

void calculateAll(){
  sine.calculate();
  overtone1.calculate();
  overtone2.calculate();
}

int getSample(){
  return (sine.getSample() + overtone1.getSample() + overtone2.getSample()) * 0.3;
}

void setFrequency2() {
  sine.setFrequency(note.getPitch() + offset);
  overtone1.setFrequency(note.getPitch()*2 + offset);
  overtone2.setFrequency(note.getPitch()*3 + offset);
}
