#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

char first_row[16];
char second_row[16];

const int buttonPin = 2;

int motorInPin[4] = {8, 10, 9, 11};

int buttonState = 0;

int Xpos = 0;
int Ypos = 0;

int newX = 2048;

Stepper motor(512, motorInPin[0], motorInPin[1], motorInPin[2], motorInPin[3]);

void motorOff() {
  for (int index = 0; index < 4; index++) {
    digitalWrite(motorInPin[index],LOW);
  }
}

void setup()
{
  pinMode(buttonPin, INPUT);
  for (int index = 0; index < 4; index++) {
    pinMode(motorInPin[index], OUTPUT);
  }
  pinMode(13,OUTPUT);  
  
  Serial.begin(115200);
  motor.setSpeed(10);

  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.setBacklight(HIGH);
}

void approachX(int &newX){
  if (Xpos == newX) {
    Xpos = 0;
    newX = 0;
    motorOff();
  } else {
    int Xdir = Xpos<newX ? 1 : -1;
    motor.step(Xdir);
    Xpos += Xdir;
  }
}

double prev_angle = 0;

void loop()
{
  approachX(newX);

  double angle = (Xpos/2048.0) * 360;
  char str_temp[6];

  dtostrf(angle, 4, 2, str_temp);
  Serial.print(angle);
  Serial.print(";");
  Serial.print(prev_angle);
  Serial.print(";");
  Serial.print(Xpos);
  Serial.print(";");
  Serial.println(str_temp);

  if (abs(angle-prev_angle) >= 10) {
    prev_angle = angle;
    memset(first_row, 0, 16);
    memset(second_row, 0, 16);
    sprintf(first_row,  "Angle: %s", str_temp);
    lcd.setCursor (0, 0);
    lcd.print(first_row);
    lcd.setCursor (0, 1);
    lcd.print(second_row);
  }
}

