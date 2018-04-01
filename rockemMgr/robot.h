#include "BlackLib/BlackPWM/BlackPWM.h"
#include "BlackLib/BlackGPIO/BlackGPIO.h"
#include "BlackLib/BlackI2C/BlackI2C.h"
#include "BlackLib/BlackADC/BlackADC.h"

class Robot{

public:
  
  Robot(int player);
  
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

  BlackLib::BlackI2C leftImu;
  BlackLib::BlackI2C rightImu;
  BlackLib::BlackI2C dodgeImu;
  BlackLib::BlackPWM dodgePitch;
  BlackLib::BlackPWM dodgeRoll;
  BlackLib::BlackADC headShot;
  BlackLib::BlackGPIO chestShot;
  */
};
