#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568


#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial camera(9, 11);
Servo servoClaw;

const int trig = 2;
const int echo = 12;
float distance = 0;

const int AIN1 = 7;
const int AIN2 = 13;
const int PWMA = 5;
const int BIN1 = 8;
const int BIN2 = 4;
const int PWMB = 3;
int motorSpeed = 0;

int slideSwitch = 8;
int buzzer = 10;
bool princess_saved = false;
int phrase1[] = {NOTE_C6, NOTE_G5, NOTE_E5, NOTE_C6, NOTE_G5, NOTE_E5, NOTE_C6};
int timing1[] = {100, 100, 150, 100, 100, 150, 400};
int phrase2[] = {NOTE_CS6, NOTE_GS5, NOTE_F5, NOTE_CS6, NOTE_GS5, NOTE_F5, NOTE_CS6};
int phrase3[] = {NOTE_DS6, NOTE_AS5, NOTE_G5, NOTE_DS6, NOTE_AS5, NOTE_G5, NOTE_DS6};
int phrase4[] = {NOTE_F6, NOTE_F6, NOTE_F6, NOTE_G6};
int timing2[] = {150, 150, 150, 500};

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
  pinMode(buzzer, OUTPUT);
  pinMode(slideSwitch, INPUT_PULLUP);
  camera.begin(9600);
  servoClaw.attach(6);
  servoClaw.write(100);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(camera.available() > 0){
    char data[13] = {camera.read()};
//    for(int i = 0; i < 14; i++){
//      Serial.print(data[i]);
    
  if(data > 0){
    distance = getDistance();
    Serial.println(distance);
    if(princess_saved == false){
      if(distance > 5 && distance < 100){
        forward(400);
        delay(100);
      }
      else if(distance < 3 && distance > 0){
        reverse(400);
        delay(200);

      }
      else if(distance < 5 && distance > 3){
        halt(500);
        right(120);
        halt(500);
        forward(380);
        delay(880);
        servoClaw.write(150);
        delay(500);
        princess_saved = true;
        halt(500);
        forward(500);
        delay(3000);
        halt(100);
        playSong();
        right(2000);
        halt(500);
        delay(1000);
 
    }
   }
  }
  else{
    halt(500);
    
    
  }
  
  }
  else{
    halt(100);
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

void right(int delayTime){
  leftMotor(500);
  rightMotor(-500);
  delay(delayTime);
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

void playSong(){
          for(int i = 0; i < 7; i++){
          tone(buzzer, phrase1[i], timing1[i]);
          delay(200);
        }
        delay(300);
        for(int i = 0; i < 7; i++){
          tone(buzzer, phrase2[i], timing1[i]);
          delay(200);
        }
        delay(300);
        for(int i = 0; i < 7; i++){
          tone(buzzer, phrase3[i], timing1[i]);
          delay(200); 
        }
        delay(300);
        for (int i = 0; i < 4; i++){
          tone(buzzer, phrase4[i], timing2[i]);
          delay(200);
        }
        delay(1000);
}
