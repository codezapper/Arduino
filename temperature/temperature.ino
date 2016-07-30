#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>

#define DHT11_PIN 7

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
dht DHT;

char first_row[16];
char second_row[16];

void setup() {
  Serial.begin(115200);

  lcd.begin (16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home
  lcd.setBacklight(HIGH);     // Backlight on
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  char str_temp[6];
  char str_humidity[6];

  dtostrf(DHT.temperature, 4, 2, str_temp);
  dtostrf(DHT.humidity, 4, 2, str_humidity);

  memset(first_row, 0, 16);
  memset(second_row, 0, 16);
  sprintf(first_row,  "Temp.:    %s", str_temp);
  sprintf(second_row, "Humidity: %s", str_humidity);
  delay(1000);
  lcd.setCursor (0, 0);
  lcd.print(first_row);
  lcd.setCursor (0, 1);
  lcd.print(second_row);
}
