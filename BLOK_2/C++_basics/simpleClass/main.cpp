#include <iostream>

class Synth{
private:
  int freq = 0;

  440*2^macht
  int mtof(freq){

  }

public:
  void setFreq(float freq){
    if(freq < 12){
      this->freq = 12;
    }
    else if(freq > 24){
      this->freq = 24;
    }
    else{
      this->freq = freq;
    }
  }

  float getFreq(){
    return freq;
  }

  void play(){
    std::cout << "playing right now\n";
  }
  void stop(std::string note){
    std::cout << "stopping right now " << note;

  }
};

class AdditiveSynth : public Synth{
private:
  int voices;
  // int calculateOvertone(int freq, int voices){
  //   freq
  // }

public:
  int setVoices(int voices){
    this->voices = voices;
    return 0;
  }
  int getVoices(){
    return voices;
  }
};

int main(){
  AdditiveSynth Synth1;
  Synth1.setFreq(14.0);

  Synth1.play();

  std::cout << Synth1.getFreq()
               << "\n";
  Synth1.stop("high note\n");

  return 0;
}
