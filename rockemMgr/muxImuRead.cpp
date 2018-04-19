#include <iostream>
#include <string>
#include <unistd.h>
#include "BlackI2C.h"
#include "BlackGPIO.h"

using namespace std;

int main(int argc, char **argv){

  if (argc != 4){
    cout << "Usage: ./imuRead <i2c port (0,1)> <deviceAddr (0xN)> <regAddr (0xN)>" << endl;
    exit(-1);
  }

  uint8_t imuAddr = strtol(argv[2], NULL, 16);
  uint8_t readAddr = strtol(argv[3], NULL, 16);
  uint8_t i2c = atoi(argv[1]);
  BlackLib::i2cName iport = (i2c == 2)? BlackLib::I2C_2 : ((i2c == 1) ? BlackLib::I2C_1 : BlackLib::I2C_0);
  BlackLib::BlackGPIO imuSig0(BlackLib::GPIO_49, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO imuSig1(BlackLib::GPIO_117, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO imuSig2(BlackLib::GPIO_125, BlackLib::output, BlackLib::FastMode);


  BlackLib::BlackI2C imuReader(iport, imuAddr);
  imuReader.open(BlackLib::ReadWrite);

  imuSig0.setValue(BlackLib::low);
  imuSig1.setValue(BlackLib::high);
  imuSig2.setValue(BlackLib::low);
  imuReader.writeByte(0x6B, 0);

  int val;
  
  while(1){

    val = imuReader.readByte(readAddr);
    cout << "mux = 0: " << val << endl;
    usleep(50000);
  }
}
