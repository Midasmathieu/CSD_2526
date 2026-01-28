#include <iostream>
#include <cmath>


class Oscillator {
public:
  Oscillator() { std::cout << "Oscillator constructor" << std::endl; }

  void play(float frequency){
    std::cout << "playing at frequency: " << frequency << std::endl;
  }
  void setFrequency(float frequency);
  float getFrequency();
  float getSample();
  float setPhase();
};



class Sine : public Oscillator {
public:


private:
  float calculate();
  float phase();
  float sample();


};


class Synth {
public:
  Synth() : oscillator() { std::cout << "Synth constructor" << std::endl; }
  ~Synth(){ std::cout << "Synth destructor" << std::endl; }

  Sine oscillator;

  void setFrequency(float a){
    frequency = a;
  }

  float getFrequency(){
    return frequency;
  }

  float mtof(float midiNote){
    float note =  midiNote - 69;
    float power = note/12;
    float frequency = 440 * pow(2, power);
    setFrequency(frequency);
    return frequency;

  }

  void play(){
    oscillator.play(frequency);
  }

private:
  float frequency;
  float midiNote;
};

int main() {
  Synth moog;
  // std::cout << moog.mtof(100.0) << std::endl;
  moog.mtof(100.0);
  moog.play();

}
