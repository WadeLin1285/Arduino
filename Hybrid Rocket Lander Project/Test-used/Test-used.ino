const int LEG_PIN = 25;
const int Relay_PIN = 8;
const int BUZZER_PIN = 27;


void setup() {
  pinMode(LEG_PIN,INPUT);
  pinMode(Relay_PIN,OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);
}

void loop() {
  digitalWrite(Relay_PIN,HIGH);
  delay(500);
  digitalWrite(Relay_PIN,LOW);
  delay(500);
}
