const int button_blue = 51;
const int button_red  = 53;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  pinMode(button_red ,INPUT);
  pinMode(button_blue,INPUT);
}

void loop() {
  if (digitalRead(button_red) == 1)  Serial.println("Red");
  if (digitalRead(button_blue) == 1) Serial.println("Blue");
}
