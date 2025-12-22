




float Synth::mtof(int midiNoteNumber) {
  return 440.0 * pow (2.0, (midiNoteNumber - 69.0f) / 12.0f);
}
