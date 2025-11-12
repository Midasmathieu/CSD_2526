#include "jbl.h"

Jbl::Jbl(std::string name){
  std::cout << "constructor, name: " << name << std::endl;
}

Jbl::~Jbl(){
  std::cout << "doekadung\n";
}

void Jbl::blast(){
  std::cout << "housemusic is music that buys you a house...\n";
}
