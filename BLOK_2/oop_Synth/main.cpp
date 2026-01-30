#include "callback.h"
#include <iostream>
#include <thread>



int main() {
  ScopedMessageThreadEnabler scopedMessageThreadEnabler;
  CustomCallback audioSource(44100);

  JUCEModule juceModule(audioSource);
  juceModule.init(1, 1);

  std::cout << "Press q + Enter to quit program..." <<std::endl;
  bool running = true;
  while(running) {
    switch (std::cin.get()) {
      case 'q':
        running = false;
    }
  }
  return 0;
  // Sine sine(100.0, 44100);
  // sine.setFrequency();
  // sine.setSamplerate();
  // std::cout << sine.getSample() << std::endl;
  // sine.tick();
  // std::cout << sine.getSample() << std::endl;
  // sine.tick();
  // std::cout << sine.getSample() << std::endl;
}
