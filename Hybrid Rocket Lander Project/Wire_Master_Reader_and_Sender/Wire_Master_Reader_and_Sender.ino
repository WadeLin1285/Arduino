/***************************************************************************************************
 * Title : Master Reader and Sender
 * Author: Wade Lin 林暐哲
 * Date  : 2017/12
 * Description : Using Wire library and I2C bus to send data and receive data. This progam is for 
 *             master device. 
 ***************************************************************************************************/

#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  Serial.println("Setup...");
}

byte x = 0;

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }
  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  
  delay(500);
}
\
