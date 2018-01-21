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
#define EV_1_PIN          10
#define EV_2_PIN           9

// others
#define LED_PIN           13

void setup() {
  // set pin modes
  // SM#1
  pinMode(SM_1_STEP_PIN  , OUTPUT);
  pinMode(SM_1_DIR_PIN   , OUTPUT);
  pinMode(SM_1_ENABLE_PIN, OUTPUT);
  // SM#2
  pinMode(SM_2_STEP_PIN  , OUTPUT);
  pinMode(SM_2_DIR_PIN   , OUTPUT);
  pinMode(SM_2_ENABLE_PIN, OUTPUT);
  // SM#3
  pinMode(SM_3_STEP_PIN  , OUTPUT);
  pinMode(SM_3_DIR_PIN   , OUTPUT);
  pinMode(SM_3_ENABLE_PIN, OUTPUT);
  // SM#4
  pinMode(SM_4_STEP_PIN  , OUTPUT);
  pinMode(SM_4_DIR_PIN   , OUTPUT);
  pinMode(SM_4_ENABLE_PIN, OUTPUT);
  // EVs and others
  pinMode(EV_1_PIN,OUTPUT);
  pinMode(EV_2_PIN,OUTPUT);
  pinMode(LED_PIN ,OUTPUT);

  // enable the output signal to stepper motor
  digitalWrite(SM_1_ENABLE_PIN,LOW);
  digitalWrite(SM_2_ENABLE_PIN,LOW);
  digitalWrite(SM_3_ENABLE_PIN,LOW);
  digitalWrite(SM_4_ENABLE_PIN,LOW);
}

void loop () {
  
  // LED control
  if (millis() %1000 <500) 
   digitalWrite(LED_PIN,HIGH);
  else
   digitalWrite(LED_PIN,LOW);
   
  // stepper motor direction
  if (millis() %10000 <5000) {
    digitalWrite(SM_1_DIR_PIN,HIGH);
    digitalWrite(SM_2_DIR_PIN,HIGH);
    digitalWrite(SM_3_DIR_PIN,HIGH);
    digitalWrite(SM_4_DIR_PIN,HIGH);
  }
  else {
    digitalWrite(SM_1_DIR_PIN,LOW);
    digitalWrite(SM_2_DIR_PIN,LOW);
    digitalWrite(SM_3_DIR_PIN,LOW);
    digitalWrite(SM_4_DIR_PIN,LOW);
  }
  
  // stepper motor motion
  // step start
  digitalWrite(SM_1_STEP_PIN,HIGH);
  digitalWrite(SM_2_STEP_PIN,HIGH);
  digitalWrite(SM_3_STEP_PIN,HIGH);
  digitalWrite(SM_4_STEP_PIN,HIGH);
  // velocity control
  delay(1);
  // step stop
  digitalWrite(SM_1_STEP_PIN,LOW);
  digitalWrite(SM_2_STEP_PIN,LOW);
  digitalWrite(SM_3_STEP_PIN,LOW);
  digitalWrite(SM_4_STEP_PIN,LOW);  
}
