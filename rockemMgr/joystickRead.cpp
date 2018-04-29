#include <iostream>
#include <unistd.h>
#include "BlackADC.h"

int main(int argc, char **argv){
  BlackLib::BlackADC BA(BlackLib::AIN2);
  BlackLib::BlackADC BS(BlackLib::AIN0);
  BlackLib::BlackADC RA(BlackLib::AIN3);
  BlackLib::BlackADC RS(BlackLib::AIN1);

  int bav, bsv, rav, rsv;
  
  while(1){
    bav = BA.getNumericValue()/40;
    bsv = BS.getNumericValue()/40;
    rav = RA.getNumericValue()/40;
    rsv = RS.getNumericValue()/40;

    std::cout << bav << " :: " << bsv << " :: " << rav << " :: " << rsv << std::endl;
    usleep(100000);
  }
}
