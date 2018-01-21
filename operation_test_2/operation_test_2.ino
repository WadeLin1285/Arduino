/******************* Noodle Machine ******************
 * Author : Wade Lin 
 * Update : 2017/5/24
 * Description :
 *   This program is use for noodle making machine. 
 *   There are two modes which selected by two buttons.
 *   After "Start" button is clicked, the mision 
 *   starts and the full operation is directly written 
 *   in the code. 
 *   NOTE: There is no stop function during the operation.
 * Devices :
 *   1 * Arduino MEGA board
 *   1 * RAMPS 1.4 board
 *   4 * DRV 8825 (motor driver)
 *   4 * stepper motor
 *   3 * electrical valve
 *   3 * button
 */
/************** Define the pin number ***************/
/* stepper motor #0
#define SM_0_STEP_PIN      26
#define SM_0_DIR_PIN       28
#define SM_0_ENABLE_PIN    24
*/

// stepper motor #1
#define SM_1_STEP_PIN      36
#define SM_1_DIR_PIN       34
#define SM_1_ENABLE_PIN    30

// stepper motor #2
#define SM_2_STEP_PIN      54
#define SM_2_DIR_PIN       55
#define SM_2_ENABLE_PIN    38

// stepper motor #3
#define SM_3_STEP_PIN      60
#define SM_3_DIR_PIN       61
#define SM_3_ENABLE_PIN    56

// stepper motor #4
#define SM_4_STEP_PIN      46
#define SM_4_DIR_PIN       48
#define SM_4_ENABLE_PIN    62

// electrical valve
#define EV_1_PIN           10
#define EV_2_PIN            9
#define EV_3_PIN            8

// others
#define LED_PIN            13
#define Button_A_PIN       2
#define Button_B_PIN       14
#define Button_START_PIN   3

unsigned int mode = 0;                                 // store the mode that user choose (1:mode A / 2:mode B)
const int speed_1 = 2000;                              // set the speed of each motor (Unit: microsecond) 
const int speed_2 = 2000;
const int speed_3 = 2000;
const int speed_4 = 2000;
const int cycle = 200;                                 // set the number of step for one cycle

void setup() {
  Serial.begin(9600);
  Serial.println("Machine Start Setup......");
  // set pin modes
  // SM#1
  pinMode(SM_1_STEP_PIN   , OUTPUT);
  pinMode(SM_1_DIR_PIN    , OUTPUT);
  pinMode(SM_1_ENABLE_PIN , OUTPUT);
  // SM#2
  pinMode(SM_2_STEP_PIN   , OUTPUT);
  pinMode(SM_2_DIR_PIN    , OUTPUT);
  pinMode(SM_2_ENABLE_PIN , OUTPUT);
  // SM#3
  pinMode(SM_3_STEP_PIN   , OUTPUT);
  pinMode(SM_3_DIR_PIN    , OUTPUT);
  pinMode(SM_3_ENABLE_PIN , OUTPUT);
  // SM#4
  pinMode(SM_4_STEP_PIN   , OUTPUT);
  pinMode(SM_4_DIR_PIN    , OUTPUT);
  pinMode(SM_4_ENABLE_PIN , OUTPUT);
  // EVs and others
  pinMode(EV_1_PIN        , OUTPUT);
  pinMode(EV_2_PIN        , OUTPUT);
  pinMode(EV_3_PIN        , OUTPUT);
  pinMode(LED_PIN         , OUTPUT);
  pinMode(Button_A_PIN    , INPUT);
  pinMode(Button_B_PIN    , INPUT);
  pinMode(Button_START_PIN, INPUT);
  
  // enable the output signal to stepper motor
  digitalWrite(SM_1_ENABLE_PIN,LOW);
  digitalWrite(SM_2_ENABLE_PIN,LOW);
  digitalWrite(SM_3_ENABLE_PIN,LOW);
  digitalWrite(SM_4_ENABLE_PIN,LOW);

  // set the stepper motor direction
  digitalWrite(SM_1_DIR_PIN,LOW);
  digitalWrite(SM_2_DIR_PIN,LOW);
  digitalWrite(SM_3_DIR_PIN,LOW);
  digitalWrite(SM_4_DIR_PIN,LOW);
  
  // turn the electical valve off
  digitalWrite(EV_1_PIN,LOW);
  digitalWrite(EV_2_PIN,LOW);
  digitalWrite(EV_3_PIN,LOW);

  // LED blink
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN,HIGH);
    delay(500);
    digitalWrite(LED_PIN,LOW);
    delay(500);
  }
  digitalWrite(LED_PIN,HIGH);                             // LED turn on represents machine operating
  Serial.println("Setup Success !");
}
void loop() {
  // confirm the mode choosed
  if (digitalRead(Button_A_PIN) == 1) {
    mode = 1;
    Serial.println("Operation mode changes to 'A'.");
  }
  if (digitalRead(Button_B_PIN) == 1) {
    mode = 2;
    Serial.println("Operation mode changes to 'B'.");   
  }
/************************* Main Mission Start ********************************/
  if (digitalRead(Button_START_PIN) == 1) {
    Serial.println("Machine Start ! ! ......");
    /*************************** MODE A *******************************/
    if (mode == 1) {                                      
      Serial.println("Starting mode A......");
      Serial.println("Testing SM#2 operation ......");

      /* 6. SM#2 five cycles */
      Serial.println("Mode A --- Step 6 : SM#2 five cycles");
      for (int i = 0; i < 5*cycle; i++) {                 // five cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      delay(3000);
      /* 8. SM#2 4.5 cycle */
      Serial.println("Mode A --- Step 8 : SM#2 4.5 cycles");
      for (int i = 0; i < 4.5*cycle; i++) {               // 4.5 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      delay(3000);
      /* 10. SM#2 3.5 cycles */
      Serial.println("Mode A --- Step 10 : SM#2 3.5 cycles");
      for (int i = 0; i < 3.5*cycle; i++) {               // 3.5 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      delay(3000);
      /* 12. SM#2 13 inverse cycles */
      Serial.println("Mode A --- Step 12 : SM#2 13 inverse cycles");
      digitalWrite(SM_2_DIR_PIN,HIGH);                    // inverse SM#2 direction
      for (int i = 0; i < 13*cycle; i++) {                // 13 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      digitalWrite(SM_2_DIR_PIN,LOW);
      mode = 0;
      Serial.println("Mode A testing finished.");
    }
    /************************* MODE B *****************************/
    else if ( mode == 2) { 
      Serial.println("Starting mode B......");
      Serial.println("Testing SM#2 operation ......");
 
      /* 6. SM#2 9.5 cycles */
      Serial.println("Mode B --- Step 6 : SM#2 9.5 cycles");
      for (int i = 0; i < 9.5*cycle; i++) {               // 9.5 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      delay(3000);
      /* 8. SM#2 4.5 inverse cycles */
      Serial.println("Mode B --- Step 8 : SM#2 4.5 inverse cycles");
      digitalWrite(SM_2_DIR_PIN,HIGH);                    // inverse SM#2 direction
      for (int i = 0; i < 4.5*cycle; i++) {               // 4.5 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      delay(3000);
      /* 10. SM#2 8 cycles */
      Serial.println("Mode B --- Step 10 : SM#2 8 cycles");
      digitalWrite(SM_2_DIR_PIN,LOW);                      // reset SM#2 direction
      for (int i = 0; i < 8*cycle; i++) {                 // 8 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      delay(3000);
      /* 12. SM#2 13 inverse cycles */
      Serial.println("Mode B --- Step 12 : SM#2 13 inverse cycles");
      digitalWrite(SM_2_DIR_PIN,HIGH);                     // inverse direction
      for (int i = 0; i < 13*cycle; i++) {                // 13 cycle
        digitalWrite(SM_2_STEP_PIN,HIGH);
        delayMicroseconds(speed_2);
        digitalWrite(SM_2_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }
      digitalWrite(SM_2_DIR_PIN,LOW);                      // reset SM#2 direction
      mode = 0;
      Serial.println("Mode B finished.");
    }
    else { // error mode
      Serial.println("Error : mode is INCORRECT.");
      mode = 0;
    }
  }
}
