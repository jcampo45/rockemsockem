#include "robot.h"

Robot::Robot(int x): points(100), pitchDodge(0), rollDodge(0){
  
}

short Robot::checkPunches(){
  return 0;
}

void Robot::punch(short ps){

}

void Robot::checkHits(){

}

void Robot::unpunch(short ps){

}

void Robot::dodge(){

}

void Robot::update(){
  points-=10;
}

void Robot::die(){

}

void Robot::win(){

}

