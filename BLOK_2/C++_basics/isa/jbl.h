#include "speaker.h"

class Jbl : public Speaker
{
public:
  Jbl(std::string name);
  ~Jbl();

  void blast();
};
