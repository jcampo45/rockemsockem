#include "BlackI2C.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char** argv){
  int leftImu = 8;
  int rightImu = 16;
  int headImu = 32;
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


  int l = 0, lp = 0;
  int r = 0, rp = 0;
  int hlr = 0, hlrp = 0;
  while(1){

    imuReader->setDeviceAddress(muxAddr);
    imuReader->writeByte(0, leftImu);
    imuReader->setDeviceAddress(imuAddr);

    lp = l;
    l = imuReader->readByte(0x47); 
    if(lp < 100 && l > 100)
        std::cout << "LEFT" <<std::endl;

    imuReader->setDeviceAddress(muxAddr);
    imuReader->writeByte(0, rightImu);
    imuReader->setDeviceAddress(imuAddr);

    rp = r;
    r = imuReader->readByte(0x47);
    if(rp < 100 && r > 100)
        std::cout << "RIGHT" <<std::endl;
	
    imuReader->setDeviceAddress(muxAddr);
    imuReader->writeByte(0, headImu);
    imuReader->setDeviceAddress(imuAddr);

    hlrp = hlr;
    hlr  = imuReader->readByte(0x3B);
    if(hlr > 42 && hlrp > 42)
        std::cout << "dr" <<std::endl;
    if(hlr < -42 && hlrp < -42)
        std::cout << "dl" <<std::endl;

    usleep(50000);
  }
  
}
