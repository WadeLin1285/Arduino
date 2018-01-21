#include <Keypad.h>

#define CODE   123456789  // password
#define CODE_N  9        // number of password digits
#define ROWS    4 // Four rows
#define COLS    4 // Four columns

const int redPin      = 15; // Define red LED pin number (A1)
const int greenPin    = 14; // Define green LED pin number (A0)
const int buzzerPin   = 16; // Define buzzer pin number (A2)
const int currentPin  = 17; // Define current sensor pin number (A3)
const int triggerPin_1 = 0; // Define door trigger pin number (light)
const int triggerPin_2 = 1; // Define door trigger pin number (endstop)
const int relayPin    = 18; // Define relay control pin number (A4)

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {19, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 5, 3, 2}; //connect to the column pinouts of the keypad
Keypad Codepad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Define variables
int current;
int computer = 1;        // computer state : ON - 1 OFF - 0
int problem = 0;         // problem  state : normal - 0 malfunction - 1
int alert = 0;           // alert   state : ON - 1 OFF - 0
unsigned long int count = 0;
int  LOWCURRENT  = 495;
int  HIGHCURRENT = 525;
int on_high = 0,on_low = 0; // the current data measured when computer is on 
int sleep_high = 0,sleep_low = 0; // the current data measured when computer is sleeping
int setON_status = 0;      // if the setON function is complete, set the status value to 1
int setSLEEP_status = 0;   // if the setSLEEP function is complete, set the status value to 1
char code[CODE_N] = {};
// Define functions
int unlock();
void setON();
void setSLEEP();
void Buzzer(int number, int delay_time = 1000); // buzzer operation mode

void setup() {
  Serial.begin(9600);
  Serial.println("System Starting...");
  pinMode(buzzerPin, OUTPUT);   //Set buzzerPin as output
  pinMode(currentPin, INPUT);   //Set current as input
  pinMode(redPin, OUTPUT);      //Set buzzerPin as output
  pinMode(greenPin, OUTPUT);    //Set buzzerPin as output
  pinMode(triggerPin_1, INPUT); //Set buzzerPin as input
  pinMode(triggerPin_2, INPUT); //Set buzzerPin as input
  pinMode(relayPin, OUTPUT);    //Set buzzerPin as output
  digitalWrite(buzzerPin,HIGH); // Buzzer close
  digitalWrite(relayPin,HIGH);  // AC current close (通路)
  digitalWrite(greenPin,HIGH);  // green light on
  digitalWrite(redPin,LOW);   // red light off
  Buzzer(2,50);
  // setting code
  long code_value = CODE;
  for (int n = CODE_N ; n > 0 ; n--) {
    code[n-1] = code_value % 10 + 48;
    code_value /= 10;
  }
  Serial.print("Code : ");
  for (int n = 0 ; n < CODE_N ; n++)  Serial.print(code[n]);
  Serial.println();
}

void loop() {
  // Code Pad Read
  char key = Codepad.getKey();
  if (key == 'A') alert = 1;  // start the alert system 
  if (key == 'B') unlock();   // close the alert system (require password)
  if (key == 'C') setON();    // set the current value when computer is on
  if (key == 'D') setSLEEP(); // set the current value when computer is sleeping

  // System Status LED Display
  if (problem == 1) { // problem occured
    digitalWrite(greenPin,LOW);  // green light off
    digitalWrite(redPin,HIGH);   // red light on
  }
  else {
    digitalWrite(greenPin,HIGH);  // green light on
    digitalWrite(redPin,LOW);    // red light off
  }

  // Door Trigger Sensor and Buzzer Alert
  if (digitalRead(triggerPin_1) == HIGH || digitalRead(triggerPin_2) == HIGH) {
    digitalWrite(redPin,HIGH);    // red light on
    if (alert == 1) digitalWrite(buzzerPin, LOW);  //Setting buzzer pin to LOW (buzzer on)
    //Serial.println("Door Opened!");
  }
  else {
    digitalWrite(redPin,LOW);     // red light off
    if (alert == 1) digitalWrite(buzzerPin,HIGH);  //Setting buzzer pin to HIGH(buzzer off)
  }

  /*  
  // Current Monitor
  current = analogRead(currentPin);
  Serial.println(current);
  delay(100);
  if (current < HIGHCURRENT && current > LOWCURRENT) count++;   // determine whether the computer is in the sleep mode
  else count = 0; // if not in sleep mode, clear the count value
  if (computer == 1) {
    if (count > 200 && count < 400) Serial.print(" Sleep Mode Confirm ... 1 "); // sleep mode confirmed for 20 second
    if (count > 400 && count < 600) Serial.print(" Sleep Mode Confirm ... 2 "); // sleep mode confirmed for 40 second
    if (count > 600) {
      Serial.print(" Sleep Mode Confirm ... 3 "); // sleep mode confirmed for 60 second
      Serial.println("Power Shutdown"); // computer power shut down 
      digitalWrite(relayPin,LOW); // AC current open (斷路)
      computer = 0; // computer in off state
    }
    delay(10000);
    digitalWrite(relayPin,HIGH); // AC current close (通路)
  }
  */
}

/*  Functions Definition  */
// unlock the alert system
int unlock() {
  char input[CODE_N];
  int num = 0;
  bool correct = false;

  while(1) {
    if (correct) { // code correct
        Serial.println("Correct password!");
        alert = 0; // close the alert function
        Buzzer(3,100);
        break;
    }
    char key = Codepad.getKey();
    if (key) {
      Serial.print("Key inserted : ");
      Serial.println(key);
      if (key == 'A') { // back
        Serial.println("Back");
        Serial.print("Inserted Code : ");
        for (int n = 0 ; n < num-1 ; n++)  Serial.print(input[n]);
        Serial.println();
        input[num-1] = 0;
        num --;
      }
      else if (key == 'B') { // clear all
        for (; num > 0 ; num--) input[num] = 0;
        Serial.println("Clear all");
      }
      else if (key == 'C') { // cancel
        Serial.println("Unlock Cancel");
        return 0;
      }
      else {
        input[num] = key;
        if (num == (CODE_N-1)) {
          for (int n = 0 ; n < CODE_N ; n++) {
            if (input[n] != code[n]) break;     // incorrect code
            if (n == CODE_N-1) correct = true;
          }
          if (!correct) {
            for (; num > 0 ; num--) input[num] = 0;
            Serial.println("Incorrect password!");
            Buzzer(1);
          }
        }
        else num ++;
      }
    }
  }
}
// set the current when computer awake
void setON() {
  Serial.println("Computer awake current status setting start...");
  // measure high current
  for (int n = 0; n < 100 ; n++) {
    current = analogRead(currentPin);
    if (current > on_high) on_high = current;
    delay(50);
    // processing signal generation
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);  // green light on
    else digitalWrite(greenPin,LOW);  // green light off
  }
  // measure low current
  for (int n = 0; n < 100 ; n++) {
    current = analogRead(currentPin);
    if (current < on_low) on_low = current;
    delay(50);
    // processing signal generation
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);  // green light on
    else digitalWrite(greenPin,LOW);  // green light off
  }
  setON_status = 1; // status update
  Serial.println("Computer awake current status is updated!");
  
  // determine whether both setting are done
  if (setON_status == 1 && setSLEEP_status == 1) {
    HIGHCURRENT = (on_high + sleep_high) / 2 ;
    LOWCURRENT  = (on_low  + sleep_low) / 2 ;
    // update the variables
    setON_status = 0;
    setSLEEP_status = 0;
    on_high = 0;
    on_low = 0;
    sleep_high = 0;
    sleep_low = 0;
    // processing signal generation
    Buzzer(3,100);
    Serial.print("Current Limit Value Change : ");
    Serial.print("HIGH = ");
    Serial.print(HIGHCURRENT);
    Serial.print(" ; LOW = ");
    Serial.println(LOWCURRENT);
  }
}
// set the current when computer sleep
void setSLEEP() {
  Serial.println("Computer sleep current status setting start...");
  // measure high current
  for (int n = 0; n < 100 ; n++) {
    current = analogRead(currentPin);
    if (current > sleep_high) sleep_high = current;
    delay(50);
    // processing signal generation
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);  // green light on
    else digitalWrite(greenPin,LOW);  // green light off
  }
  // measure low current
  for (int n = 0; n < 100 ; n++) {
    current = analogRead(currentPin);
    if (current < sleep_low) sleep_low = current;
    delay(50);
    // processing signal generation
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);  // green light on
    else digitalWrite(greenPin,LOW);  // green light off
  }
  setSLEEP_status = 1; // status update
  Serial.println("Computer sleep current status is updated!");
  
  // determine whether both setting are done
  if (setON_status == 1 && setSLEEP_status == 1) {
    HIGHCURRENT = (on_high + sleep_high) / 2 ;
    LOWCURRENT  = (on_low  + sleep_low) / 2 ;
    // update the variables
    setON_status = 0;
    setSLEEP_status = 0;
    on_high = 0;
    on_low = 0;
    sleep_high = 0;
    sleep_low = 0;
    // processing signal generation
    Buzzer(3,100);
    Serial.print("Current Limit Value Change : ");
    Serial.print("HIGH = ");
    Serial.print(HIGHCURRENT);
    Serial.print(" ; LOW = ");
    Serial.println(LOWCURRENT);
  }
}
// buzzer mode
void Buzzer(int number, int delay_time = 1000){
  for (int n = 0; n < number ; n++) {
      digitalWrite(buzzerPin, LOW);  //Setting buzzer pin to LOW (buzzer on)
      delay(delay_time);
      digitalWrite(buzzerPin,HIGH);  //Setting buzzer pin to HIGH(buzzer off)
      delay(delay_time);
  }
}
