#include "robot.h"
#include "display.h"

int main(int argc, char **argv){

  printf("Initializing Robots\n");
  // Initialize left robot
  Robot leftRobot = Robot(1);
  printf("Left Robto Initialized\n");
  
  // Initialize right robot
  Robot rightRobot = Robot(2);
  printf("Right Robto Initialized\n");
  
  // Initialize display
  Display disp = Display();
  printf("Display Initialized");

  disp.set(leftRobot.points/10, leftRobot.points%10, ':', rightRobot.points/10, rightRobot.points%10);

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

    //    printf("Reading Hits\n");
    // Register hit
    leftRobot.checkHits();
    rightRobot.checkHits();
    //    printf("Hits Read\n");

    // Retract
    leftRobot.unpunch(lp);
    rightRobot.unpunch(rp);

    // Check for and execute dodge
    leftRobot.dodge();
    rightRobot.dodge();

    disp.set(leftRobot.points/10, leftRobot.points%10, ':', rightRobot.points/10, rightRobot.points%10);
    
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
