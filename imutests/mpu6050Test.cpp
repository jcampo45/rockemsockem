//BBB-MPU6050.cpp
//by OP from teachmemicro.com

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream> //+: for output file
#include <stdexcept>
#include <cstring>
#include <string>
#include <memory>
#include <array>

using namespace std;

int16_t accel_x;
int16_t accel_y;
int16_t accel_z;
int16_t gyro_x;
int16_t gyro_y;
int16_t gyro_z;

const char* deviceADDR = " 0x68 ";
const char* PWR_MGMT_1 = " 0x6B ";
const char* ACCEL_X_OUT_H = " 0x3B ";
const char* ACCEL_X_OUT_L = " 0x3C ";
const char* ACCEL_Y_OUT_H = " 0x3D ";
const char* ACCEL_Y_OUT_L = " 0x3E ";
const char* ACCEL_Z_OUT_H = " 0x3F ";
const char* ACCEL_Z_OUT_L = " 0x40 ";
const char* GYRO_X_OUT_H = " 0x43 ";
const char* GYRO_X_OUT_L = " 0x44 ";
const char* GYRO_Y_OUT_H = " 0x45 ";
const char* GYRO_Y_OUT_L = " 0x46 ";
const char* GYRO_Z_OUT_H = " 0x47 ";
const char* GYRO_Z_OUT_L = " 0x48 ";

const char* cmdGet = "i2cget -y 2";
const char* cmdSet = "i2cset -y 2";

//exec function that runs bash commands in c++
string exec(char* cmd) {
  string data;
  FILE * stream;
  const int max_buffer = 256;
  char buffer[max_buffer];
  strcat(cmd," 2>&1");
  stream = popen(cmd, "r");

  if (stream) {
    while (!feof(stream))
      if (fgets(buffer, max_buffer, stream) != NULL) 
	data.append(buffer);
    pclose(stream);
  }
  return data;
}

//function that performs geti2c
string get(const char* reg1, const char* reg2){
  char str[100];
  string str2;

  strcpy(str, cmdGet);
  strcat(str, reg1);
  strcat(str, reg2);

  str2 = exec(str);
  return str2;
}

//function that performs seti2c
void set(const char* reg1, const char* reg2, int value){
  char str[100];
  string str2;

  strcpy(str, cmdSet);
  strcat(str, reg1);
  strcat(str, reg2);
  strcat(str, to_string(value).c_str());

	
  str2 = exec(str);
}//CHANGE

int main(){

  
  set(deviceADDR, PWR_MGMT_1, 0);//turn on the MPU6050
  system("i2cdump 2 0x68");

  //+:Configure LED
  std::fstream fs;
  fs.open ("/sys/kernel/debug/omap_mux/gpmc_ad4"); fs << "7"; fs.close();
  fs.open("/sys/class/gpio/export"); fs << 67; fs.close();
  fs.open("/sys/class/gpio/gpio67/direction"); fs << "out"; fs.close();
        
  //+: create export files
  ofstream out_XAccel,  out_YAccel,  out_ZAccel,
    out_XGyro, out_YGyro, out_ZGyro;
  out_XAccel.open("Accel_X.txt"); out_YAccel.open("Accel_Y.txt"); out_ZAccel.open("Accel_Z.txt");
  out_XGyro.open("Gyro_X.txt"); out_YGyro.open("Gyro_Y.txt"); out_ZGyro.open("Gyro_Z.txt");
	
  while(true){
    fs.open("/sys/class/gpio/gpio67/value"); fs << "0"; fs.close();
    
    accel_x = stoi(get(deviceADDR, ACCEL_X_OUT_H), nullptr, 
		   16) << 8 + stoi(get(deviceADDR, ACCEL_X_OUT_L), nullptr, 16);
    accel_y = stoi(get(deviceADDR, ACCEL_Y_OUT_H), nullptr, 
		   16) << 8 + stoi(get(deviceADDR, ACCEL_Y_OUT_L), nullptr, 16);
    accel_z = stoi(get(deviceADDR, ACCEL_Z_OUT_H), nullptr, 
		   16) << 8 + stoi(get(deviceADDR, ACCEL_Z_OUT_L), nullptr, 16);
    accel_x = accel_x / 8192;
    accel_y = accel_y / 8192;
    accel_z = accel_z / 8192;

    //+: LED Control
    if(accel_x != 0) {
      cout << "condition is true" << endl;
      fs.open("/sys/class/gpio/gpio67/value"); fs << "1"; fs.close(); 
    }


    gyro_x = stoi(get(deviceADDR, GYRO_X_OUT_H), nullptr, 
		  16) << 8 + stoi(get(deviceADDR, GYRO_X_OUT_L), nullptr, 16);
    gyro_y = stoi(get(deviceADDR, GYRO_Y_OUT_H), nullptr, 
		  16) << 8 + stoi(get(deviceADDR, GYRO_Y_OUT_L), nullptr, 16);
    gyro_z = stoi(get(deviceADDR, GYRO_Z_OUT_H), nullptr, 
		  16) << 8 + stoi(get(deviceADDR, GYRO_Z_OUT_L), nullptr, 16);
    gyro_x = gyro_x / 66;
    gyro_y = gyro_y / 66;
    gyro_z = gyro_z / 66;

    /*cout << "X-acc: " << accel_x << " Y-acc: " << accel_y << 
      " Z-acc: " << accel_z << endl;
      cout << "X-gyro: " << gyro_x << " Y-gyro: " << gyro_y << 
      " Z-gyro: " << gyro_z << endl;*/
		
    //+: Write to export file
    //outputFile << "X-Acc: " << accel_x << endl;
    out_XAccel << accel_x << endl; out_YAccel << accel_y << endl; out_ZAccel << accel_z << endl;
    out_XGyro << gyro_x <<endl; out_YGyro << gyro_y <<endl; out_ZGyro << gyro_z <<endl;
  }
  
  /*+: Close File
  cout << "made it to end" << endl;
  fs.open("/sys/class/gpio/gpio67/value");
  fs << "0";
  fs.close();
  out_XAccel.close(); out_YAccel.close(); out_ZAccel.close();
  out_XGyro.close(); out_YGyro.close(); out_ZGyro.close();*/
	
  return 0;
}
