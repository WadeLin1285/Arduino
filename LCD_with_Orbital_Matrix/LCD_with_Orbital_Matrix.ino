#include <Wire.h>

int address = 40;

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(address);
  // These next two bytes send the command to clear the display.
  Wire.write(254);
  Wire.write(88);
  Wire.endTransmission();
  delay(500);
}


