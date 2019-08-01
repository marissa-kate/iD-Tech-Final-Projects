const int trig = 11;
const int echo = 12;
float distance = 0;

const int AIN1 = 7;
const int AIN2 = 6;
const int PWMA = 5;
const int BIN1 = 2;
const int BIN2 = 4;
const int PWMB = 3;
int motorSpeed = 0;

int slideSwitch = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(slideSwitch, INPUT_PULLUP);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int switchOn = digitalRead(slideSwitch);
  distance = getDistance();
  Serial.println(distance);
  if(switchOn == LOW){
    if(distance < 4){
      halt(500); 
      reverse(100); 
      halt(100);
      right();
      distance = getDistance();
      if(distance < 6){
        halt(500);
        left();
        forward(200);
        delay(100);
        left();
        halt(100);
        distance = getDistance();
        reverse(200);
      }
      }
    else{
      forward(100);
}
  }
  else{
    halt(1000);
  }
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

void forward(int Speed){
  leftMotor(Speed);
  rightMotor(Speed+2);
}

void reverse(int Speed){
  Speed = -Speed;
  leftMotor(Speed);
  rightMotor(Speed);
  delay(200);
}

void right(){
  leftMotor(100);
  rightMotor(-100);
  delay(700);
}

void left(){
  leftMotor(-100);
  rightMotor(100);
  delay(720);
  }

void halt(int delayTime){
  leftMotor(0);
  rightMotor(0);
  delay(delayTime);
}
