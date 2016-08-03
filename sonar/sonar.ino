#include <NewPing.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

#define FULL_TURN 2048

#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define TRIGGER_PIN  7
#define ECHO_PIN     6
#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters).
                        //Maximum sensor distance is rated at 400-500cm.

int DistanceIn;
int DistanceCm;
const int resetsensor = 12; //Pin to BC-547 in Common Emitter mode thru 1k ohm resistor in base
const int ledsensor= 13; //Light to clone the reset sensor

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

char first_row[16];
char second_row[16];

const int buttonPin = 2;

int motorInPin[4] = {8, 10, 9, 11};

int buttonState = 0;

int Xpos = 0;
int Ypos = 0;

int newX = FULL_TURN;
int refX = FULL_TURN;

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
  motor.setSpeed(30);

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
    int Xdir = Xpos < newX ? 1 : -1;
    motor.step(Xdir);
    Xpos += Xdir;
  }
}

int prev_angle = 0;

void loop()
{
  approachX(newX);
  int distance_cm = sonar.ping_cm();

  if ((distance_cm < 3) && (distance_cm > 0)) {  //If distance is getting too low
    digitalWrite (resetsensor, LOW); //reset transistor, this is, take out power of SR-04
    digitalWrite (ledsensor, LOW); //light down to indicate we are resetting
    delay (200);
    digitalWrite (resetsensor, HIGH); //power up SR-04 again
    digitalWrite (ledsensor, HIGH); //ligh up to indicate SR-04 is again powered up
  }

  if (Xpos != 0) {
    int angle = (Xpos/2048.0) * 360;
    if (abs(angle-prev_angle) >= 1) {
      char str_temp[6];
      char str_to_send[255];
  
      dtostrf(angle, 3, 0, str_temp);

      memset(str_to_send, 0, 255);
      sprintf(str_to_send, "%d;%d;%d;%s;%d", angle, prev_angle, Xpos, str_temp, distance_cm);
      Serial.println(str_to_send);
      Serial.flush();
      prev_angle = angle;
      memset(first_row, ' ', 16);
      memset(second_row, ' ', 16);
      sprintf(first_row,  "Angle: %s ", str_temp);
      sprintf(second_row, "Distance: %02d cm", distance_cm);
      lcd.setCursor (0, 0);
      lcd.print(first_row);
      lcd.setCursor (0, 1);
      lcd.print(second_row);
    }
  } else {
    refX = -refX;
    newX = refX;
  }
}

