/*
  Showing number 0-9 on a Common Anode 7-segment LED display
  Displays the numbers 0-9 on the display, with one second inbetween.
    A
   ---
F |   | B
  | G |
   ---
E |   | C
  |   |
   ---
    D
  This example code is in the public domain.
 */
 
// Pin 2-8 is connected to the 7 segments of the display.

#include "pitches.h"
#include "digits.h"

#define outputA 15
#define outputB 16

#define BUTTON_PIN 17
#define SPEAKER_PIN 18

#define NOTE_TIME 100

int current_time;
int prev_time;
int button_prev_time;
int timer = 0;
int counter = 0;
int rotary_state;
int rotary_last_state;
int button_state = true;
int button_last_state = true;
int timer_started = false;
int notes[] = {NOTE_C4, NOTE_C4, NOTE_B5};
int current_note = -1;
int max_rings = 10;
int current_rings = 0;
int note_interval;

void setup() {
  Serial.begin(9600);
  setup_digits();
  current_time = millis();
  prev_time = millis();
  button_prev_time = millis();
  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(SPEAKER_PIN,OUTPUT);
  rotary_last_state = digitalRead(outputA);
  button_last_state = digitalRead(BUTTON_PIN);

  note_interval = NOTE_TIME;
}

// the loop routine runs over and over again forever:
void loop() {
  current_time = millis();

  // Rotary code
  if (current_note == -1) {
    rotary_state = digitalRead(outputA);
    if (rotary_state != rotary_last_state) {
      if ((current_time - prev_time) >= 100) {
        prev_time = current_time;
        if (digitalRead(outputB) != rotary_state) {
          timer++;
        } else {
          timer--;
        }
      }
      rotary_last_state = rotary_state;
    }
  }
  display_number(timer);

  // Display code

  if (timer_started) {
    if ((timer >= 0) && ((current_time - prev_time) >= 1000)) {
      if (timer == 0) {
        current_note = 0;
        timer_started = 0;
      } else {
        prev_time = current_time;
      }
      timer--;
    }
    display_number(timer);
  }

  // Button code
  button_state = digitalRead(BUTTON_PIN);
  if (button_state == LOW && button_last_state == HIGH && millis() - button_prev_time > 500) {
    if (timer > 0) {
      timer_started = !timer_started;
    }
    if (current_note >= 0) {
      current_note = -1;
      current_rings = 0;
    }
    button_prev_time = millis();
  }
  button_last_state = button_state;

  // Speaker code
  if (current_note >= 0) {
    Serial.println("00");
    if ((current_time - prev_time) >= note_interval) {
    Serial.println("01");
      if (current_rings >= max_rings) {
    Serial.println("02");
        current_note = -1;
        current_rings = 0;
        noTone(SPEAKER_PIN);
      } else {
    Serial.println("03");
        tone(SPEAKER_PIN, notes[current_note], NOTE_TIME);
        current_note++;
        if (current_note >= 3) {
          current_rings++;
    Serial.println("04");
          note_interval = 1000;
          current_note = 0;
        } else {
    Serial.println("05");
          note_interval = NOTE_TIME;
        }
        prev_time = current_time;
      }
    }
  }
}
