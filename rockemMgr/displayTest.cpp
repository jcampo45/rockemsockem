#include "display.h"
#include <unistd.h>

int main(int argc, char** argv){

  Display d = Display();
  sleep(1);
  d.init();
  sleep(1);
  d.hello();
  sleep(1);
  int r = 0;
  int b = 20;
  while(r){
    d.set(b/10, b%10, ':', r/10, r%10);
    r--;
    usleep(100000);
  }
  d.hello();

}
