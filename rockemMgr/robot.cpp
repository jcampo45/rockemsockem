
#include "robot.h"

const int punchThresh        = 80;
const int leftThresh         = 27;
const int rightThresh        = -27;
const int frontThresh        = 22;
const int backThresh         = -22; 

const int rollsB[3]          = {1900000,1750000,1650000};
const int pitchesB[3]        = {1000000,960000,900000};
const int rollsR[3]          = {1750000,1550000,1350000};
const int pitchesR[3]        = {2400000,2350000,2280000};

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

Robot::Robot(int x): points(75){
  
  if(x==1){

    headShotFB  = new BlackLib::BlackADC(BlackLib::AIN0);
    headShotLR  = new BlackLib::BlackADC(BlackLib::AIN2);
    chest1      = new BlackLib::BlackGPIO(BlackLib::GPIO_49, BlackLib::input, BlackLib::FastMode);
    chest2      = new BlackLib::BlackGPIO(BlackLib::GPIO_115, BlackLib::input, BlackLib::FastMode);
    chest3      = new BlackLib::BlackGPIO(BlackLib::GPIO_112, BlackLib::input, BlackLib::FastMode);
    leftSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_2, BlackLib::output, BlackLib::FastMode);
    rightSol    = new BlackLib::BlackGPIO(BlackLib::GPIO_15, BlackLib::output, BlackLib::FastMode);
    headSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_14, BlackLib::output, BlackLib::FastMode);
    pitchServo  = new PWM("pwmchip2/", "pwm0/");
    rollServo   = new PWM("pwmchip0/", "pwm1/");

    leftImu     = 1 << 3;
    rightImu    = 1 << 4;
    headImu     = 1 << 5;

    std::copy(pitchesB, pitchesB+3, pitchPos);
    std::copy(rollsB, rollsB+3, rollPos);
    
  }else{

    headShotFB  = new BlackLib::BlackADC(BlackLib::AIN1);
    headShotLR  = new BlackLib::BlackADC(BlackLib::AIN3);
    chest1      = new BlackLib::BlackGPIO(BlackLib::GPIO_26, BlackLib::input, BlackLib::FastMode);
    chest2      = new BlackLib::BlackGPIO(BlackLib::GPIO_46, BlackLib::input, BlackLib::FastMode);
    chest3      = new BlackLib::BlackGPIO(BlackLib::GPIO_65, BlackLib::input, BlackLib::FastMode);
    leftSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_67, BlackLib::output, BlackLib::FastMode);
    rightSol    = new BlackLib::BlackGPIO(BlackLib::GPIO_68, BlackLib::output, BlackLib::FastMode);
    headSol     = new BlackLib::BlackGPIO(BlackLib::GPIO_44, BlackLib::output, BlackLib::FastMode);
    pitchServo  = new PWM("pwmchip5/", "pwm0/");
    rollServo   = new PWM("pwmchip5/", "pwm1/");

    leftImu     = 1 << 0;
    rightImu    = 1 << 1;
    headImu     = 1 << 2;

    std::copy(pitchesR, pitchesR+3, pitchPos);
    std::copy(rollsR, rollsR+3, rollPos);
    
  }

  pitchServo->setPeriod(20000000);
  pitchServo->setDutyCycle(pitchPos[1]);
  pitchServo->enable();
  
  rollServo->setPeriod(20000000);
  rollServo->setDutyCycle(rollPos[1]);
  rollServo->enable();
  
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
  imuReader->writeByte(0x1B, 0);
  imuReader->writeByte(0x1C, 0);
  
}

short Robot::checkPunches(){
  
    
  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, leftImu);
  imuReader->setDeviceAddress(imuAddr);
  
  int8_t left = imuReader->readByte(GYRO_Z_OUT_H);

  imuReader->setDeviceAddress(muxAddr);
  imuReader->writeByte(0, rightImu);
  imuReader->setDeviceAddress(imuAddr);

  int8_t right = imuReader->readByte(GYRO_Z_OUT_H);
  
  short result = 0;

  if (left > punchThresh){
    result = result + (1<<8);
  }

  if (right > punchThresh){
    result = result + 1;
  }
  
  //  _lastLeft = left;
  //  _lastRight = right;
  
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

  points      = points - std::min(5,headlat+headant) - c1 - c2 - c3;

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
  imuReader->writeByte(0, headImu);
  imuReader->setDeviceAddress(imuAddr);
  
  int dodgeLR = imuReader->readByte(ACCEL_X_OUT_H);
  int dodgeFB = imuReader->readByte(ACCEL_Z_OUT_H);
  //  std::cout<<dodgeLR<<std::endl;

  if (dodgeFB >= frontThresh){
    std::cout<<"front"<<std::endl;
    pitchServo->setDutyCycle(pitchPos[0]);
  }
  if (dodgeFB <= backThresh){
    std::cout<<"back"<<std::endl;
    pitchServo->setDutyCycle(pitchPos[2]);
  }
  if ((frontThresh > dodgeFB) && (dodgeFB > backThresh)){
    pitchServo->setDutyCycle(pitchPos[1]);
  }
  
  if (dodgeLR >= leftThresh){
    std::cout<<"left"<<std::endl;
    rollServo->setDutyCycle(rollPos[0]);
  }
  if (dodgeLR <= rightThresh){
    std::cout<<"right"<<std::endl;
    rollServo->setDutyCycle(rollPos[2]);
  }
  if ((leftThresh > dodgeLR) && (dodgeLR > rightThresh)){
    rollServo->setDutyCycle(rollPos[1]);
  }
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
