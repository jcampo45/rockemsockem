#include <iostream>
#include <unistd.h>
#include "BlackGPIO.h"

int main(int argc, char **argv){
  BlackLib::BlackGPIO rc1(BlackLib::GPIO_49, BlackLib::input);
  BlackLib::BlackGPIO rc2(BlackLib::GPIO_117, BlackLib::input);
  BlackLib::BlackGPIO rc3(BlackLib::GPIO_125, BlackLib::input);
  BlackLib::BlackGPIO bc1(BlackLib::GPIO_26, BlackLib::input);
  BlackLib::BlackGPIO bc2(BlackLib::GPIO_46, BlackLib::input);
  BlackLib::BlackGPIO bc3(BlackLib::GPIO_65, BlackLib::input);

  int bc1v, bc2v, bc3v, rc1v, rc2v, rc3v;
  
  while(1){
    bc1v = bc1.getNumericValue();
    bc2v = bc2.getNumericValue();
    bc3v = bc3.getNumericValue();
    rc1v = rc1.getNumericValue();
    rc2v = rc2.getNumericValue();
    rc3v = rc3.getNumericValue();

    std::cout << bc1v << " :: " << bc2v << " :: " << bc3v << " :: " << rc1v << " :: " << rc2v << " :: " << rc3v << std::endl;
    usleep(100000);
  }
}
