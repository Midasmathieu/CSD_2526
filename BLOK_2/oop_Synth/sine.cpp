#include "sine.h"
#include "math.h"

Sine::Sine (float frequency, float samplerate)
  : Oscillator (frequency, samplerate) {
  std::cout << "Sine::Sine constructor" << std::endl;
}

void Sine::calculate() {
  sample = sin(M_PI * 2 * phase) * amplitude;
}
