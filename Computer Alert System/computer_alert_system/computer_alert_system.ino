#include <Keypad.h>
#include <SPI.h>
#include <Ethernet.h>

#define ROWS    4           // Four rows
#define COLS    4           // Four columns

/***************************** 以下數值可做更改 *********************************/
#define CODE    123456789   // 系統密碼 (Hint: 可自行改寫，但僅可為數字)
#define CODE_N  9           // 系統密碼長度 (Hint:若密碼有更動，需檢查密碼長度)
#define TEST    1           // 測試模式 (Hint:若為0則為正式使用；1為測試使用)
#define DATA1   "NCKU"      // 網路訊息通知之資料1
#define DATA2   "001"       // 網路訊息通知之資料2
#define SHUTDOWN_TIME 60    // 系統判斷關機的持續時間 (Hint:若系統偵測到電腦處於睡眠狀態，且連續持續SUHTDOWN_TIME，就會關閉電腦電源) (Hint:單位-秒)
#define RESTART_TIME  10    // 系統重新啟動電源的時間 (Hint:若系統關閉電腦電源後，經過RESTART_TIME後，會重新開啟電腦電源) (Hint:單位-秒)

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFE };                      // 網路擴張版之 MAC 地址 (Hint:若系統出現無法連上 MAC 或 DHCP 訊息時，可能為網路線未連接好，或沒有網際網路連線)
IPAddress ip(192,168,2,105);                                              // 網路擴張版之 IP 地址 (Hint:此設定為備用之使用)
char MakerIFTTT_Key[]   = "bJa2fXsJqd4GvtJBF-2agaj5wjoTpLTUJnB0x7S-Zyq";  // 此3行程式碼須和前端程式互相配合設定
char MakerIFTTT_Event[] = "Alert";                                        // 此3行程式碼須和前端程式互相配合設定
byte server[] = { 34 , 201 , 225 , 3};               // 網路伺服器IP位置  // 此3行程式碼須和前端程式互相配合設定
/********************************************************************************/

const int redPin       = 0;  // Define red LED pin number 
const int greenPin     = 1;  // Define green LED pin number 
const int triggerPin_1 = 14; // Define door trigger pin number (light)
const int triggerPin_2 = 15; // Define door trigger pin number (endstop)
const int buzzerPin    = 16; // Define buzzer pin number (A2)
const int currentPin   = 17; // Define current sensor pin number (A3)
const int relayPin     = 18; // Define relay control pin number (A4)

// Define Etherent
EthernetClient client;

// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {19, 9, 8, 7};                                         //connect to the row pinouts of the keypad
byte colPins[COLS] = { 6, 5, 3, 2};                                         //connect to the column pinouts of the keypad
Keypad Codepad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Define variables
int current;
bool pc = true;                                                             // computer state : ON - true OFF - false
bool problem = false;                                                       // problem  state : normal - 0 malfunction - 1
bool alert = false;                                                         // alert   state : ON - 1 OFF - 0
unsigned long int count = 0,count2 = 0,t = 0,old_t = 0; // time of system
int  LOWCURRENT  = 490;
int  HIGHCURRENT = 525;
int on_high = 0,on_low = 0;                                                 // the current data measured when computer is on 
int sleep_high = 0,sleep_low = 0;                                           // the current data measured when computer is sleeping
int setON_status = 0;                                                       // if the setON function is complete, set the status value to 1
int setSLEEP_status = 0;                                                    // if the setSLEEP function is complete, set the status value to 1
char code[CODE_N];         

// Define functions
int unlock();
void setON();
void setSLEEP();
void Buzzer(int number, int delay_time = 1000);                             // buzzer operation mode
void Alert(char *school, char *number,char *event);
char *append_str(char *here, char *s);
char *append_ul(char *here, unsigned long u);
int checkAlert();

void setup() {
  Serial.begin(9600);                                                         // (Hint:若不要在電腦中顯示程式碼說明，可註解掉此行)
  Serial.println(F("System Starting..."));
  pinMode(buzzerPin,     OUTPUT);         //Set buzzerPin as output
  pinMode(currentPin,    INPUT );         //Set current as input
  pinMode(redPin,        OUTPUT);         //Set buzzerPin as output
  pinMode(greenPin,      OUTPUT);         //Set buzzerPin as output
  pinMode(triggerPin_1,  INPUT );         //Set buzzerPin as input
  pinMode(triggerPin_2,  INPUT );         //Set buzzerPin as input
  pinMode(relayPin,      OUTPUT);         //Set buzzerPin as output
  digitalWrite(buzzerPin,HIGH  );         // Buzzer close
  digitalWrite(relayPin, HIGH  );         // AC current close (通路)
  digitalWrite(greenPin, LOW   );         // green light off
  digitalWrite(redPin,   HIGH  );        // red light on
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
  Alert(DATA1,DATA2,"Ethernet setup confirmed!");
  delay(1000);
 
  Buzzer(2,100);                                                           // 系統設定完成時，會發出2次嗶嗶聲 (Hint: Buzzer(a,b) a為嗶嗶聲之次數，b為每次聲音之間隔時間(單位為毫秒ms=0.001s))
  digitalWrite(greenPin, HIGH  ); // green light on                        // 系統設定完成時，亮綠燈
  digitalWrite(redPin,   LOW   ); // red light off                         
  Serial.println(F("\nAll setup complete!\n"));
}

void loop() {
  // Code Pad Read
  char key = Codepad.getKey();
  if (key == 'A') {                                                        // 點擊A按鈕，進入鎖定模式
    Serial.println(F("Alert System operating..."));
    alert = true;                                                          // start the alert system                                                         
    Buzzer(1,50);
  }
  if (key == 'B') {                                                        // 點擊B按鈕，進入解鎖模式 (Hint:若在解鎖時，觸發警鈴，將會回到鎖定模式)
    Serial.println(F("Unlocking the alert system..."));               
    Buzzer(1,50);
    unlock();                                                              // close the alert system (require password)
  }
  if (key == 'C') {                                                        // 點擊C按鈕，進入設定電腦開機時之電流 (Hint:必須在電腦開機時使用)
    Serial.println(F("Computer awake current status setting start..."));
    Buzzer(1,50);
    setON();                                                               // set the current value when computer is on
  }
  if (key == 'D') {                                                        // 點擊D按鈕，進入設定電腦睡眠時之電流 (Hint:必須在電腦睡眠時使用)
    Serial.println(F("Computer sleep current status setting start..."));
    Buzzer(1,50);
    setSLEEP();                                                            // set the current value when computer is sleeping
  }

  // System Status LED Display
  if (problem) {                    // problem occured
    digitalWrite(greenPin,LOW);     // green light off
    digitalWrite(redPin,HIGH);      // red light on
  }
  else {
    digitalWrite(greenPin,HIGH);    // green light on
    digitalWrite(redPin,LOW);       // red light off
  }

  checkAlert();
  
  // 控制系統偵測電腦電流之數值，並顯示出來
  current = analogRead(currentPin);
  Serial.print(F("Duration Time: "));
  Serial.print(count/1000);
  Serial.print(F(" s  Computer Current: "));
  Serial.println(current);
  delay(100);
  
  // 電腦電流控制系統 (Hint:電腦將在睡眠後SUHTDOWN_TIME秒時，強制切斷電源，並在RESTART_TIME秒後重新連結電源)
  if (pc) {
    t = millis();                                                                        // aquire time data
    if (old_t == 0) old_t = t;
    // counting
    if (current < HIGHCURRENT && current > LOWCURRENT) {
      count = count + (t - old_t);                                                       // determine whether the computer is in the sleep mode
      Serial.print(F(" Sleep Mode Confirm ...  "));
    }
    else count = 0;                                                                      // if not in sleep mode, clear the count value

    old_t = t;                                                                           // update old time data
    
    if (count > (SHUTDOWN_TIME*1000)) {
      Serial.println(F("Power Shutdown"));                                                 // computer power shut down 
      digitalWrite(relayPin,LOW);                                                         // AC current open (斷路)
      pc = false;                                                                         // setting computer on-off state to "false(off)"
      count = 0;                                                                          // reset count number
      count2 = 0;
    }
  }
  else {
    t = millis();                                                                         // aquire time data
    Serial.print(F("Computer off... "));
    // counting
    count2 = count2 + (t - old_t);
    if (current > HIGHCURRENT || current < LOWCURRENT) count = count + (t - old_t);       // determine whether the computer is in the sleep mode
    if (count2 > (RESTART_TIME*1000)) digitalWrite(relayPin,HIGH);                        // AC current close (通路)
    if (count  > (SHUTDOWN_TIME*1000)){
      pc = true;                                                                          // setting computer on-off state to "true(on)"
      count = 0;                                                                          // reset count number
      count2 = 0;
    }
    old_t = t;                                                                            // update old time data
  }
}

/*  Function Definition  */
// unlock the alert system
int unlock() {
  char input[CODE_N];
  int num = 0;
  bool correct = false;

  // Read the code 
  while(1) {
    if (checkAlert()) break;                                                             // still check the trigger

    char key = Codepad.getKey();
    if (key) {
      
      Buzzer(1,50);
      
      Serial.print(F("Key inserted : "));
      Serial.println(key);
      if (key == 'A') {                               // back
        Serial.println(F("Back"));
        Serial.print(F("Inserted Code : "));
        for (int n = 0 ; n < num-1 ; n++)  Serial.print(input[n]);
        Serial.println();
        input[num-1] = 0;
        num --;
      }
      else if (key == 'B') {                          // clear all
        for (; num > 0 ; num--) input[num] = 0;
        Serial.println(F("Clear all"));
      }
      else if (key == 'C') {                          // cancel
        Serial.println(F("Unlock Cancel"));
        return 0;
      }
      else {
        input[num] = key;
        if (num == (CODE_N-1)) {
          for (int n = 0 ; n < CODE_N ; n++) {
            if (input[n] != code[n]) break;           
            if (n == CODE_N-1) correct = true;
          }
          if (!correct) {                              // incorrect code
            for (; num > 0 ; num--) input[num] = 0;
            Serial.println(F("Incorrect password!"));
            Buzzer(1,5000);                                                              // 密碼輸入錯誤時，會發出1次長嗶聲 (Hint: Buzzer(a,b) a為嗶嗶聲之次數，b為每次聲音之間隔時間(單位為毫秒ms=0.001s))
            return 0;
          }
          if (correct) {                               // code correct
              Serial.println(F("Correct password!"));
              alert = 0;                               // close the alert function
              Buzzer(0);                               // close the buzzer
              Buzzer(3,100);
              break;
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
    if (n % 10 == 1) digitalWrite(greenPin,HIGH);   // green light on
    else digitalWrite(greenPin,LOW);                // green light off
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
    else digitalWrite(greenPin,LOW);               // green light off
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
  static int buzzer_state;
  if (number == -1) {
    digitalWrite(buzzerPin, LOW);  //Setting buzzer pin to LOW (buzzer on)
    buzzer_state = 1;
    return;
  }
  else if (number == 0) {
    digitalWrite(buzzerPin, HIGH);  //Setting buzzer pin to HIGH (buzzer off)
    buzzer_state = 0;
    return;
  }
  if (buzzer_state == 0)
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

int checkAlert(){
  // Door Trigger Sensor and Buzzer Alert
  if (TEST) {
    if (digitalRead(triggerPin_2) == LOW) {
      digitalWrite(redPin,HIGH);    // red light on
      if (alert) {
        Buzzer(1,500);
        Alert(DATA1,DATA2,"Door Open");  // trigger ifttt event
        Serial.println(F("Door Opened!"));
      }
      return 1;
    }
    else {
      digitalWrite(redPin,LOW);     // red light off
      return 0;
    }
  }
  else {
    if (digitalRead(triggerPin_2) == HIGH) {
      digitalWrite(redPin,HIGH);    // red light on
      if (alert) {
        Buzzer (-1);
        Alert(DATA1,DATA2,"Door Open");  // trigger ifttt event
        Serial.println(F("Door Opened!"));
      }
      return 1;
    }
    else {
      digitalWrite(redPin,LOW);     // red light off
      return 0;
    }
  }
}
