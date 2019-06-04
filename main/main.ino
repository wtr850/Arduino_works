//ジャイロも実装した完成バージョン

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

// 0と1は使用不可
const int motor1 = 12; // red 
const int motor2 = 13;
const int motor3 = 8;
const int motor4 = 5; //~
const int motor1_r = 4;  // yellow 
const int motor2_r = 3; //~
const int motor3_r = 2;
const int motor4_r = 7;
const int PWM_mot1 = 11; // green (~)
const int PWM_mot2 = 10; //~
const int PWM_mot3 = 9; //~
const int PWM_mot4 = 6; //~

MPU6050 mpu;

bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
VectorFloat gravity;
float ypr[3];

volatile bool mpuInterrupt = false;

void dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {

  Wire.begin();
  Wire.setClock(400000);

  mpu.initialize();
  while(!mpu.testConnection() ){
  }

  devStatus = mpu.dmpInitialize();

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
  
  // preparation for variables
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT); // for testing
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor1_r, OUTPUT);
  pinMode(motor2_r, OUTPUT);
  pinMode(motor3_r, OUTPUT);
  pinMode(motor4_r, OUTPUT);

  //define the speed of digital communication (bps)
  Serial.begin(9600);
}

void loop() {
  // arduino repeats this part permanently

    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();

    if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
      mpu.resetFIFO();
    } else if (mpuIntStatus & 0x02) {
      while (fifoCount < packetSize){
        fifoCount = mpu.getFIFOCount();
      }

    mpu.getFIFOBytes(fifoBuffer, packetSize);        
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    float pitch = ypr[1] * 180/M_PI;
    float roll = ypr[2] * 180/M_PI;
  
    if( 40 < roll && roll < 140 ){
      if( 40 < pitch && pitch < 140 ){  //2 & 3
        digitalWrite(motor1,LOW);
        digitalWrite(motor1_r,LOW);
        digitalWrite(motor2,HIGH);
        digitalWrite(motor2_r,LOW);
        digitalWrite(motor3,HIGH);
        digitalWrite(motor3_r,LOW);
        digitalWrite(motor4,LOW);
        digitalWrite(motor4_r,LOW);
        //analogWrite(PWM_mot1, 255);
        analogWrite(PWM_mot2, 255);
        analogWrite(PWM_mot3, 255);
        //analogWrite(PWM_mot4, 255);
        delay(1000);
     
      }
      else if( -140 < pitch && pitch < -40 ){  //2 & 1
        digitalWrite(motor1,HIGH);
        digitalWrite(motor1_r,LOW);
        digitalWrite(motor2,HIGH);
        digitalWrite(motor2_r,LOW);
        digitalWrite(motor3,LOW);
        digitalWrite(motor3_r,LOW);
        digitalWrite(motor4,LOW);
        digitalWrite(motor4_r,LOW);
        analogWrite(PWM_mot1, 255);
        analogWrite(PWM_mot2, 255);
        //analogWrite(PWM_mot3, 255);
        //analogWrite(PWM_mot4, 255);
        delay(1000);
      }
    }
    else if( -140 < roll && roll < -40 ){
      if( 40 < pitch && pitch < 140 ){  //4 & 3
        digitalWrite(motor1,LOW);
        digitalWrite(motor1_r,LOW);
        digitalWrite(motor2,LOW);
        digitalWrite(motor2_r,LOW);
        digitalWrite(motor3,HIGH);
        digitalWrite(motor3_r,LOW);
        digitalWrite(motor4,HIGH);
        digitalWrite(motor4_r,LOW);
        //analogWrite(PWM_mot1, 255);
        //analogWrite(PWM_mot2, 255);
        analogWrite(PWM_mot3, 255);
        analogWrite(PWM_mot4, 255);
        delay(1000);
      }
      else if( -140 < pitch && pitch < -40 ){  //4 & 1
        digitalWrite(motor1,HIGH);
        digitalWrite(motor1_r,LOW);
        digitalWrite(motor2,LOW);
        digitalWrite(motor2_r,LOW);
        digitalWrite(motor3,LOW);
        digitalWrite(motor3_r,LOW);
        digitalWrite(motor4,HIGH);
        digitalWrite(motor4_r,LOW);
        analogWrite(PWM_mot1, 255);
        //analogWrite(PWM_mot2, 255);
        //analogWrite(PWM_mot3, 255);
        analogWrite(PWM_mot4, 255);
        delay(1000);
      }
    }
    else {
      byte var = Serial.read();
      var = var - 0x30;
    
      switch (var) {
        case 0: //only 2 for working
          digitalWrite(motor1,LOW);
          digitalWrite(motor1_r,LOW);
          digitalWrite(motor2,HIGH); //!
          digitalWrite(motor2_r,LOW);
          digitalWrite(motor3,LOW);
          digitalWrite(motor3_r,LOW);
          digitalWrite(motor4,LOW);
          digitalWrite(motor4_r,LOW);
          analogWrite(PWM_mot2, 255);
          delay(1000); 
          break;
          
        case 1: //1,2,3,4 for working
          digitalWrite(motor1,HIGH);
          digitalWrite(motor1_r,LOW);
          digitalWrite(motor2,HIGH);
          digitalWrite(motor2_r,LOW);
          digitalWrite(motor3,HIGH);
          digitalWrite(motor3_r,LOW);
          digitalWrite(motor4,HIGH);
          digitalWrite(motor4_r,LOW);
          analogWrite(PWM_mot1, 255);
          analogWrite(PWM_mot2, 255);
          analogWrite(PWM_mot3, 255);
          analogWrite(PWM_mot4, 255);
          delay(1000);
          break;
          
        case 2: // only 1,2 for working
          digitalWrite(motor1,HIGH);
          digitalWrite(motor1_r,LOW);
          digitalWrite(motor2,HIGH);
          digitalWrite(motor2_r,LOW);
          digitalWrite(motor3,LOW);
          digitalWrite(motor3_r,LOW);
          digitalWrite(motor4,LOW);
          digitalWrite(motor4_r,LOW);
          analogWrite(PWM_mot1, 255);
          analogWrite(PWM_mot2, 255);
          delay(1000);
          break;
          
    //    case 3: //1,3,4 reverse 
    //      digitalWrite(motor1_r,HIGH);
    //      digitalWrite(motor1,LOW);
    //      digitalWrite(motor2,LOW);
    //      digitalWrite(motor2_r,LOW);
    //      digitalWrite(motor3_r,HIGH);
    //      digitalWrite(motor3,LOW);
    //      digitalWrite(motor4_r,HIGH);
    //      digitalWrite(motor4,LOW);
    //      analogWrite(PWM_mot1, 255);
    //      analogWrite(PWM_mot2, 255);
    //      analogWrite(PWM_mot3, 255);
    //      analogWrite(PWM_mot4, 255);
    //      delay(1000);
    //      break;
    
        case 4: //only 2 3 for working
          digitalWrite(motor1,LOW);
          digitalWrite(motor1_r,LOW);
          digitalWrite(motor2,HIGH); //!
          digitalWrite(motor2_r,LOW);
          digitalWrite(motor3,HIGH);
          digitalWrite(motor3_r,LOW);
          digitalWrite(motor4,LOW);
          digitalWrite(motor4_r,LOW);
          analogWrite(PWM_mot3, 255);
          analogWrite(PWM_mot2, 255);
          delay(1000); 
          break;

        }

      }
   }
}

// 2 3
// 1 4
// (Arduino)
