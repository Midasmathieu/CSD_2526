#include <iostream>
#include "speaker.h"


int main() {
  Speaker aSpeaker;
  aSpeaker.subDiameter = 5;
  aSpeaker.subConePos = 0.5;
  aSpeaker.tweeterDiameter = 2.5;
  aSpeaker.tweeterConePos = -0.5;
  aSpeaker.info();
  return 0;
}
