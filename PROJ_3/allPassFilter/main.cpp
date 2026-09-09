// "Copyleft [2026] <Midasmathieu>"
#include <iostream>

class Allpass {
 public:
  Allpass() { std::cout << "Allpass constructor" << std::endl; }
  ~Allpass() { std::cout << "Allpass destructor" << std::endl; }

  //filter dsp calculations
  void applyEffect(const float& input, float& output) {
    feedbackInput = input + 0.167772f * sampleMinusEight;
    output = feedbackInput * 0.167772f - sampleMinusEight;
    sampleMinusEight = sampleMinusSeven;
    sampleMinusSeven = sampleMinusSix;
    sampleMinusSix = sampleMinusFive;
    sampleMinusFive = sampleMinusFour;
    sampleMinusFour = sampleMinusThree;
    sampleMinusThree = sampleMinusTwo;
    sampleMinusTwo = sampleMinusOne;
    sampleMinusOne = feedbackInput;
    // added cout for impulse response
    std::cout << sampleNumber << ": " << output << std::endl;
    sampleNumber++;
  }
  //buffer floats (could also have been circulair buffer but this is easier
  float feedbackInput     = { 0.0f };
  float summedInput       = { 0.0f };
  float sampleMinusOne    = { 0.0f };
  float sampleMinusTwo    = { 0.0f };
  float sampleMinusThree  = { 0.0f };
  float sampleMinusFour   = { 0.0f };
  float sampleMinusFive   = { 0.0f };
  float sampleMinusSix    = { 0.0f };
  float sampleMinusSeven  = { 0.0f };
  float sampleMinusEight  = { 0.0f };
  int sampleNumber        = { 0 };
};


int main() {
  // make filter and run impulse response signal through
  Allpass filter;
  float filteredSignal = 0.0f;
  float inputSignal = 1.0f;
  filter.applyEffect(inputSignal, filteredSignal);
  inputSignal = 0.0f;
  for (int i = 0; i <= 21; i++) {
    filter.applyEffect(inputSignal, filteredSignal);
  }
}



