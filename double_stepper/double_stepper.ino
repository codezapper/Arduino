#include <Stepper.h>

const int buttonPin = 2;

int motorInPin[2][4] = {
  {8, 10, 9, 11},
  {3, 5, 4, 6}
};

int buttonState = 0;

int Xpos = 0;
int Ypos = 0;

int newX = 0;
int newY = 0;


Stepper motor(512, motorInPin[0][0], motorInPin[0][1], motorInPin[0][2], motorInPin[0][3]);
Stepper motor2(512, motorInPin[1][0], motorInPin[1][1], motorInPin[1][2], motorInPin[1][3]);

void motorOff(int index) {
  for (int y = 0; y < 4; y++) {
    digitalWrite(motorInPin[index][y],LOW);
  }
}

void setup()
{
  pinMode(buttonPin, INPUT);
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 4; y++) {
      pinMode(motorInPin[x][y], OUTPUT);
    }
  }
  pinMode(13,OUTPUT);  
  
  Serial.begin(9600);
  motor.setSpeed(30);
  motor2.setSpeed(30);
}

void approachX(int &newX){
  if (Xpos == newX) {
    Xpos = 0;
    newX = 0;
    motorOff(0);
    // Serial.print("Finished X\n");
  } else {
    int Xdir = Xpos<newX ? 1 : -1;
    motor.step(Xdir);        // move one step in the Ydir direction.
    Xpos += Xdir;               // update Ypos.
  }
}

void approachY(int &newY){
  if (Ypos == newY) {
    Ypos = 0;
    newY = 0;
    motorOff(1);
    // Serial.print("Finished Y\n");
  } else {
    char s[255] = "";
    sprintf(s, "%d - %d\n", Ypos, newY);
    Serial.print(s);
    int Ydir = 1; // Ypos<newY ? 1 : -1;
    motor2.step(Ydir);        // move one step in the Ydir direction.
    Ypos += Ydir;               // update Ypos.
  }
}

void loop()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
    Serial.print("Button HIGH\n");
    newX = 100;
    newY = 100;
  }
  approachX(newX);
  approachY(newY);
}

