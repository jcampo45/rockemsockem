#include <iostream>
#include "BlackGPIO.h"
#include "BlackI2C.h"

int main(int argc, char **argv){
  
  if (argc != 3){
    std::cout << "Usage: ./punchTest <regAddr (0xN)> <thresh>" << std::endl;
    exit(-1);
  }

  uint8_t imuAddr   = 0x68;
  uint8_t muxAddr   = 0x70;
  uint8_t readAddr  = strtol(argv[1], NULL, 16);
  uint8_t thresh    = atoi(argv[2]);

  BlackLib::BlackI2C muxWriter(BlackLib::I2C_2, muxAddr);
  
  BlackLib::BlackGPIO solenoidR(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
  BlackLib::BlackGPIO solenoidL(BlackLib::GPIO_68, BlackLib::output, BlackLib::FastMode);
  
  muxWriter.writeByte(0x00, 0x01);
  BlackLib::BlackI2C imuReader(BlackLib::I2C_2, imuAddr);
  imuReader.writeByte(0x6B, 0);

  muxWriter.writeByte(0x00, 0x02);
  BlackLib::BlackI2C imuReader(BlackLib::I2C_2, imuAddr);
  imuReader.writeByte(0x6B, 0);

  int val;
  while(1){
    
    muxWriter.writeByte(0x00,0x01);
  BlackLib::BlackI2C imuReader(BlackLib::I2C_2, imuAddr);    
    val = imuReader.readByte(readAddr);
    std::cout<<val<<std::endl;
    if(abs(val) > thresh){
      solenoidL.setValue(BlackLib::high);
    }

    muxWriter.writeByte(0x00,0x02);
      BlackLib::BlackI2C imuReader(BlackLib::I2C_2, imuAddr);
    val = imuReader.readByte(readAddr);
    if(abs(val) > thresh){
      solenoidR.setValue(BlackLib::high);
    }

    usleep(100000);
    solenoidL.setValue(BlackLib::low);
    solenoidR.setValue(BlackLib::low);
    usleep(10000);
    
  }

}
