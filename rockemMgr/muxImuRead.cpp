#include <iostream>
#include <string>
#include "BlackI2C.h"
#include "BlackGPIO.h"

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
  BlackLib::BlackGPIO imuSig0(BlackLib::GPIO_40, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO imuSig1(BlackLib::GPIO_51, BlackLib::output, BlackLib::FastMode);


  BlackLib::BlackI2C imuReader(iport, imuAddr);
  imuReader.open(BlackLib::ReadWrite);

  imuSig0.setValue(BlackLib::low);
  imuSig1.setValue(BlackLib::low);
  imuReader.writeByte(0x6B, 0);

  imuSig0.setValue(BlackLib::high);
  imuSig1.setValue(BlackLib::low);
  imuReader.writeByte(0x6B, 0);

  while(1){

    imuSig0.setValue(BlackLib::low);
    imuSig1.setValue(BlackLib::low);
    cout << "mux = 0: " << imuReader.readByte(readAddr) << endl;

    imuSig0.setValue(BlackLib::high);
    imuSig1.setValue(BlackLib::low);
    cout << "mux = 1: " << imuReader.readByte(readAddr) << endl;

  }
}
