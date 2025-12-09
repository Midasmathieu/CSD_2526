#include <iostream>

class Note {
public:
  Note() {
    std::cout << "\n holy shit note constructor.\n"
  }

};


int main() {
  Note note;
  std::cout << "\nReached the end of the application.\n";
  //  In c++ maakt het uit of je enkele of dubbele aanhalingstekens gebruikt.
  // \n is newline
};
