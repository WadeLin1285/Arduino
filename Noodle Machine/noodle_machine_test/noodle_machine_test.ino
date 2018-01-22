/******************* Noodle Machine ******************
 * Author : Wade Lin 
 * Update : 2017/5/24
 * Description :
 *   This program is use for testing the operation of 
 *   control Arduino MEGA board with stepper motors and 
 *   electrical valves.
 *   The main goals of testing are: 
 *      a. test the pins and pinModes are correct
 *      b. test the number of step for one cycle of 
 *         stepper motors
 *      c. test the direction of motors
 *      d. test the speed of motors is suitable
 *      e. test some examples in full operation
 * Devices :
 *   1 * Arduino MEGA board
 *   1 * RAMPS 1.4 board
 *   4 * DRV 8825 (motor driver)
 *   4 * stepper motor
 *   3 * electrical valve
 */
/************** Define the pin number ***************/
// stepper motor #1
#define SM_1_STEP_PIN      26
#define SM_1_DIR_PIN       28
#define SM_1_ENABLE_PIN    24

// stepper motor #2
#define SM_2_STEP_PIN      36
#define SM_2_DIR_PIN       34
#define SM_2_ENABLE_PIN    30

// stepper motor #3
#define SM_3_STEP_PIN      54
#define SM_3_DIR_PIN       55
#define SM_3_ENABLE_PIN    38

// stepper motor #4
#define SM_4_STEP_PIN      61
#define SM_4_DIR_PIN       60
#define SM_4_ENABLE_PIN    62

// electrical valve
#define EV_1_PIN           10
#define EV_2_PIN            9
#define EV_3_PIN            8

// others
#define LED_PIN            13
#define Button_A_PIN       49
#define Button_B_PIN       51
#define Button_START_PIN   53

unsigned int mode = 0;                                 // store the mode that user choose (1:mode A / 2:mode B)
const int speed_1 = 1000;                              // set the speed of each motor (Unit: microsecond) 
const int speed_2 = 1000;
const int speed_3 = 1000;
const int speed_4 = 1000;
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
/***************** a. test the pins and pinModes are correct ******************/
  Serial.println(" Test A start.");
  // SM#1
  Serial.println("SM#1 test");
  for (int i = 0; i < 20; i++) {                        // SM#1 36 angle
    digitalWrite(SM_1_STEP_PIN,HIGH);
    delayMicroseconds(speed_1);
    digitalWrite(SM_1_STEP_PIN,LOW);
    delayMicroseconds(speed_1);
  }
  delay(1000);
  digitalWrite(SM_1_DIR_PIN,HIGH);
  Serial.println("SM#1 inverse");
  for (int i = 0; i < 20; i++) {                        // SM#1 36 angle (inverse)
    digitalWrite(SM_1_STEP_PIN,HIGH);
    delayMicroseconds(speed_1);
    digitalWrite(SM_1_STEP_PIN,LOW);
    delayMicroseconds(speed_1);
  }
  digitalWrite(SM_1_DIR_PIN,LOW);
  delay(1000);
  // SM#2
  Serial.println("SM#2 test");
  for (int i = 0; i < 20; i++) {                        // SM#2 36 angle
    digitalWrite(SM_2_STEP_PIN,HIGH);
    delayMicroseconds(speed_2);
    digitalWrite(SM_2_STEP_PIN,LOW);
    delayMicroseconds(speed_2);
  }
  delay(1000);
  digitalWrite(SM_2_DIR_PIN,HIGH);
  Serial.println("SM#2 inverse");
  for (int i = 0; i < 20; i++) {                        // SM#2 36 angle (inverse)
    digitalWrite(SM_2_STEP_PIN,HIGH);
    delayMicroseconds(speed_2);
    digitalWrite(SM_2_STEP_PIN,LOW);
    delayMicroseconds(speed_2);
  }
  digitalWrite(SM_2_DIR_PIN,LOW);
  delay(1000);
  // SM#3
  Serial.println("SM#3 test");
  for (int i = 0; i < 20; i++) {                        // SM#3 36 angle
    digitalWrite(SM_3_STEP_PIN,HIGH);
    delayMicroseconds(speed_3);
    digitalWrite(SM_3_STEP_PIN,LOW);
    delayMicroseconds(speed_3);
  }
  delay(1000);
  digitalWrite(SM_3_DIR_PIN,HIGH);
  Serial.println("SM#3 inverse");
  for (int i = 0; i < 20; i++) {                        // SM#3 36 angle (inverse)
    digitalWrite(SM_3_STEP_PIN,HIGH);
    delayMicroseconds(speed_3);
    digitalWrite(SM_3_STEP_PIN,LOW);
    delayMicroseconds(speed_3);
  }
  digitalWrite(SM_3_DIR_PIN,LOW);
  delay(1000);
  // SM#4
  Serial.println("SM#4 test");
  for (int i = 0; i < 20; i++) {                        // SM#4 36 angle
    digitalWrite(SM_4_STEP_PIN,HIGH);
    delayMicroseconds(speed_4);
    digitalWrite(SM_4_STEP_PIN,LOW);
    delayMicroseconds(speed_4);
  }
  delay(1000);
  digitalWrite(SM_4_DIR_PIN,HIGH);
  Serial.println("SM#4 inverse ");
  for (int i = 0; i < 20; i++) {                        // SM#4 36 angle (inverse)
    digitalWrite(SM_4_STEP_PIN,HIGH);
    delayMicroseconds(speed_4);
    digitalWrite(SM_4_STEP_PIN,LOW);
    delayMicroseconds(speed_4);
  }
  digitalWrite(SM_4_DIR_PIN,LOW);
  delay(1000);
  Serial.println(" Test A completed.");
/***************** b. test the number of step for one cycle of stepper motors *****************/
  Serial.println(" Test B start.");
  // SM#1
  Serial.println("SM#1 full cycle test");
  for (int i = 0; i < cycle; i++) {                      // SM#1 full cycle
    digitalWrite(SM_1_STEP_PIN,HIGH);
    delayMicroseconds(speed_1);
    digitalWrite(SM_1_STEP_PIN,LOW);
    delayMicroseconds(speed_1);
  }
  delay(1000);
  // SM#2
  Serial.println("SM#2 full cycle test");
  for (int i = 0; i < cycle; i++) {                     // SM#2 full cycle
    digitalWrite(SM_2_STEP_PIN,HIGH);
    delayMicroseconds(speed_2);
    digitalWrite(SM_2_STEP_PIN,LOW);
    delayMicroseconds(speed_2);
  }
  delay(1000);
  // SM#3
  Serial.println("SM#3 full cycle test");
  for (int i = 0; i < cycle; i++) {                     // SM#3 full cycle
    digitalWrite(SM_3_STEP_PIN,HIGH);
    delayMicroseconds(speed_3);
    digitalWrite(SM_3_STEP_PIN,LOW);
    delayMicroseconds(speed_3);
  }
  delay(1000);
  // SM#4
  Serial.println("SM#4 full cycle test");
  for (int i = 0; i < cycle; i++) {                     // SM#4 full cycle
    digitalWrite(SM_4_STEP_PIN,HIGH);
    delayMicroseconds(speed_4);
    digitalWrite(SM_4_STEP_PIN,LOW);
    delayMicroseconds(speed_4);
  }
  delay(1000);
  Serial.println(" Test B completed.");
/**************** c. test the direction of motors (SKIP)  ****************/ 
/**************** d. test the speed of motors is suitable (SKIP) *****************/
/**************** e. test some examples in full operation *****************/
}

