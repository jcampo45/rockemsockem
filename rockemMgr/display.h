#include "BlackI2C.h"
#include <map>

class Display{

 public:
  
  Display();
  ~Display();
  
  void set(char a, char b, char c, char d, char e);
  void flash();
  void solid();
  void init();
  void hello();

 private:
  
  BlackLib::BlackI2C* disp;
  std::map<char, int> lib;

};
