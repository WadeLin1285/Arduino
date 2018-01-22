const int pin_1  = 29;
const int pin_2  = 31;
const int pin_3  = 33;
const int pin_4  = 35;
const int pin_5  = 37;
const int pin_6  = 39;
const int pin_7  = 41;
const int pin_8  = 43;
const int pin_9  = 45;
const int pin_10 = 47;

void setup() {
  pinMode(pin_1,OUTPUT);
  pinMode(pin_2,OUTPUT);
  pinMode(pin_3,OUTPUT);
  pinMode(pin_4,OUTPUT);
  pinMode(pin_5,OUTPUT);
  pinMode(pin_6,OUTPUT);
  pinMode(pin_7,OUTPUT);
  pinMode(pin_8,OUTPUT);
  pinMode(pin_9,OUTPUT);
  pinMode(pin_10,OUTPUT);
}

void loop() {
  digitalWrite(pin_1,HIGH);
  delay(300);
  digitalWrite(pin_2,HIGH);
  delay(300);
  digitalWrite(pin_3,HIGH);
  delay(300);
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_4,HIGH);
  delay(300);
  digitalWrite(pin_2,LOW);
  digitalWrite(pin_5,HIGH);
  delay(300);
  digitalWrite(pin_3,LOW);
  digitalWrite(pin_6,HIGH);
  delay(300);
  digitalWrite(pin_4,LOW);
  digitalWrite(pin_7,HIGH);
  delay(300);
  digitalWrite(pin_5,LOW);
  digitalWrite(pin_8,HIGH);
  delay(300);
  digitalWrite(pin_6,LOW);
  digitalWrite(pin_9,HIGH);
  delay(300);
  digitalWrite(pin_7,LOW);
  digitalWrite(pin_10,HIGH);
  delay(300);
  digitalWrite(pin_8,LOW);
  delay(300);
  digitalWrite(pin_9,LOW);
  delay(300);
  digitalWrite(pin_10,LOW);
  delay(300);
}
