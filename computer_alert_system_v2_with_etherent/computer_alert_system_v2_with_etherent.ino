#include <Keypad.h>
#include <SPI.h>
#include <Ethernet.h>

#define CODE    123456789 // password
#define CODE_N  9         // number of password digits
#define ROWS    4         // Four rows
#define COLS    4         // Four columns

const int redPin       = 0; // Define red LED pin number 
const int greenPin     = 1; // Define green LED pin number 
const int triggerPin_1 = 14; // Define door trigger pin number (light)
const int triggerPin_2 = 15; // Define door trigger pin number (endstop)
const int buzzerPin    = 16; // Define buzzer pin number (A2)
const int currentPin   = 17; // Define current sensor pin number (A3)
const int relayPin     = 18; // Define relay control pin number (A4)

// Define Etherent
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };
IPAddress ip(192,168,2,105);
char MakerIFTTT_Key[]   = "bJa2fXsJqd4GvtJBF-2agaj5wjoTpLTUJnB0x7S-Zyq";
char MakerIFTTT_Event[] = "Alert";
byte server[] = { 34 , 201 , 255 , 3}; // maker.ifttt.com
EthernetClient client;

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
bool pc = true;        // computer state : ON - true OFF - false
bool problem = false;         // problem  state : normal - 0 malfunction - 1
bool alert = false;           // alert   state : ON - 1 OFF - 0
unsigned long int count = 0;
int  LOWCURRENT  = 490;
int  HIGHCURRENT = 525;
int on_high = 0,on_low = 0; // the current data measured when computer is on 
int sleep_high = 0,sleep_low = 0; // the current data measured when computer is sleeping
int setON_status = 0;      // if the setON function is complete, set the status value to 1
int setSLEEP_status = 0;   // if the setSLEEP function is complete, set the status value to 1
char code[CODE_N];

// Define functions
int unlock();
void setON();
void setSLEEP();
void Buzzer(int number, int delay_time = 1000); // buzzer operation mode
void Alert(char *school, char *number,char *event);
char *append_str(char *here, char *s);
char *append_ul(char *here, unsigned long u);
  
void setup() {
  //Serial.begin(9600);
  Serial.println(F("System Starting..."));
  pinMode(buzzerPin,     OUTPUT); //Set buzzerPin as output
  pinMode(currentPin,    INPUT ); //Set current as input
  pinMode(redPin,        OUTPUT); //Set buzzerPin as output
  pinMode(greenPin,      OUTPUT); //Set buzzerPin as output
  pinMode(triggerPin_1,  INPUT ); //Set buzzerPin as input
  pinMode(triggerPin_2,  INPUT ); //Set buzzerPin as input
  pinMode(relayPin,      OUTPUT); //Set buzzerPin as output
  digitalWrite(buzzerPin,HIGH  ); // Buzzer close
  digitalWrite(relayPin, HIGH  ); // AC current close (通路)
  digitalWrite(greenPin, LOW  ); // green light off
  digitalWrite(redPin,   HIGH   ); // red light on
  delay(1000);
  
  // setting code
  Serial.println(F("Setting code number..."));
  long int code_value = CODE;
  for (int n = CODE_N ; n > 0 ; n--) {
    code[n-1] = code_value % 10 + 48;
    if (n == 1) code_value = 0;
    else code_value /= 10;
  }
  Serial.print(F("Code : "));
  for (int n = 0 ; n < CODE_N ; n++)  Serial.print(code[n]);
  Serial.println();
  delay(1000);

  // setting ethernet
  Serial.println(F("Setting ethernet shield and connecting to server..."));
  if (Ethernet.begin(mac) == 0) {
    Serial.println(F("Failed to configure Ethernet using DHCP"));
    Ethernet.begin(mac, ip);
  }
  else Serial.println(F("Connect to Etherent shield with MAC address"));
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println(F("Connecting to server..."));
  if (client.connect(server,80)) Serial.println(F("connected"));
  else Serial.println(F("connection failed"));
  delay(1000);
  
  // initialize the variables
  pc = true;        
  problem = false;     
  alert = false; 

  // ethernet connection confirm
  Alert("NCKU","001","Ethernet setup confirmed!");
  delay(1000);
  
  Buzzer(2,100);
  digitalWrite(greenPin, HIGH  ); // green light on
  digitalWrite(redPin,   LOW   ); // red light off
  Serial.println(F("\nAll setup complete!\n"));
  
}

void loop() {
  // Code Pad Read
  char key = Codepad.getKey();
  if (key == 'A') {
    Serial.println(F("Alert System operating..."));
    alert = true;  // start the alert system 
    Buzzer(1,50);
  }
  if (key == 'B') {
    Serial.println(F("Unlocking the alert system..."));
    unlock();   // close the alert system (require password)
  }
  if (key == 'C') {  
    Serial.println(F("Computer awake current status setting start..."));
    setON();    // set the current value when computer is on
  }
  if (key == 'D') {
    Serial.println(F("Computer sleep current status setting start..."));
    setSLEEP(); // set the current value when computer is sleeping
  }

  // System Status LED Display
  if (problem) { // problem occured
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
    if (alert) {
      digitalWrite(buzzerPin, LOW);  //Setting buzzer pin to LOW (buzzer on)
      //Buzzer(1,500);
      Alert("NCKU","001","Door Open");  // trigger ifttt event
      Serial.println(F("Door Opened!"));
    }    
  }
  else {
    digitalWrite(redPin,LOW);     // red light off
  }
  
  // Current Monitor
  current = analogRead(currentPin);
  Serial.print(F("Count: "));
  Serial.print(count);
  Serial.print(F("  Computer Current: "));
  Serial.println(current);
  delay(100);
  /*
  if (pc) {
    // counting
    if (current < HIGHCURRENT && current > LOWCURRENT) count++;   // determine whether the computer is in the sleep mode
    else count = 0; // if not in sleep mode, clear the count value
    
    if (count > 200 && count < 400) Serial.print(F(" Sleep Mode Confirm ... 1 ")); // sleep mode confirmed for 20 second
    if (count > 400 && count < 600) Serial.print(F(" Sleep Mode Confirm ... 2 ")); // sleep mode confirmed for 40 second
    if (count > 600) {
      Serial.print(F(" Sleep Mode Confirm ... 3 ")); // sleep mode confirmed for 60 second
      Serial.println(F("Power Shutdown")); // computer power shut down 
      digitalWrite(relayPin,LOW); // AC current open (斷路)
      pc = false; // computer in off state
      count = 0; // reset count number
      delay(10000);
      digitalWrite(relayPin,HIGH); // AC current close (通路)
    }
  }
  else {
    Serial.print(F("Computer off... "));
    // counting
    if (current > HIGHCURRENT || current < LOWCURRENT) count++;   // determine whether the computer is in the sleep mode
    if (count > 600){
      pc = true; // computer is on state
      count = 0; // reset count number
      delay(1000);
    }
  }*/
}

/*  Functions Definition  */
// unlock the alert system
int unlock() {
  char input[CODE_N];
  int num = 0;
  bool correct = false;

  // Read the code 
  while(1) {
    if (correct) { // code correct
        Serial.println(F("Correct password!"));
        digitalWrite(buzzerPin,HIGH);  //Setting buzzer pin to HIGH (buzzer off)
        alert = 0; // close the alert function
        Buzzer(3,100);
        break;
    }
    char key = Codepad.getKey();
    if (key) {
      Serial.print(F("Key inserted : "));
      Serial.println(key);
      if (key == 'A') { // back
        Serial.println(F("Back"));
        Serial.print(F("Inserted Code : "));
        for (int n = 0 ; n < num-1 ; n++)  Serial.print(input[n]);
        Serial.println();
        input[num-1] = 0;
        num --;
      }
      else if (key == 'B') { // clear all
        for (; num > 0 ; num--) input[num] = 0;
        Serial.println(F("Clear all"));
      }
      else if (key == 'C') { // cancel
        Serial.println(F("Unlock Cancel"));
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
            Serial.println(F("Incorrect password!"));
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
  // measure high current
  for (int n = 0; n < 100 ; n++) {
    current = analogRead(currentPin);
    if (current > on_high) on_high = current;
    delay(50);
    // processing signal generation
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);  // green light on
    else digitalWrite(greenPin,LOW);  // green light off
  }
  current = analogRead(currentPin);
  on_low = current;
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
  Serial.println(F("Computer awake current status is updated!"));
  
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
    Serial.print(F("Current Limit Value Change : "));
    Serial.print(F("HIGH = "));
    Serial.print(HIGHCURRENT);
    Serial.print(F(" ; LOW = "));
    Serial.println(LOWCURRENT);
  }
}
// set the current when computer sleep
void setSLEEP() {
  // measure high current
  for (int n = 0; n < 100 ; n++) {
    current = analogRead(currentPin);
    if (current > sleep_high) sleep_high = current;
    delay(50);
    // processing signal generation
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);  // green light on
    else digitalWrite(greenPin,LOW);  // green light off
  }
  current = analogRead(currentPin);
  sleep_low = current;
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
  Serial.println(F("Computer sleep current status is updated!"));
  
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
    Serial.print(F("Current Limit Value Change : "));
    Serial.print(F("HIGH = "));
    Serial.print(HIGHCURRENT);
    Serial.print(F(" ; LOW = "));
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
// send alert message
void Alert(char *school, char *number,char *event) {
    // construct the POST request
    Serial.println(F("Sending alert message"));
    char post_rqst[256];    // hand-calculated to be big enough

    char *p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");

    // we need to remember where the content length will go, which is:
    char *content_length_here = p;

    // it's always two digits, so reserve space for them (the NN)
    p = append_str(p, "NN\r\n");

    // end of headers
    p = append_str(p, "\r\n");

    // construct the JSON; remember where we started so we will know len
    char *json_start = p;

    // As described - this example reports a pin, uptime, and "hello world"
    p = append_str(p, "{\"value1\":\"");    // value is defined as "No"
    p = append_str(p, school);
    p = append_str(p, "\",\"value2\":\"");  // value is defined as "Time"
    p = append_str(p, number);
    p = append_str(p, "\",\"value3\":\"");  // value is defined as "Event"
    p = append_str(p, event);
    p = append_str(p, "\"}");

    // go back and fill in the JSON length
    // we just know this is at most 2 digits (and need to fill in both)
    int i = strlen(json_start);
    content_length_here[0] = '0' + (i/10);
    content_length_here[1] = '0' + (i%10);

    // finally we are ready to send the POST to the server!
    client.print(post_rqst);
    Serial.println(F("Message sending sucess!"));
}
char *append_str(char *here, char *s) {
    while (*here++ = *s++)
  ;
    return here-1;
}
char *append_ul(char *here, unsigned long u) {
    char buf[20];       // we "just know" this is big enough

    return append_str(here, ultoa(u, buf, 10));
}
