/***************************************************************************************************
 * Title : DST (MTY test 1) Control System Test
 * Author: Wade Lin 林暐哲
 * Date  : 2017/11 
 * Description : Test the devices used in the DST control system. The devices are following:
 *              1. Altimeter : VL53L0X
 *              2. LCD Monitor
 *              3. SD Card 
 *              4. Four-way Relay
 *              5. Buzzer  
 *              6. Bluetooth : ZS-040
 *              7. 9-DOF Sensor : GY-6500(GY-9250)
 * Note:  1. Bluetooth pin
 *          Not all pins on the Mega and Mega 2560 support change interrupts, so only the following 
 *          can be used for RX: 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69   
 *          Not all pins on the Leonardo support change interrupts, so only the following can be
 *          used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 *       2. Definition of Signals from Bluetooth 
 *          Mission Start - 'O'
 *          Mission Stop(forced stop) - 'X'
 *          DST System On  - 'D' + 'o'
 *          DST System Off - 'D' + 'f'
 *          ACS System On  - 'A' + 'o'
 *          ACS System Off - 'A' + 'f'
 ***************************************************************************************************/
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <VL53L0X.h>
#include <SoftwareSerial.h>
#include <SdFat.h>             // #include <SD.h>

SdFat SD;
VL53L0X altimeter;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);      // Setting LCD address
SoftwareSerial I2CBT(10,18);     // Define Bluetooth pins on arduino(RX,TX)

// Relay signal pins
const int RELAY_1_PIN = 36;     // Relay INT 1 pin
const int RELAY_2_PIN = 38;     // Relay INT 2 pin
const int RELAY_3_PIN = 40;     // Relay INT 3 pin
const int RELAY_4_PIN = 42;     // Relay INT 4 pin

// SD card pins
const int SD_MISO_PIN = 50;     // SD card MISO pin
const int SD_MOSI_PIN = 51;     // SD card MOSI pin
const int SD_SCK_PIN  = 52;     // SD card SCK pin
const int SD_CS_PIN   = 53;     // SD card CS(SS) pin

// Set the pins for other devices
const int BUTTOM_PIN = 34;
const int BUZZER_PIN = 44;

// Set some functions and global variables
int missionState = 0;
byte command[20];
int insize;
void alert();
void systemStop();

void setup() {
  Serial.begin(9600);
  I2CBT.begin(9600);      //bluetooth baud rate  
  Wire.begin();
  
  // Device setups
  lcd.begin(16, 2);
  lcd.blink();
  Serial.println("LCD Start..");
  lcd.print("LCD Start..");
  delay(500);
  altimeter.init();
  altimeter.setTimeout(500);
  altimeter.startContinuous();
  lcd.clear();
  Serial.println("Altimeter Start..");
  lcd.print("Altimeter Start..");
  delay(500);
  lcd.clear();
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD Card Fail!");
    lcd.print("SD Card Fail!");
    return;
  }
  else {
    Serial.println("SD Card Success!");
    lcd.print("SD Card Success!");
  }
  delay(500);
  lcd.clear();
  if (I2CBT.available() > 0) {
    Serial.println("BT Fail!");
    lcd.print("BT Fail!");
  }
  else {
    Serial.println("BT Success!");
    lcd.print("BT Success!");
  }
  
  // Pin Definitions
  pinMode(RELAY_1_PIN,OUTPUT);
  pinMode(RELAY_2_PIN,OUTPUT);
  pinMode(RELAY_3_PIN,OUTPUT);
  pinMode(RELAY_4_PIN,OUTPUT);
  pinMode(BUTTOM_PIN, INPUT );
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(RELAY_1_PIN,HIGH);     // turn off relay
  digitalWrite(RELAY_2_PIN,HIGH);
  digitalWrite(RELAY_3_PIN,HIGH);
  digitalWrite(RELAY_4_PIN,HIGH);

  Serial.println("System Start-up Success!");
  lcd.clear();
  lcd.print("System Start-up");
  lcd.setCursor(0,1);
  lcd.print("Success!");
}

void loop() {
  Serial.print(millis());
  Serial.print(" ");
  
  // Some Special Situations
  if (missionState < 0) {               // Mission forced stop
    while(1) {
      digitalWrite(BUZZER_PIN,HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(300);
    }
  }
  if (digitalRead(BUTTOM_PIN)) alert();   // Alerting

  // Bluetooth Signal Processing
  if ((insize = (I2CBT.available()))>0) {
    for (int i=0; i < insize; i++) command[i]=char(I2CBT.read());
    // Definition of signals are noted at code description
    switch (command[0]) {
      case 79:      // 'O' - Start
        Serial.println("Mission Start!");
        lcd.clear();
        lcd.print("Mission Start!");
        missionState = 1;
        break;
      case 88:      // 'X' - Stop
        Serial.println("Mission Stop!");
        lcd.clear();
        lcd.print("Mission Stop!");
        systemStop();
        break;
      case 68:      // 'D' - DST system
        if (command[1] == 111) {     // 'o' - DST System on
          Serial.println("DST System On!");
          lcd.clear();
          lcd.print("DST System On!");
          digitalWrite(RELAY_1_PIN,LOW);
        }
        else if (command[1] == 102) { // 'f' - DST System off
          Serial.println("DST System Off!");
          lcd.clear();
          lcd.print("DST System Off!");
          digitalWrite(RELAY_1_PIN,HIGH);
        }
        break;
      case 65:      // 'A' - ACS system
       if (command[1] == 111) {      // 'o' - ACS System on
          Serial.println("ACS System On!");
          lcd.clear();
          lcd.print("ACS System On!");
          digitalWrite(RELAY_2_PIN,LOW);
        }
        else if (command[1] == 102) { // 'f' - ACS System off
          Serial.println("ACS System Off!");
          lcd.clear();
          lcd.print("ACS System Off!");
          digitalWrite(RELAY_2_PIN,HIGH);
        }
        break;
    } // switch
  } // if

  // System Height Measurement
  uint16_t height = altimeter.readRangeContinuousMillimeters();     // unit: mm
  Serial.print(height);
  if (altimeter.timeoutOccurred()) { 
    Serial.print("Timeout!");
    lcd.clear();
    lcd.print("Altimeter Timeout!");
    systemStop();
  }
  
  Serial.println();
}

void alert() {
  for (int i = 0 ; i < 3 ; i++) {
    digitalWrite(BUZZER_PIN,HIGH);
    delay(50);
    digitalWrite(BUZZER_PIN, LOW);
    delay(50);
  }
}

void systemStop() {
  digitalWrite(RELAY_1_PIN,HIGH);     // turn off relay
  digitalWrite(RELAY_2_PIN,HIGH);
  digitalWrite(RELAY_3_PIN,HIGH);
  digitalWrite(RELAY_4_PIN,HIGH);
  missionState = -1;
  lcd.setCursor(0,1);
  lcd.print("System Disabled...");
}

