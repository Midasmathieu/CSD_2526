#include "callback.h"

Callback::Callback(float samplerate) : AudioCallback(samplerate), samplerate(samplerate) {}

void Callback::prepare (int samplerate)  {
  this->samplerate = samplerate;
  melody.prepare(samplerate);
  sine.setSamplerate(samplerate);
  overtone1.setSamplerate(samplerate);
  overtone2.setSamplerate(samplerate);
  overtone3.setSamplerate(samplerate);
  overtone4.setSamplerate(samplerate);
  overtone5.setSamplerate(samplerate);
  overtone6.setSamplerate(samplerate);
  lfo.setSamplerate(samplerate);
  // overtone2.setSamplerate(samplerate);

  // set start frequency
  Note currentNote = melody.getCurrentNote();
  sine.setFrequency(currentNote.getPitch());
  overtone1.setFrequency(currentNote.getPitch()*3);
  overtone2.setFrequency(currentNote.getPitch()*5);
  overtone3.setFrequency(currentNote.getPitch()*7);
  overtone4.setFrequency(currentNote.getPitch()*9);
  overtone5.setFrequency(currentNote.getPitch()*11);
  overtone6.setFrequency(currentNote.getPitch()*13);
  lfo.setFrequency(1);
}

void Callback::process(AudioBuffer buffer)  {
  auto [inputChannels,
        outputChannels,
        numInputChannels,
        numOutputChannels,
        numFrames] = buffer;


  for (int channel = 0; channel < numOutputChannels; ++channel) {

    for (int frame = 0; frame < numFrames; ++frame) {
      sine.tick();
      overtone1.tick();
      overtone2.tick();
      overtone3.tick();
      overtone4.tick();
      overtone5.tick();
      overtone6.tick();
      lfo.tick();
      sine.calculate();
      overtone1.calculate();
      overtone2.calculate();
      overtone3.calculate();
      overtone4.calculate();
      overtone5.calculate();
      overtone6.calculate();
      lfo.calculate();

      outputChannels[channel][frame] = (sine.getSample() +
        + overtone1.getSample() * 1.0f + overtone2.getSample() * 1.0f
        + overtone3.getSample() * 1.0f + overtone4.getSample() * 1.0f
        + overtone5.getSample() * 1.0f + overtone6.getSample() * 1.0f ) * 0.05;

      if (melody.tick())
      { }
        /* NOTE: retrieving a copy of note, would be better to use a pointer,
         * but usage of pointers is out of scope for now.
         */
        // Note note = melody.getCurrentNote();
        // sine.setFrequency(note.getPitch());
        Note note = melody.getCurrentNote();
        lfo.setFrequency(0.8);
        float offset = lfo.getSample()*10;
        sine.setFrequency(note.getPitch() + offset);
        overtone1.setFrequency(note.getPitch()*2 + offset);
        overtone2.setFrequency(note.getPitch()*3 + offset);
        overtone3.setFrequency(note.getPitch()*4 + offset);
        overtone4.setFrequency(note.getPitch()*5 + offset);
        overtone5.setFrequency(note.getPitch()*6 + offset);
        overtone6.setFrequency(note.getPitch()*7 + offset);


      // melody.tick returns true when a new note is reached

    }
  }
}
