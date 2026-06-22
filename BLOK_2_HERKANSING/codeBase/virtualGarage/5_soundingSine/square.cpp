#include "square.h"
#include "math.h"

Square::Square() : amplitude(1.0), sample(0)
{
  std::cout << "Square - constructor\n";
}

Square::~Square() {
  std::cout << "Square - destructor\n";
}


float Square::getSample() {
  return sample;
}

void Square::calculateSample() 
{
  if(phase >= 0.5)  {sample = -1;} else {sample = 1;}
}

