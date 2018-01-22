/***************************************************************************************************
   Title : DST (MTY test 1) Control System for MEGA
   Author: Wade Lin ���
   Date  : 2017/12
   Description : The devices are following: (includeing MEGA and DUE)
                1. Altimeter : VL53L0X (DUE)
                2. SD Card (MEGA)
                3. Relay (DUE)
                4. Buzzer  (MEGA)
                5. Bluetooth : ZS-040 (MEGA)
                6. 9-DOF Sensor : GY-6500(GY-9250) (MEGA)
   Note:  1. Bluetooth pin
            Not all pins on the Mega and Mega 2560 support change interrupts, so only the following
            can be used for RX: 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
            Not all pins on the Leonardo support change interrupts, so only the following can be
            used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
         2. Definition of Signals from Bluetooth
            Mission Start - 'O'
            Mission Stop(forced stop) - 'X'
            DST System On  - 'D' + 'o'
            DST System Off - 'D' + 'f'
            ACS System On  - 'A' + 'o'
            ACS System Off - 'A' + 'f'
 ***************************************************************************************************/

#include <Wire.h>

void setup() {
  Serial.begin(9600);  // start serial for output
  Serial.println("Setup...");
  
  Wire.begin();        // join i2c bus (address optional for master)

}

byte x = 0;

void loop() {
  Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    int c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }
  /*
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
*/
  x++;
  delay(100);
}
