#include <stdio.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <time.h>
#include "BlackI2C.h"

const uint8_t PWR_MGMT_1     = 0x6B;
const uint8_t ACCEL_X_OUT_H  = 0x3B;
const uint8_t ACCEL_X_OUT_L  = 0x3C;
const uint8_t ACCEL_Y_OUT_H  = 0x3D;
const uint8_t ACCEL_Y_OUT_L  = 0x3E;
const uint8_t ACCEL_Z_OUT_H  = 0x3F;
const uint8_t ACCEL_Z_OUT_L  = 0x40;
const uint8_t GYRO_X_OUT_H   = 0x43;
const uint8_t GYRO_X_OUT_L   = 0x44;
const uint8_t GYRO_Y_OUT_H   = 0x45;
const uint8_t GYRO_Y_OUT_L   = 0x46;
const uint8_t GYRO_Z_OUT_H   = 0x47;
const uint8_t GYRO_Z_OUT_L   = 0x48;

int main(int argc, char **argv){

  if (argc != 3){
    std::cout << "Usage: ./motionTrace <deviceAddr (0xN)> <filename>" << std::endl;
    exit(-1);
  }
  uint8_t imuAddr = strtol(argv[1], NULL, 16);
  char* filename = argv[2];

  BlackLib::BlackI2C imuReader(BlackLib::I2C_2, imuAddr);
  std::cout << imuReader.open(BlackLib::ReadWrite) << std::endl;
  imuReader.writeByte(0x6B, 0);
  imuReader.writeByte(0x1B, 0);
  imuReader.writeByte(0x1C, 0);

  int AXH[1000], AXL[1000], AYH[1000], AYL[1000], AZH[1000], AZL[1000];
  int GXH[1000], GXL[1000], GYH[1000], GYL[1000], GZH[1000], GZL[1000];
  float t[100];
  int i=0;
  clock_t c;

  while(i<1000){

    c = clock();
    AXH[i] = imuReader.readByte(ACCEL_X_OUT_H);
    AXL[i] = imuReader.readByte(ACCEL_X_OUT_L);
    AYH[i] = imuReader.readByte(ACCEL_Y_OUT_H);
    AYL[i] = imuReader.readByte(ACCEL_Y_OUT_L);
    AZH[i] = imuReader.readByte(ACCEL_Z_OUT_H);
    AZL[i] = imuReader.readByte(ACCEL_Z_OUT_L);
    GXH[i] = imuReader.readByte(GYRO_X_OUT_H);
    GXL[i] = imuReader.readByte(GYRO_X_OUT_L);
    GYH[i] = imuReader.readByte(GYRO_Y_OUT_H);
    GYL[i] = imuReader.readByte(GYRO_Y_OUT_L);
    GXH[i] = imuReader.readByte(GYRO_Z_OUT_H);
    GZL[i] = imuReader.readByte(GYRO_Z_OUT_L);
    
    if (i%100==0){
      std::cout<<clock()<<std::endl;
    }

    usleep(10000);
    i++;
    t[i]   = ((float)(clock() - c))/CLOCKS_PER_SEC;
  
  }

  i=0;
  FILE* fd = fopen(filename,"w");

  while(i<10000){
    char buf[4096];
    sprintf(buf,"%f, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\r\n", t[i], AXH[i], AXL[i], AYH[i], AYL[i], AZH[i], AZL[i], GXH[i], GXL[i], GYH[i], GYL[i], GZH[i], GZL[i]);
    fwrite(buf,sizeof(char), strlen(buf), fd);
    i++;
  }
}
