#include "robot.h"
#include "display.h"
#include "pwm.h"

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
  printf("Display Initialized\n");

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
    usleep(5000);
    rp = rightRobot.checkPunches();
    usleep(5000);
    
    // Punch
    leftRobot.punch(lp);
    usleep(5000);
    rightRobot.punch(rp);
    usleep(5000);
    
    // Pause for extension
    usleep(150000);

    //    printf("Reading Hits\n");
    // Register hit
    leftRobot.checkHits();
    usleep(5000);
    rightRobot.checkHits();
    usleep(5000);
    //    printf("Hits Read\n");

    // Retract
    leftRobot.unpunch(lp);
    usleep(5000);
    rightRobot.unpunch(rp);
    usleep(5000);
    
    // Check for and execute dodge
    leftRobot.dodge();
    usleep(5000);
    rightRobot.dodge();
    usleep(5000);
    
    disp.set(leftRobot.points/10, leftRobot.points%10, ':', rightRobot.points/10, rightRobot.points%10);
    
  }

  // Show winner
  if(leftRobot.points>0){
    disp.set(8,8,':','n','n');
    disp.flash();
    rightRobot.dieBegin();
    sleep(1);
    leftRobot.win();
    rightRobot.dieEnd();
  }else{

    disp.set('n','n',':',8,8);
    disp.flash();
    leftRobot.dieBegin();
    sleep(1);
    rightRobot.win();
    leftRobot.dieEnd();

  }

  return 0;
}
