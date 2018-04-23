#include "BlackLib/BlackGPIO/BlackGPIO.h"
#include <unistd.h>

int main(int argc, char **argv){

  BlackLib::BlackGPIO solenoidBR(BlackLib::GPIO_15, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidBL(BlackLib::GPIO_14, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidBH(BlackLib::GPIO_113, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidRR(BlackLib::GPIO_68, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidRL(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidRH(BlackLib::GPIO_44, BlackLib::output, BlackLib::FastMode);

  while(1){
    solenoidBL.setValue(BlackLib::high);
    usleep(100000);
    solenoidBL.setValue(BlackLib::low);
    sleep(1);
    solenoidBR.setValue(BlackLib::high);
    usleep(100000);
    solenoidBR.setValue(BlackLib::low);
    sleep(1);
    solenoidBH.setValue(BlackLib::high);
    usleep(100000);
    solenoidBH.setValue(BlackLib::low);
    sleep(1);
    solenoidRR.setValue(BlackLib::high);
    usleep(100000);
    solenoidRR.setValue(BlackLib::low);
    sleep(1);
    solenoidRL.setValue(BlackLib::high);
    usleep(100000);
    solenoidRL.setValue(BlackLib::low);
    sleep(1);
    solenoidRH.setValue(BlackLib::high);
    usleep(100000);
    solenoidRH.setValue(BlackLib::low);
    sleep(1);
  }
}
