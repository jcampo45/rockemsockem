#include "robot.h"

int main(int argc, char **argv){
  
  // Initialize left robot
  Robot leftRobot = Robot(1);

  // Initialize right robot
  Robot rightRobot = Robot(2);

  short lp, rp;

  // This loop must run slow enough to:
  //   check for punch
  //   punch
  //   check for hits
  //   retract
  //   sense for dodging
  //   dodge
  //
  // Must run fast enough that punches and dodges don't get missed (often)
  // Means you can punch at same time or after last punch thrown is retracted 
  while(leftRobot.points>0 && rightRobot.points>0){
  
    // Check for punches
    lp = leftRobot.checkPunches();
    rp = rightRobot.checkPunches();

    // Punch
    leftRobot.punch(lp);
    rightRobot.punch(rp);
    
    // Pause for extension
    usleep(1000);
    
    // Register hit
    leftRobot.checkHits();
    rightRobot.checkHits();

    // Retract
    leftRobot.unpunch(lp);
    rightRobot.unpunch(rp);

    // Check for and execute dodge
    leftRobot.dodge();
    rightRobot.dodge();

    // Update display
    leftRobot.update();
    rightRobot.update();
    
  }

  // Show winner
  if(leftRobot.points>0){

    rightRobot.die();
    leftRobot.win();

  }else{

    leftRobot.die();
    rightRobot.win();

  }

  return 0;
}
