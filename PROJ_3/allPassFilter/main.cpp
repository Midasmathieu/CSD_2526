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



class Allpass2 {
 public:
  Allpass2() {
    std::cout << "Allpass2 constructor" << std::endl;
    allocateBuffer();
  }

  ~Allpass2() {
    std::cout << "Allpass2 destructor" << std::endl;
    releaseBuffer();
  }

  void applyEffect(const float& input, float& output) {

    output = input * 0.167772f + read();
    write(-input + 0.167772f * output);
    //std::cout << "readwrite: " << readH << ", " << writeH << std::endl;
    std::cout << readH << ", " << sampleInt << ": " << output << std::endl;
    sampleInt++;
    readH = wrap(readH + 1);
    writeH = wrap(writeH + 1);
  }

  void allocateBuffer() {
    m_buffer = (float*)malloc(m_size * sizeof(float));
    memset(m_buffer, 0, m_size * sizeof(float));
    std::cout << " allocate buffer \n";
    for ( int i = 0; i <= m_size; i++) {
    }
  }
  void releaseBuffer() {
    std::cout << " release buffer \n";
    free(m_buffer);
  }

  int wrap(int numberToWrap) {
    if (numberToWrap > m_size) {
      numberToWrap -= m_size+1;
    }
    if (numberToWrap < 0) {
      numberToWrap += m_size+1;
    }
    return numberToWrap;
  }

  void write(float input) {
    m_buffer[writeH] = input;
  }

  float read() {
    return m_buffer[readH];
  }

 private:
  int m_size = 7;
  float* m_buffer;
  int readH = 0;
  int writeH = 0;
  int sampleInt = 0;
};



int main() {
  // make filter and run impulse response signal through
    //Allpass filter;
  Allpass2 allpassFilter;
    //allpassFilter.printHeads();
  float filteredSignal = 0.0f;
  float inputSignal = 1.0f;
    //filter.applyEffect(inputSignal, filteredSignal);
  allpassFilter.applyEffect(inputSignal, filteredSignal);
  inputSignal = 0.0f;
  for (int i = 0; i <= 21; i++) {
      //filter.applyEffect(inputSignal, filteredSignal);
    allpassFilter.applyEffect(inputSignal, filteredSignal);
  }
}



