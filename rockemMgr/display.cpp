#include "display.h"

Display::Display(){

  lib = std::map<char, int>();
  lib[':'] = 0x03;
  lib[0] = 0x3F;
  lib[1] = 0x06;
  lib[2] = 0x5B;
  lib[3] = 0x4F;
  lib[4] = 0x66;
  lib[5] = 0x6D;
  lib[6] = 0x7D;
  lib[7] = 0x07;
  lib[8] = 0x7F;
  lib[9] = 0x6F;
  lib['a'] = 0x5F;
  lib['A'] = 0x77;
  lib['b'] = 0x7C;
  lib['c'] = 0x58;
  lib['C'] = 0x39;
  lib['d'] = 0x5E;
  lib['E'] = 0x79;
  lib['F'] = 0x71;
  lib['h'] = 0x74;
  lib['H'] = 0x76;

  disp = new BlackLib::BlackI2C(BlackLib::I2C_2, 0x72);

  this->init();
  this->hello();
  this->flash();

}

void Display::init(){

  disp->open( BlackLib::ReadWrite | BlackLib::NonBlock );
  
  bool i=true;
  i = disp->writeByte(0x21, 1);
  if (!i)
    printf("osc write fail");
  disp->writeByte(0x81, 1);
  if (!i)
    printf("solid write fail");
  disp->writeByte(0xEF, 1);
  if (!i)
    printf("bright write fail");
  
}

void Display::flash(){

  disp->writeByte(0x85, 1);

}

void Display::solid(){
  
  disp->writeByte(0x81, 1);

}

void Display::set(char a, char b, char c, char d, char e){

  disp->writeByte(0x00, lib[a]);
  disp->writeByte(0x02, lib[b]);
  disp->writeByte(0x04, lib[c]);
  disp->writeByte(0x06, lib[d]);
  disp->writeByte(0x08, lib[e]);

}

void Display::hello(){

  this->set('H',1,':','H',1);

}

Display::~Display(){

  disp->writeByte(0x20,1);
  delete disp;
  
}
