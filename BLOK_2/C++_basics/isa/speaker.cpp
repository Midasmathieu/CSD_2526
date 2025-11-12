#include "speaker.h"

Speaker::Speaker(){
  std::cout << "speaker constructor sir-mam-person\n";
  subDiameter = 0;
  subConePos = 0;
  tweeterDiameter = 0;
  tweeterConePos = 0;
}

void Speaker::info(){
  std::cout << "subDiameter: " << subDiameter << std::endl << "subPos: " <<
    subConePos << std::endl << "tweeterDiameter: " << tweeterDiameter <<
    std::endl << "tweeterPos: " << tweeterConePos << std::endl;
}
