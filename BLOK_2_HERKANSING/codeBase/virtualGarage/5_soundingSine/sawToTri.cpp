#include "sawToTri.h"

SawToTri::SawToTri() 
{ std::cout << "SawToTri::constructor" << std::endl; }

SawToTri::~SawToTri() 
{ std::cout << "SawToTri::destructor" << std::endl; }

float SawToTri::applyShaper(float input)
{
  float output = input;
  if(input >= 4) { output = -input + 8; }
  return output * 0.5 - 1;
}
