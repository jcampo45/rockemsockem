#include <iostream>
#include <unistd.h>
#include "BlackADC.h"

int main(int argc, char **argv){
  BlackLib::BlackADC LA(BlackLib::AIN0);
  BlackLib::BlackADC LS(BlackLib::AIN2);
  BlackLib::BlackADC RA(BlackLib::AIN1);
  BlackLib::BlackADC RS(BlackLib::AIN3);

  int lav, lsv, rav, rsv;
  
  while(1){
    lav = LA.getNumericValue()/40;
    lsv = LS.getNumericValue()/40;
    rav = RA.getNumericValue()/40;
    rsv = RS.getNumericValue()/40;

    std::cout << lav << " :: " << lsv << " :: " << rav << " :: " << rsv << std::endl;
    usleep(100000);
  }
}
