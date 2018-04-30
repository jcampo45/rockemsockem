#include "BlackI2C.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv){
  int leftImu = 1;
  int rightImu = 2;
  int headImu = 4;
  int imuAddr = 0x68;
  int muxAddr = 0x70;
  
  BlackLib::BlackI2C* imuReader = new BlackLib::BlackI2C(BlackLib::I2C_2, muxAddr);
  imuReader->open(BlackLib::ReadWrite);  

  imuReader->writeByte(0, leftImu);
  imuReader->setDeviceAddress(imuAddr);
  imuReader->writeByte(0x6B, 0);

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, rightImu);
  imuReader->setDeviceAddress(imuAddr);
  imuReader->writeByte(0x6B, 0);

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, headImu);
  imuReader->setDeviceAddress(imuAddr);
  imuReader->writeByte(0x6B, 0);

  int i=0;
  int v;
  while(i<300){
    v = imuReader->readByte(0x03B);
    std::cout << v << std::endl;
    usleep(10000);
    i++;
  }

  i=0;
  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, rightImu);
  imuReader->setDeviceAddress(imuAddr);
  
  while(i<300){
    v = imuReader->readByte(0x03B);
    std::cout << v << std::endl;
    usleep(10000);
    i++;
  }

  i=0;
  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, leftImu);
  imuReader->setDeviceAddress(imuAddr);
  
  while(i<300){
    v = imuReader->readByte(0x03B);
    std::cout << v << std::endl;
    usleep(10000);
    i++;
  }
  
}
