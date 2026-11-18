#include "integrator.h"

Integrator::Integrator()
{ std::cout << "integrator constructor" << std::endl; }

Integrator::~Integrator()
{ std::cout << "integrator destructor" << std::endl; }

void Integrator::setFrequency(float freq)
{
  frequency = freq;
  float time = 1.0 / freq;
  Vin = -(capacitor * resistor * 8) / time;
  std::cout << Vin << std::endl;
}

void Integrator::tick()
{
  phase += frequency / samplerate;
  calculateVout();

  if(phase >= 1.0f) 
  { 
    phase -= 1.0f;
    //std::cout << Vout << std::endl;
    Vout = 0;
    //TODO: let tick of oscillator call calculate sample of child class
  }
}


float Integrator::getSample()
{
  return Vout * 0.25 - 1;
}

float Integrator::getVout()
{
  return Vout;
}

void Integrator::calculateVout() 
{
  Vout = -Vin * deltaTime / (resistor * capacitor) + Vout;
  //std::cout << Vin << ", " << deltaTime << ", " << resistor << ", " << capacitor << std::endl;


  if(Vout > 10) { Vout = 10; std::cout << "CLIPPING@!!!!!!" << std::endl; }
}
