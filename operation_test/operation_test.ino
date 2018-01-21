/******************* Noodle Machine ******************
 * Author : Wade Lin 
 * Update : 2017/5/24
 * Description :
 *   TEST USE
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
      Serial.println("Testing SM#1.3.4 operations ......");
      /* 1. SM#1 four cycles */
      Serial.println("Mode A --- Step 1 : SM#1 four cycles");
      digitalWrite(SM_1_DIR_PIN,LOW);
      for (int i = 0; i < 4*cycle; i++) {                 // four cycle
        digitalWrite(SM_1_STEP_PIN,HIGH);
        delayMicroseconds(speed_1);
        digitalWrite(SM_1_STEP_PIN,LOW);
        delayMicroseconds(speed_1);
      }
      /* 2. Turn EV#1 on for 10 sec */
      Serial.println("Mode A --- Step 2 : Turn EV#1 on for 10 sec");
      digitalWrite(EV_1_PIN,HIGH);
      delay(6000);                                      // delay 6 sec
      /* 3. At sixth sec after EV#1 operated, SM#1 four inverse cycles. */
      Serial.println("Mode A --- Step 3 : At sixth sec after EV#1 operated, SM#1 four inverse cycles");
      digitalWrite(SM_1_DIR_PIN,HIGH);                    // inverse SM#1 direction
      unsigned long time_record = millis();
      unsigned long time_record_2 = millis();
      for (int i = 0,j = 0; i < 4*cycle; i++) {           // four cycle
        digitalWrite(SM_1_STEP_PIN,HIGH);
        delayMicroseconds(speed_1);
        digitalWrite(SM_1_STEP_PIN,LOW);
        delayMicroseconds(speed_1);
        time_record_2 = millis();
        if (j > 0) continue;                            // check if the EV#1 had already turn off
        if ((time_record_2-time_record) >= 4000) {         // check if EV#1 have trun on for 10 sec
          digitalWrite(EV_1_PIN,LOW);
          j++;
        }
      }
      delay(4000-(time_record_2-time_record));             // delay another 4 sec
      digitalWrite(EV_1_PIN,LOW);
      
      /* 7. SM#3 one cycle */
      Serial.println("Mode A --- Step 7 : SM#3 one cycle");
      for (int i = 0; i < cycle; i++) {                   // one cycle
        digitalWrite(SM_3_STEP_PIN,HIGH);
        delayMicroseconds(speed_3);
        digitalWrite(SM_3_STEP_PIN,LOW);
        delayMicroseconds(speed_3);
      }

      /* 9. SM#4 one cycle */
      Serial.println("Mode A --- Step 9 : SM#4 one cycle");
      for (int i = 0; i < cycle; i++) {                   // one cycle
        digitalWrite(SM_4_STEP_PIN,HIGH);
        delayMicroseconds(speed_4);
        digitalWrite(SM_4_STEP_PIN,LOW);
        delayMicroseconds(speed_4);
      }

      /* 11. Turn EV#3 on for 10 sec */
      Serial.println("Mode A --- Step 11 : Turn EV#3 on for 10 sec");
      digitalWrite(EV_3_PIN,HIGH);
      delay(10000);                                       // 10 sec
      digitalWrite(EV_3_PIN,LOW);

      mode = 0;
      Serial.println("Mode A testing finished.");
    }
    /************************* MODE B *****************************/
    else if ( mode == 2) { 
      Serial.println("Starting mode B......");
      Serial.println("Testing SM#1.3.4 operations ......");
      /* 1. SM#1 four cycles */
      Serial.println("Mode B --- Step 1 : SM#1 four cycles");
      digitalWrite(SM_1_DIR_PIN,LOW);
      for (int i = 0; i < 4*cycle; i++) {                 // four cycle
        digitalWrite(SM_1_STEP_PIN,HIGH);
        delayMicroseconds(speed_1);
        digitalWrite(SM_1_STEP_PIN,LOW);
        delayMicroseconds(speed_1);
      }
      /* 2. Turn EV#1 on for 10 sec */
      Serial.println("Mode B --- Step 2 : Turn EV#1 on for 10 sec");
      digitalWrite(EV_1_PIN,HIGH);
      delay(6000);                                        // 6 sec
      /* 3. At sixth sec after EV#1 operated, SM#1 four inverse cycles. */
      Serial.println("Mode B --- Step 3 : At sixth sec after EV#1 operated, SM#1 four inverse cycles.");
      digitalWrite(SM_1_DIR_PIN,HIGH);                      // inverse SM#1 direction
      unsigned long time_record = millis();
      unsigned long time_record_2 = millis();
      for (int i = 0,j = 0; i < 4*cycle; i++) {             // four cycle
        digitalWrite(SM_1_STEP_PIN,HIGH);
        delayMicroseconds(speed_1);
        digitalWrite(SM_1_STEP_PIN,LOW);
        delayMicroseconds(speed_1);
        time_record_2 = millis();
        if (j > 0) continue;                              // check if the EV#1 had already turn off
        if ((time_record_2-time_record) >= 4000) {           // check if EV#1 have trun on for 10 sec
          digitalWrite(EV_1_PIN,LOW);
          j++;
        }
      }
      delay(4000-(time_record_2-time_record));               // delay 4 sec
      digitalWrite(EV_1_PIN,LOW);
   
      /* 7. SM#4 one cycle */
      Serial.println("Mode B --- Step 7 : SM#4 one cycle");
      for (int i = 0; i < cycle; i++) {                   // one cycle
        digitalWrite(SM_4_STEP_PIN,HIGH);
        delayMicroseconds(speed_4);
        digitalWrite(SM_4_STEP_PIN,LOW);
        delayMicroseconds(speed_4);
      }

      /* 9. SM#3 one cycle */
      Serial.println("Mode B --- Step 9 : SM#3 one cycle");
      for (int i = 0; i < cycle; i++) {                  // one cycle
        digitalWrite(SM_3_STEP_PIN,HIGH);
        delayMicroseconds(speed_3);
        digitalWrite(SM_3_STEP_PIN,LOW);
        delayMicroseconds(speed_2);
      }

      mode = 0;
      Serial.println("Mode B testing finished.");
    }
    else { // error mode
      Serial.println("Error : mode is INCORRECT.");
      mode = 0;
    }
  }
}
