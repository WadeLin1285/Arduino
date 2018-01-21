#define LOWCURRENT 495
#define HIGHCURRENT 525
 
const int currentPin   = 17; // Define current sensor pin number (A3)
int current;

void setup() {
  Serial.begin(9600);
  pinMode(currentPin, INPUT);  //Set current as input
}

void loop() {
  current = analogRead(currentPin);
  Serial.println(current);
  delay(100);
}
