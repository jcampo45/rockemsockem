#include "robot.h"

const int punchThresh        = 90;
const int leftThresh         = 40;
const int rightThresh        = -40;
const int frontThresh        = 40;
const int backThresh         = -40; 

const int rollsR[3]          = {60,50,40};
const int pitchesR[3]        = {60,50,40};
const int rollsB[3]          = {60,50,40};
const int pitchesB[3]        = {60,50,40};

const uint8_t muxAddr        = 0x70;
const uint8_t imuAddr        = 0x68;
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

Robot::Robot(int x): points(25){
  
  if(x==1){

    headShotFB  = new BlackLib::BlackADC(BlackLib::AIN0);
    headShotLR  = new BlackLib::BlackADC(BlackLib::AIN2);
    chest1      = new BlackLib::BlackGPIO(BlackLib::GPIO_49, BlackLib::output, BlackLib::FastMode);
    chest2      = new BlackLib::BlackGPIO(BlackLib::GPIO_117, BlackLib::output, BlackLib::FastMode);
    chest3      = new BlackLib::BlackGPIO(BlackLib::GPIO_125, BlackLib::output, BlackLib::FastMode);
    leftSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_15, BlackLib::output, BlackLib::FastMode);
    rightSol    = new BlackLib::BlackGPIO(BlackLib::GPIO_14, BlackLib::output, BlackLib::FastMode);
    headSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_113, BlackLib::output, BlackLib::FastMode);
    pitchServo  = new BlackLib::BlackPWM(BlackLib::P9_14);
    rollServo   = new BlackLib::BlackPWM(BlackLib::P9_16);

    leftImu     = 1 << 0;
    rightImu    = 1 << 1;
    headImu     = 1 << 2;

    std::copy(pitchesB, pitchesB+3, pitchPos);
    std::copy(rollsB, rollsB+3, rollPos);
    
  }else{

    headShotFB  = new BlackLib::BlackADC(BlackLib::AIN1);
    headShotLR  = new BlackLib::BlackADC(BlackLib::AIN3);
    chest1      = new BlackLib::BlackGPIO(BlackLib::GPIO_26, BlackLib::output, BlackLib::FastMode);
    chest2      = new BlackLib::BlackGPIO(BlackLib::GPIO_46, BlackLib::output, BlackLib::FastMode);
    chest3      = new BlackLib::BlackGPIO(BlackLib::GPIO_65, BlackLib::output, BlackLib::FastMode);
    leftSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
    rightSol    = new BlackLib::BlackGPIO(BlackLib::GPIO_68, BlackLib::output, BlackLib::FastMode);
    headSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_44, BlackLib::output, BlackLib::FastMode);
    pitchServo  = new BlackLib::BlackPWM(BlackLib::P8_13);
    rollServo   = new BlackLib::BlackPWM(BlackLib::P8_19);

    leftImu     = 1 << 3;
    rightImu    = 1 << 4;
    headImu     = 1 << 5;

    std::copy(pitchesB, pitchesB+3, pitchPos);
    std::copy(rollsB, rollsB+3, rollPos);
    
  }

  imuReader = new BlackLib::BlackI2C(BlackLib::I2C_2, muxAddr);
  imuReader->open(BlackLib::ReadWrite);  

  imuReader->writeByte(0, leftImu);
  imuReader->setDeviceAddress(imuAddr);
  imuReader->writeByte(0x6B, 0);

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, rightImu);
  imuReader->setDeviceAddress(imuAddr);
  imuReader->writeByte(PWR_MGMT_1, 0);

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, headImu);
  imuReader->setDeviceAddress(imuAddr);
  imuReader->writeByte(PWR_MGMT_1, 0);

}

short Robot::checkPunches(){

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, leftImu);
  imuReader->setDeviceAddress(imuAddr);
  
  int8_t left = imuReader->readByte(ACCEL_X_OUT_H);

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, rightImu);
  imuReader->setDeviceAddress(imuAddr);

  int8_t right = imuReader->readByte(ACCEL_X_OUT_H);
  
  short result = 0;

  if (left > punchThresh){
    result = result + (1<<8);
  }

  if (right > punchThresh){
    result = result + 1;
  }

  return result;

}

void Robot::punch(short ps){
  if (ps & 1){
    rightSol->setValue(BlackLib::high);
  }
  if (ps & 1<<8){
    leftSol->setValue(BlackLib::high);
  }
}

void Robot::checkHits(){

  int headlat = abs(headShotLR->getNumericValue()-2000)/400;
  int headant = abs(headShotFB->getNumericValue()-2000)/400;
  int c1      = chest1->getNumericValue();
  int c2      = chest2->getNumericValue();
  int c3      = chest3->getNumericValue();

  points      = points - std::max(5,headlat+headant) - c1 - c2 - c3;

}

void Robot::unpunch(short ps){
  
  if (ps & 1){
    rightSol->setValue(BlackLib::low);
  }
  if (ps & 1<<8){
    leftSol->setValue(BlackLib::low);
  }

}

void Robot::dodge(){
  
  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, leftImu);
  imuReader->setDeviceAddress(imuAddr);
  
  int8_t dodgeLR = imuReader->readByte(ACCEL_X_OUT_H);
  int8_t dodgeFB = imuReader->readByte(ACCEL_Z_OUT_H);

  if (dodgeFB > frontThresh){}
    //    pitchServo->;
  if (dodgeFB < backThresh){}
    //pitchServo->;
  if ((frontThresh > dodgeFB) && (dodgeFB > backThresh)){}
    //pitchServo->;
  
  if (dodgeLR > leftThresh){}
    //rollServo->;
  if (dodgeLR < rightThresh){}
    //rollServo->;
  if ((leftThresh > dodgeLR) && (dodgeLR > rightThresh)){}
    //rollServo->;
}

void Robot::die(){

}

void Robot::win(){

}

Robot::~Robot(){

  delete headShotFB;
  delete headShotLR;
  delete chest1;
  delete chest2; 
  delete chest3;
  delete leftSol;
  delete rightSol;
  delete headSol;
  delete pitchServo;
  delete rollServo;

}
