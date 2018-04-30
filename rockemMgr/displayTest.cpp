#include "display.h"

int main(int argc, char** argv){

  Display d = Display();
  sleep(1);
  d.init();
  sleep(1);
  d.hello();

}
