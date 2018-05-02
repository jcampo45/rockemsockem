#include <iostream>
#include <string>
#include <unistd.h>
#include "BlackI2C.h"

int main(int argc, char **argv){

  if (argc != 4){
    std::cout << "Usage: ./imuRead <i2c port (0,1,2)> <deviceAddr (0xN)> <regAddr (0xN)>" << std::endl;
    exit(-1);
  }
  uint8_t imuAddr = strtol(argv[2], NULL, 16);
  uint8_t readAddr = strtol(argv[3], NULL, 16);
  uint8_t i2c = atoi(argv[1]);
  BlackLib::i2cName iport = (i2c == 2) ? BlackLib::I2C_2 : ((i2c == 1) ? BlackLib::I2C_1 : BlackLib::I2C_0);
  std::cout << iport << std::endl;
  
  BlackLib::BlackI2C imuReader(iport, imuAddr);
  std::cout << imuReader.open(BlackLib::ReadWrite) << std::endl;
  imuReader.writeByte(0x6B, 0);
  imuReader.writeByte(0x1B, 0);
  imuReader.writeByte(0x1B, 0);
  
  int val;
  while(1){
    usleep(100000);
    val = imuReader.readByte(readAddr);
    std::cout << val << std::endl;
  }
}
