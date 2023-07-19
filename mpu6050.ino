/*
Code for Gyro
*/

#include "Wire.h"
const int MPU_ADDR=0x68;  //I2C Port for MPU-6050

int16_t acc_x, acc_y, acc_z;
int16_t gyro_x, gyro_y, gyro_z;
int16_t temperature;
float ax,ay,az,gx,gy,gz,temp;

bool printRaw = false;
bool printInfo = true;
bool printAcc = false;
bool printTemp = true;
bool printGyro = false;

char tmp_str[7]; //temp for convert

char* convert_int16_to_str(int16_t i) { // converts int16 to string.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(MPU_ADDR); //begins transmission to I2C slave GY-521
    Wire.write(0x6B);
    Wire.write(0);  //wakes up the MPU-6050
    Wire.endTransmission(true);
}

void loop() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);   //starting with register 0x3B - reference MPU-6050 Register Mp and Descriptions 4.2 p.40
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR,7*2, true);  //request a total of 14 registers
    
    acc_x = Wire.read()<<8 | Wire.read();
    acc_y = Wire.read()<<8 | Wire.read();
    acc_z = Wire.read()<<8 | Wire.read();
    temperature = Wire.read()<<8 | Wire.read();
    gyro_x = Wire.read()<<8 | Wire.read();
    gyro_y = Wire.read()<<8 | Wire.read();
    gyro_z = Wire.read()<<8 | Wire.read();
                
    ax = acc_x/16384.;
    ay = acc_y/16384.;
    az = acc_z/16384.;
    temp = temperature/340. + 36.53;
    gx = gyro_x/131.;
    gy = gyro_y/131.;
    gz = gyro_z/131.;
    
  if(printRaw){
    if(printAcc){
      Serial.print("aX ="); Serial.print(convert_int16_to_str(acc_x));
      Serial.print(" | aY ="); Serial.print(convert_int16_to_str(acc_y));
      Serial.print(" | aZ ="); Serial.print(convert_int16_to_str(acc_z));
    }
    if(printTemp){
      Serial.print(" | T ="); Serial.print(convert_int16_to_str(temperature));
    }
    if(printGyro){
      Serial.print(" | gX ="); Serial.print(convert_int16_to_str(gyro_x));
      Serial.print(" | gY ="); Serial.print(convert_int16_to_str(gyro_y));
      Serial.print(" | gZ ="); Serial.print(convert_int16_to_str(gyro_z));
    }
    Serial.println();
  }
    
  if(printInfo){
    if(printAcc){
      Serial.print("aX ="); Serial.print(ax);  Serial.print("g");
      Serial.print(" | aY ="); Serial.print(ay); Serial.print("g");
      Serial.print(" | aZ ="); Serial.print(az); Serial.print("g");
    }
    if(printTemp){
        Serial.print(" | T ="); Serial.print(temp); Serial.print("°C");
    }
    if(printGyro){
      Serial.print(" | gX ="); Serial.print(gx); Serial.print("°/s");
      Serial.print(" | gY ="); Serial.print(gy); Serial.print("°/s");
      Serial.print(" | gZ ="); Serial.print(gz); Serial.print("°/s");
    }
    Serial.println();
  }
  if(printRaw||printInfo){
    delay(100);
  }
}