// "Copyleft [2026] <Midasmathieu>"
#include <iostream>

class Allpass 
{
 public:
  Allpass(){ std::cout << "Allpass constructor" << std::endl; }
  ~Allpass(){ std::cout << "Allpass destructor" << std::endl; }

  void applyEffect(const float& input, float& output)
  {
    output = flexInput * 0.167772 - sampleMinusEight;
    sampleMinusEight = sampleMinusSeven;
    sampleMinusSeven = sampleMinusSix;
    sampleMinusSix = sampleMinusFive;
    sampleMinusFive = sampleMinusFour;
    sampleMinusFour = sampleMinusThree;
    sampleMinusThree = sampleMinusTwo;
    sampleMinusTwo = sampleMinusOne;
    sampleMinusOne = flexInput;
    flexInput = input + 0.167772 * sampleMinusEight;
    std::cout << output << std::endl;
  }
  float flexInput =        { 0.0f };
  float summedInput =      { 0.0f };
  float sampleMinusOne =   { 0.0f };
  float sampleMinusTwo =   { 0.0f };
  float sampleMinusThree = { 0.0f };
  float sampleMinusFour =  { 0.0f };
  float sampleMinusFive =  { 0.0f };
  float sampleMinusSix =   { 0.0f };
  float sampleMinusSeven = { 0.0f };
  float sampleMinusEight = { 0.0f };

};


int main()
{
  Allpass filter;
  float filteredSignal = 0.0f;
  float inputSignal = 1.0f;
  filter.applyEffect(inputSignal, filteredSignal);
  inputSignal = 0.0f;
  for(int i = 0; i <= 20; i++)
  {
    filter.applyEffect(inputSignal, filteredSignal);
  }

}



