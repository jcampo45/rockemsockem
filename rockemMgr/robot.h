#include "BlackPWM.h"
#include "BlackGPIO.h"
#include "BlackI2C.h"
#include "BlackADC.h"

class Robot{

public:
  
  Robot(int player);
  ~Robot();
  
  short checkPunches();
  void punch(short ps);
  void checkHits();
  void unpunch(short ps);
  void dodge();
  void update();
  void die();
  void win();

  int points;
  int pitchDodge;
  int rollDodge;
  
private:
  /*
  int leftPunch();
  int rightPunch();
  int rollDodge(int pos);
  int pitchDodge(int po);

  int checkHead();
  int checkChest();
  int checkLeftPunch();
  int checkRightPunch();
  int checkPitchDodge();
  int checkRollDodge();


  BlackLib::BlackI2C rightImu;
  BlackLib::BlackI2C dodgeImu;
  BlackLib::BlackPWM dodgePitch;
  BlackLib::BlackPWM dodgeRoll;
  */

  BlackLib::BlackGPIO *imuSig0;
  BlackLib::BlackGPIO *imuSig1;
  BlackLib::BlackI2C *imuReader;
  BlackLib::BlackADC *headShotLat;
  BlackLib::BlackADC *headShotAnt;
  BlackLib::BlackGPIO *chestShot;
  BlackLib::BlackGPIO *leftSol;
  BlackLib::BlackGPIO *rightSol;
};
