#include <iostream>
#include "jbl.h"


int main() {
  // Speaker aSpeaker;
  // aSpeaker.subDiameter = 5;
  // aSpeaker.subConePos = 0.5;
  // aSpeaker.tweeterDiameter = 2.5;
  // aSpeaker.tweeterConePos = -0.5;
  Jbl aJbl("hifive");

  aJbl.subDiameter = 5;
  aJbl.info();
  aJbl.blast();
  //
  // aSpeaker.info();
  return 0;
}
