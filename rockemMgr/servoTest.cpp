#include <unistd.h>
#include "BlackPWM.h"

int main(int argc, char** argv){

  BlackLib::BlackPWM* s = new BlackLib::BlackPWM(BlackLib::P9_14);

  s->setPeriodTime(20000000);
  float p = 10.0;
  while(p<90){
    s->setDutyPercent(p);
    usleep(50000);
    s++;
  }

}
