#include "robot.h"

const int thresh = 50;
const uint8_t imuADDR = 0x68;
const uint8_t PWR_MGMT_1 = 0x6B;
const uint8_t ACCEL_X_OUT_H = 0x3B;
const uint8_t ACCEL_X_OUT_L = 0x3C;
const uint8_t ACCEL_Y_OUT_H = 0x3D;
const uint8_t ACCEL_Y_OUT_L = 0x3E;
const uint8_t ACCEL_Z_OUT_H = 0x3F;
const uint8_t ACCEL_Z_OUT_L = 0x40;
const uint8_t GYRO_X_OUT_H = 0x43;
const uint8_t GYRO_X_OUT_L = 0x44;
const uint8_t GYRO_Y_OUT_H = 0x45;
const uint8_t GYRO_Y_OUT_L = 0x46;
const uint8_t GYRO_Z_OUT_H = 0x47;
const uint8_t GYRO_Z_OUT_L = 0x48;

Robot::Robot(int x): points(100), pitchDodge(0), rollDodge(0){
  if(x==1){

    headShotLat = new BlackLib::BlackADC(BlackLib::AIN0);
    headShotAnt = new BlackLib::BlackADC(BlackLib::AIN1);
    imuReader   = new BlackLib::BlackI2C(BlackLib::I2C_1, imuADDR);
    imuSig0     = new BlackLib::BlackGPIO(BlackLib::GPIO_40, BlackLib::output, BlackLib::FastMode);
    imuSig1     = new BlackLib::BlackGPIO(BlackLib::GPIO_51, BlackLib::output, BlackLib::FastMode);
    leftSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
    rightSol    = new BlackLib::BlackGPIO(BlackLib::GPIO_68, BlackLib::output, BlackLib::FastMode);
    
  }else{

    headShotLat = new BlackLib::BlackADC(BlackLib::AIN2);
    headShotAnt = new BlackLib::BlackADC(BlackLib::AIN3);
    imuReader   = new BlackLib::BlackI2C(BlackLib::I2C_0, imuADDR);
    imuSig0     = new BlackLib::BlackGPIO(BlackLib::GPIO_31, BlackLib::output, BlackLib::FastMode);
    imuSig1     = new BlackLib::BlackGPIO(BlackLib::GPIO_48, BlackLib::output, BlackLib::FastMode);
    leftSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_46, BlackLib::output, BlackLib::FastMode);
    rightSol    = new BlackLib::BlackGPIO(BlackLib::GPIO_65, BlackLib::output, BlackLib::FastMode);

  }

  imuReader->open(BlackLib::ReadWrite);  

  imuSig0->setValue(BlackLib::low);
  imuSig1->setValue(BlackLib::low);
  imuReader->writeByte(PWR_MGMT_1, 0);
  
  imuSig0->setValue(BlackLib::high);
  imuSig1->setValue(BlackLib::low);
  imuReader->writeByte(PWR_MGMT_1, 0);

}

short Robot::checkPunches(){

  imuSig0->setValue(BlackLib::low);
  imuSig1->setValue(BlackLib::low);
  uint8_t left = imuReader->readByte(ACCEL_X_OUT_H);
  imuSig0->setValue(BlackLib::high);
  imuSig1->setValue(BlackLib::low);
  uint8_t right = imuReader->readByte(ACCEL_X_OUT_H);
  
  short result = 0;
  if (left > thresh){
    result = result + (1<<8);
  }
  if (right > thresh){
    result = result;
  }

  return result;

}

void Robot::punch(short ps){
  if (ps){
    rightSol->setValue(BlackLib::high);
  }
  if (ps>>8){
    leftSol->setValue(BlackLib::high);
  }
}

void Robot::checkHits(){
  int headlat = 0;//headShotLat->getNumericValue();
  int headant = 0;//headShotAnt->getNumericValue();
  points = points - headlat - headant - 10;
}

void Robot::unpunch(short ps){
  if (ps){
    rightSol->setValue(BlackLib::low);
  }
  if (ps>>8){
    leftSol->setValue(BlackLib::low);
  }

}

void Robot::dodge(){

}

void Robot::update(){
  //points-=10;
}

void Robot::die(){

}

void Robot::win(){

}

Robot::~Robot(){
  delete headShotLat;
  delete headShotAnt;
  delete imuReader;
  delete imuSig0;
  delete imuSig1;
  delete rightSol;
  delete leftSol;
}
