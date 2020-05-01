int pinA = 2;
int pinB = 3;
int pinC = 4;
int pinD = 5;
int pinE = 6;
int pinF = 7;
int pinG = 8;
int D1 = 9;
int D2 = 10;
int D3 = 11;
int D4 = 12;

void setup_digits() {                
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);  
}

void one() {
  digitalWrite(pinA, HIGH);   
  digitalWrite(pinB, LOW);   
  digitalWrite(pinC, LOW);   
  digitalWrite(pinD, HIGH);   
  digitalWrite(pinE, HIGH);   
  digitalWrite(pinF, HIGH);   
  digitalWrite(pinG, HIGH);   
  delay(1);
}

void two() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, HIGH); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, LOW); // E   
  digitalWrite(pinF, HIGH); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void three() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, HIGH); // E   
  digitalWrite(pinF, HIGH); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void four() {
  digitalWrite(pinA, HIGH); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, HIGH); // D
  digitalWrite(pinE, HIGH); // E   
  digitalWrite(pinF, LOW); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void five() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, HIGH); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, HIGH); // E   
  digitalWrite(pinF, LOW); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void six() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, HIGH); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, LOW); // E   
  digitalWrite(pinF, LOW); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void seven() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, HIGH); // D
  digitalWrite(pinE, HIGH); // E   
  digitalWrite(pinF, HIGH); // F
  digitalWrite(pinG, HIGH); // G
  delay(1);
}

void eight() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, LOW); // E   
  digitalWrite(pinF, LOW); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void nine() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, HIGH); // E   
  digitalWrite(pinF, LOW); // F
  digitalWrite(pinG, LOW); // G
  delay(1);
}

void zero() {
  digitalWrite(pinA, LOW); // A
  digitalWrite(pinB, LOW); // B  
  digitalWrite(pinC, LOW); // C
  digitalWrite(pinD, LOW); // D
  digitalWrite(pinE, LOW); // E   
  digitalWrite(pinF, LOW); // F
  digitalWrite(pinG, HIGH); // G
  delay(1);
}

void display_digit(int digit, int pos) {
  digitalWrite(D1, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D3, LOW);
  digitalWrite(D4, LOW);
  digitalWrite(D1 + pos, HIGH);

  switch (digit) {
    case 0:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
  
}

void display_number(int number) {
  if ((number < 0) or (number > 9999)) {
    return;
  }
  if (number == 0) {
    display_digit(0, 3);
    return;
  }
  int pos = 3;
  while (number > 0) {
    int res = number % 10;
    display_digit(res, pos);
    number = number / 10;
    pos--;
  }
}
