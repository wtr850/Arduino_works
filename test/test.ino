const int motor1 = 12; // normal
const int motor2 = 10;
const int motor3 = 8;
const int motor4 = 6;
const int motor1_r = 4;  // r...reverse
const int motor2_r = 3;
const int motor3_r = 2;
const int motor4_r = 1;
const int PWM_mot1 = 13; // analog write
const int PWM_mot2 = 11;
const int PWM_mot3 = 9;
const int PWM_mot4 = 7;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT); // for testing
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor1_r, OUTPUT);
  pinMode(motor2_r, OUTPUT);
  pinMode(motor3_r, OUTPUT);
  pinMode(motor4_r, OUTPUT);

}

void loop() {
  //  testing
  digitalWrite(motor2, HIGH);
  digitalWrite(motor2_r, LOW);
  analogWrite(PWM_mot2, 100);
  delay(500);
  digitalWrite(motor2, LOW);
  digitalWrite(motor2_r, LOW);
  delay(500);
}
