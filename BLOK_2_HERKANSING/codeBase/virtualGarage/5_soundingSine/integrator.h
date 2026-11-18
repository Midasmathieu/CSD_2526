#ifndef _INTEGRATOR_H_
#define _INTEGRATOR_H_
#include <iostream>
#include <cmath>

class Integrator 
{
 public:
  Integrator();
  ~Integrator();
  
  float getSample();
  float getVout();
  void calculateVout();
  void setFrequency(float freq);
  void tick();

 private:
  float amplitude = 1;
  float sample;
  float Vout = 0;
  float Vin;
  float phase = 0;
  float samplerate = 48000;
  float deltaTime = 1/samplerate;
  float resistor = 220 * pow(10, 3);
  float capacitor = 47 * pow(10, -12);
  float frequency = 100;
};





#endif
