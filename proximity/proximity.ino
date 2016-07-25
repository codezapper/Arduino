#include <NewPing.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

/*-----( Declare Constants and Pin Numbers )-----*/
#define  TRIGGER_PIN  7
#define  ECHO_PIN     8
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters).
                         //Maximum sensor distance is rated at 400-500cm.
/*-----( Declare objects )-----*/
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
/*-----( Declare Variables )-----*/
int DistanceIn;
int DistanceCm;
const int resetsensor = 12; //Pin to BC-547 in Common Emitter mode thru 1k ohm resistor in base
const int ledsensor= 13; //Light to clone the reset sensor
char first_row[16];
char second_row[16];

int n = 1;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()   /****** SETUP: RUNS ONCE ******/
{
  Serial.begin(9600);
//  Serial.println("Resetting the dammed SR-04 UltraSonic Distance Meter");
//  Serial.println("questions to vidalgm@gmail.com");
  pinMode (resetsensor, OUTPUT);
  pinMode (ledsensor, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home
  lcd.setBacklight(HIGH);     // Backlight on
}


void loop()   /****** LOOP: RUNS CONSTANTLY ******/
{
  digitalWrite (resetsensor,HIGH); //Gives power to the dammned SR-04 thru the BC-547
  delay(100);// Wait 100ms between pings (about 10 pings/sec). 29ms should be the shortest delay between pings.
  DistanceIn = sonar.ping_in();
//  Serial.print("Ping: ");
//  Serial.print(DistanceIn); // Convert ping time to distance and print result
//                            // (0 = outside set distance range, no ping echo)
//  Serial.print(" in     ");
 
  delay(100);// Wait 100ms between pings (about 10 pings/sec). 29ms should be the shortest delay between pings.
  DistanceCm = sonar.ping_cm();
//  Serial.print("Ping: ");
//  Serial.print(DistanceCm);
//  Serial.println(" cm");
  if (DistanceCm < 1) {  //If distance is getting too low
    digitalWrite (resetsensor, LOW); //reset transistor, this is, take out power of SR-04
    digitalWrite (ledsensor, LOW); //light down to indicate we are resetting
    delay (200);
    digitalWrite (resetsensor, HIGH); //power up SR-04 again
    digitalWrite (ledsensor, HIGH); //ligh up to indicate SR-04 is again powered up
  } else {
    memset(first_row, 0, 16);
    memset(second_row, 0, 16);
    sprintf(first_row,  "Distance: %02d cm", DistanceCm);
    sprintf(second_row, "          %02d in", DistanceIn);
    lcd.setCursor (0, 0);
    lcd.print(first_row);
    lcd.setCursor (0, 1);
    lcd.print(second_row);
    if ((DistanceCm > 0) && (DistanceCm < 20)) {
      digitalWrite (2,HIGH);
      digitalWrite (3,LOW);
    } else {
      digitalWrite (2,LOW);
      digitalWrite (3,HIGH);
    }
  }
}

