#include <iostream>
#include <string>
#include <unistd.h>
#include "BlackI2C.h"
#include "BlackGPIO.h"

int main(int argc, char **argv){

  if (argc != 3){
    std::cout << "Usage: ./onePunch <regAddr (0xN)> <thresh>" << std::endl;
    exit(-1);
  }
  int thresh = atoi(argv[2]);
  uint8_t imuAddr = 0x68;
  uint8_t readAddr = strtol(argv[1], NULL, 16);
  BlackLib::i2cName iport = BlackLib::I2C_2;

  BlackLib::BlackGPIO solenoidL(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackI2C imuReader(iport, imuAddr);

  std::cout << imuReader.open(BlackLib::ReadWrite) << std::endl;
  imuReader.writeByte(0x6B, 0);

  int val;
  while(1){
    usleep(200000);
    val = imuReader.readByte(readAddr);
    std::cout << val << std::endl;
    if(abs(val) > thresh){
      solenoidL.setValue(BlackLib::high);
      usleep(150000);
      solenoidL.setValue(BlackLib::low);
    }
  }
}
