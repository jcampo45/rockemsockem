#include "BlackLib/BlackGPIO/BlackGPIO.h"
#include <unistd.h>

int main(int argc, char **argv){

  BlackLib::BlackGPIO solenoid(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);

  while(1){
    solenoid.setValue(BlackLib::high);
    usleep(100000);
    solenoid.setValue(BlackLib::low);
    sleep(1);
  }
}
