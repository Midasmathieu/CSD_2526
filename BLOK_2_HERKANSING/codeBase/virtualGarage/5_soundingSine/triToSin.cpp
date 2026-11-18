#include "triToSin.h"

TriToSin::TriToSin()
{ std::cout << "TriToSin::constructor" << std::endl; } 
TriToSin::~TriToSin()
{ std::cout << "TriToSin::destructor" << std::endl; }

float TriToSin::applyShaper(float input) 
{
  return atan(2*input)*0.9;
}
