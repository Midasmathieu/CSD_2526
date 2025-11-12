#ifndef _SPEAKER_H_
#define _SPEAKER_H_
#include <iostream>

class Speaker
{
public:
  Speaker();
  float subDiameter;
  float subConePos;
  float tweeterDiameter;
  float tweeterConePos;
  void info();
};

#endif
