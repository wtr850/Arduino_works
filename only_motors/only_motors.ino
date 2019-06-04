// ジャイロ機能はなしバージョン
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
// 0と1は使用不可

void setup() {
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
  byte var = Serial.read();
  var = var - 0x30;

//  testing
//  digitalWrite(motor2, HIGH);
//  digitalWrite(motor2_r, LOW);
//  analogWrite(PWM_mot2, 100);
//  delay(500);
//  digitalWrite(motor2, LOW);
//  digitalWrite(motor2_r, LOW);
//  delay(500);
  
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
      
    case 3: //1,3,4 reverse 
      digitalWrite(motor1,HIGH);
      digitalWrite(motor1_r,LOW);
      digitalWrite(motor2,LOW);
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

// 2 3
// 1 4
// (Arduino)
