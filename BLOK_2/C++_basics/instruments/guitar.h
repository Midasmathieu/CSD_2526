#include "stringInst.h"


class Guitar : public StringInst
{
public:
  Guitar();
  ~Guitar();
private:
  //fields
  int frets;
  int scalelength;
  std::string sound;
  //methods
  void shred();

};
