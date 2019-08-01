#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
byte smileyEye[8] = {
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000,
  B00000,
};
byte smileyEdge[8] = {
  B00000,
  B11111,
  B11111,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
};

byte smileySmile[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B11111,
  B11111,
};

byte smileyWink[8] = {
  B00000,
  B00000,
  B01110,
  B11111,
  B10001,
  B00000,
  B00000,
  B00000,
};

void setup() {
  lcd.createChar(0, smileyEye);
  lcd.createChar(1, smileySmile);
  lcd.createChar(2, smileyEdge);
  lcd.createChar(4, smileyWink);
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(5, 0);
  lcd.write(byte(0));
  lcd.setCursor(10, 0);
  lcd.write(byte(0));
  for(int i = 3; i < 13; i++){
    lcd.setCursor(i, 1);
    lcd.write(byte(1));
  }
  delay(3000);
  lcd.setCursor(5, 0);
  lcd.write(byte(4));
  lcd.setCursor(10, 0);
  lcd.write(byte(4));
  lcd.setCursor(3, 1);
  lcd.write(byte(2));
  lcd.setCursor(12, 1);
  lcd.write(byte(2));
  delay(800);
}
