/*************************************************************************
 *  * Note:  Bluetooth pin
 *          Not all pins on the Mega and Mega 2560 support change interrupts, so only the following 
 *          can be used for RX: 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69   
 *          Not all pins on the Leonardo support change interrupts, so only the following can be
 *          used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 */
#include <SoftwareSerial.h>
#include <Wire.h>

int LED = 13;
SoftwareSerial I2CBT(15,14); //定義Arduino PIN10及PIN11分別為RX及TX腳位
//請注意Arduino的TX要接藍牙模組的RX, 反之亦然

void setup() {
  Serial.begin(9600);
  I2CBT.begin(38400);//bluetooth baud rate  
  pinMode(LED, OUTPUT);    
}

void loop() {
  byte cmmd[20];
  int insize;
  Serial.println("event start");
  while(1){
    
    //read message from bluetooth
    if ((insize=(I2CBT.available()))>0){
      Serial.print("input size = "); 
      Serial.println(insize);
      for (int i=0; i<insize; i++){
        Serial.print(cmmd[i]=char(I2CBT.read()));
        Serial.print("\n"); 
      }
    }
    //根據所收到訊號執行對應動作  
    switch (cmmd[0]) {
    case 97: //'a'     
      digitalWrite(LED,HIGH);
      break;  

    case 98://'b'
      digitalWrite(LED,LOW);
      break;
    } //Switch
  } //while
}
