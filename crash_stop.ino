const int trig = 11;
const int echo = 12;
int slideSwitch = 8;
float distance = 0;

const int AIN1 = 7;
const int AIN2 = 6;
const int PWMA = 5;

const int BIN1 = 2;
const int BIN2 = 3;
const int PWMB = 4;

int motorSpeed = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(slideSwitch, INPUT_PULLUP);
  
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int switchOn = digitalRead(slideSwitch);
  distance = getDistance();
  Serial.println(distance);
  if(switchOn == LOW){
    if(distance < 15){
      rightMotor(0);
      leftMotor(0);
      delay(500);
      rightMotor(-150);
      leftMotor(-150);
      delay(300);
      rightMotor(-150);
      leftMotor(150);
      delay(200);
      rightMotor(0);
      leftMotor(0);
      delay(500);
    }
    else{
      leftMotor(128);
      rightMotor(150);
    }
  }
  else{
    rightMotor(0);
    leftMotor(0);
  }
  delay(50);
}
float getDistance(){
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  float echoTime = pulseIn(echo, HIGH);
  float calculateDistance = echoTime/148.0;
  return calculateDistance;
}

void leftMotor(int motorSpeed){
  if(motorSpeed > 0){
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else if(motorSpeed < 0){
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, HIGH);
  }
  else{
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
  }
  analogWrite(PWMB, abs(motorSpeed));
}

void rightMotor(int motorSpeed){
  if(motorSpeed > 0){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else if(motorSpeed < 0){
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, HIGH);
  }
  else{
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
  }
  analogWrite(PWMA, abs(motorSpeed));
}
