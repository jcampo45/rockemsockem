#include "robot.h"

Robot::Robot(int x): points(100), pitchDodge(0), rollDodge(0){
  if(x==1){

    headShotLat = new BlackLib::BlackADC(BlackLib::AIN0);
    headShotAnt = new BlackLib::BlackADC(BlackLib::AIN1);

  }else{
    headShotLat = new BlackLib::BlackADC(BlackLib::AIN2);
    headShotAnt = new BlackLib::BlackADC(BlackLib::AIN3);

  }
}

short Robot::checkPunches(){
  return 0;
}

void Robot::punch(short ps){

}

void Robot::checkHits(){
  int headlat = headShotLat->getNumericValue();
  int headant = headShotAnt->getNumericValue();
  points = points - headlat - headant;
}

void Robot::unpunch(short ps){

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

