#include "BlackPWM.h"
#include "BlackGPIO.h"
#include "BlackI2C.h"
#include "BlackADC.h"

class Robot{

public:
  
  Robot(int player);
  ~Robot();
  
  short checkPunches(int us);
  void punch(short ps);
  void checkHits(int us);
  void unpunch(short ps);
  void dodge();
  void update();
  void die();
  void win();

  int points;
  int pitchPos;
  int rollPos;
  int leftImu;
  int rightImu;
  int headImu;

private:

  BlackLib::BlackI2C *imuReader;
  BlackLib::BlackADC *headShotSide;
  BlackLib::BlackADC *headShotFront;
  BlackLib::BlackGPIO *chest1;
  BlackLib::BlackGPIO *chest2;
  BlackLib::BlackGPIO *chest3;
  BlackLib::BlackGPIO *leftSol;
  BlackLib::BlackGPIO *rightSol;
  BlackLib::BlackGPIO *headSol;
  BlackLib::BlackPWM *pitchServo;
  BlackLib::BlackPWM *rollServo;

};
