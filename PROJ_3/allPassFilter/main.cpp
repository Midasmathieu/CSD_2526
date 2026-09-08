// "Copyleft [2026] <Midasmathieu>"
#include <iostream>

class Allpass 
{
 public:
  Allpass(){ std::cout << "Allpass constructor" << std::endl; }
  ~Allpass(){ std::cout << "Allpass destructor" << std::endl; }

  void applyEffect(const float& input, float& output)
  {
    output = input * 0.167772 + sampleMinusOne;
    sampleMinusOne = input;
    std::cout << output << std::endl;
  }

  float sampleMinusOne = { 0.0f };
};


int main()
{
  Allpass filter;
  float filteredSignal = 0.0f;
  float inputSignal = 1.0f;
  filter.applyEffect(inputSignal, filteredSignal);
  inputSignal = 0.0f;
  for(int i = 0; i <= 10; i++)
  {
    filter.applyEffect(inputSignal, filteredSignal);
  }

}



