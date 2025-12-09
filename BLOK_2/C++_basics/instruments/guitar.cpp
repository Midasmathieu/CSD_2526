#include "guitar.h"

Guitar::Guitar() {
  std::cout << "guitar constructor\n";
  play();
}

Guitar::~Guitar() {
  std::cout << "guitar destructor\n";
}

void Guitar::shred(){
  std::cout << "shredding right now\n";
}
