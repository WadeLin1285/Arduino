#include <Wire.h>

int address = 20;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
  Wire.begin();
  // LCD setting
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);  // clean all
  Wire.write(254);
  Wire.write(74);  // underline on
  Wire.write(254);
  Wire.write(83);  // blinking on
  Wire.endTransmission();
  // Starting
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.write("Starting");
  Wire.endTransmission();
  delay(5000);
}

void loop() {
  Wire.beginTransmission(address);
  // These next two bytes send the command to clear the display.
  Wire.write(254);
  Wire.write(88);
  Wire.write("Temperature:");
  Wire.endTransmission();
  delay(500);
}
