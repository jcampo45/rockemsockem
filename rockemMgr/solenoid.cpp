#include "BlackLib/BlackGPIO/BlackGPIO.h"
#include <unistd.h>

int main(int argc, char **argv){

  BlackLib::BlackGPIO solenoidR(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidL(BlackLib::GPIO_68, BlackLib::output, BlackLib::FastMode);

  while(1){
    solenoidL.setValue(BlackLib::high);
    usleep(100000);
    solenoidL.setValue(BlackLib::low);
    sleep(1);
    solenoidR.setValue(BlackLib::high);
    usleep(100000);
    solenoidR.setValue(BlackLib::low);
    sleep(1);
  }
}
