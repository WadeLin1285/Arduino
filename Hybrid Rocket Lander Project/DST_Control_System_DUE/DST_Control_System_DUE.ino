/***************************************************************************************************
 * Title : DST (MTY test 1) Control System for DUE
 * Author: Wade Lin 林暐哲
 * Date  : 2017/12
 * Description : The devices are following: (includeing MEGA and DUE)
 *              1. Altimeter : VL53L0X (DUE)
 *              2. SD Card (MEGA)
 *              3. Relay (DUE)
 *              4. Buzzer  (MEGA)
 *              5. Bluetooth : ZS-040 (MEGA)
 *              6. 9-DOF Sensor : GY-6500(GY-9250) (MEGA)
 * Note:  
 ***************************************************************************************************/
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X altimeter;
extern TwoWire Wire1;
long H, oldH, V;
static unsigned long t, oldt;

/************** FUNCTIONS ******************/
void calculateVelocity();
void thruster(signed long H, signed long V, unsigned long t);

/**************   SETUP   ******************/
void setup() {
  Serial.begin(19200);  // start serial for output
  Serial.println("Setup...");

  Wire.begin();
  altimeter.init();
  altimeter.setTimeout(500);
  altimeter.startContinuous();
  
  Wire1.begin(8);              // join i2c bus with address #8
  Wire1.onRequest(requestEvent); // register event
  Wire1.onReceive(receiveEvent); // register event
}

/************** MAIN PROGRAM ******************/
void loop() {
  // System Altitude Measurement
  t = millis();
  H = altimeter.readRangeContinuousMillimeters();    // unit: mm
  calculateVelocity();                                   
  
  // Thruster Control
  //thruster(H,V,millis());

  // Serial Print
  Serial.print(H);
  Serial.print("\t");
  Serial.print(V);
  Serial.print("\t");
  Serial.print(t - oldt);

  Serial.println();

  // End condition
  oldt = t;
  oldH = H; 
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire1.write(millis());        // sends time (unsigned long)
  Wire1.write(H);              // sends altitude (signed long)
  Wire1.write(V);              // sends altitude (signed long)
}

void receiveEvent(int howMany) {
  while (Wire1.available()) { // loop through all but the last
    int c = Wire1.read(); // receive byte as an integer
    Serial.println(c);         // print the character
  }
}

void calculateVelocity(){
  const int N = 5;
  static long dV[N] = {0,0,0,0,0};
  long long int sumV = 0;
  for (int i = N-1; i >= 0; i--) dV[i] = dV[i-1];
  dV[0] = (H - oldH)*1000 / (t - oldt);        
  for (int i = 0; i < N; i++) sumV += dV[i];
  V = (long)(sumV/N);
}

void thruster(signed long H, signed long V, unsigned long t){
  
}

