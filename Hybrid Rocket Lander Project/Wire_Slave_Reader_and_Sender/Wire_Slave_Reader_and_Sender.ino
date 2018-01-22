/***************************************************************************************************
 * Title : Slave Reader and Sender
 * Author: Wade Lin 林暐哲
 * Date  : 2017/12
 * Description : Using Wire library and I2C bus to send data and receive data. This progam is for 
 *             slave device. 
 ***************************************************************************************************/

#include <Wire.h>
extern TwoWire Wire1;

int x;

void setup() {
  Wire1.begin(8);                // join i2c bus with address #8
  Serial.begin(9600);  // start serial for output
  Serial.println("Setup...");
  Wire1.onRequest(requestEvent); // register event
  Wire1.onReceive(receiveEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire1.write(x);              // sends one byte
  x++;
}

void receiveEvent(int howMany) {
  while (Wire1.available()) { // loop through all but the last
    int c = Wire1.read(); // receive byte as a character
    Serial.println(c);         // print the character
  }
}

\
