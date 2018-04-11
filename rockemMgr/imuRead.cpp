#include <iostream>
#include <string>
#include "BlackI2C.h"
using namespace std;

int main(int argc, char **argv){

  if (argc != 4){
    cout << "Usage: ./imuRead <i2c port (0,1)> <deviceAddr (0xN)> <regAddr (0xN)>" << endl;
    exit(-1);
  }
  uint8_t imuAddr = atoi(argv[2]);
  uint8_t readAddr = atoi(argv[3]);
  uint8_t i2c = atoi(argv[1]);
  BlackLib::i2cName iport = (i2c == 1) ? BlackLib::I2C_1 : BlackLib::I2C_0;

  BlackLib::BlackI2C imuReader(iport, imuAddr);
  imuReader.open(BlackLib::ReadWrite);
  imuReader.writeByte(0x6B, 0);

  while(1){
    cout << imuReader.readByte(readAddr) << endl;
  }
}
