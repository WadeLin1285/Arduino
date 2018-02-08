#include <Keypad.h>
#include <SPI.h>
#include <Ethernet.h>

#define ROWS    4                                                                // 設定鍵盤排數
#define COLS    4                                                                // 設定鍵盤列數

/***************************** 以下數值可做更改 *********************************/
#define CODE          123456789   // 系統預設密碼 (Hint: 可自行改寫，但僅可為數字)
#define CODE_MAX      9           // 系統密碼最大長度 (Hint: 可自行改寫)
#define TEST          0           // 測試模式 (Hint:若為0則為正式使用；1為測試使用)
#define DATA1         "NCKU"      // 網路訊息通知之資料1
#define DATA2         "001"       // 網路訊息通知之資料2
#define SHUTDOWN_TIME 60          // 系統判斷睡眠的時間長度 (Hint:若系統在 SHUTDOWN_TIME 間，偵測到小於 SAMPLE_NUM 次數的電流變化數量，就會關閉電腦電源) (Hint:單位-秒)
#define RESTART_TIME  10          // 系統重新啟動電源的時間 (Hint:若系統關閉電腦電源後，經過 RESTART_TIME 後，會重新開啟電腦電源) (Hint:單位-秒)
#define SET_ON_MUTI   3           // 系統設定新開機時樣本數時，會記錄 SHUTDOWN_TIME * SET_ON_MUTI 時間內之樣本數，並予以平均
#define LOCK_DELAY    10          // 系統上鎖延遲時間 (Hint:單位-秒)
#define ALERT_DELAY   5           // 系統警報延遲時間 (Hint:單位-秒)
#define CURRENT_PLOT  true        // 顯示電流感測之數值 (Hint:顯示-true；不顯示-false)
int  LOWCURRENT  = 513;           // 
int  HIGHCURRENT = 515;
int  SAMPLE_NUM  =  20;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xFD };                             // 網路擴張版之 MAC 地址 (Hint:若系統出現無法連上 MAC 或 DHCP 訊息時，可能為網路線未連接好，或沒有網際網路連線)
char MakerIFTTT_Key[]   = "bJa2fXsJqd4GvtJBF-2agaj5wjoTpLTUJnB0x7S-Zyq";         // 此3行程式碼須和前端程式互相配合設定
char MakerIFTTT_Event[] = "Alert";                                               // 此3行程式碼須和前端程式互相配合設定
byte server[] = { 34 , 201 , 225 , 3};                      // 網路伺服器IP位置  // 此3行程式碼須和前端程式互相配合設定
/********************************************************************************/

const int redPin       = 0;       // Define red LED pin number 
const int greenPin     = 1;       // Define green LED pin number 
const int triggerPin_1 = 14;      // Define door trigger pin number
const int triggerPin_2 = 15;      // Define door trigger pin number
const int buzzerPin    = 16;      // Define buzzer pin number (A2)
const int currentPin   = 17;      // Define current sensor pin number (A3)
const int relayPin     = 18;      // Define relay control pin number (A4)

// Define Etherent
EthernetClient client;
IPAddress ip(192,168,2,105);                                              // 網路擴張版之 IP 地址 (Hint:此設定為備用之使用)

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
int  current;
int  count_num;
int  on_sample = 0,sleep_sample = 0;                                                 // the current data measured when computer is on 
int  code_length;
bool pc = true;                                                             // computer state : ON - true OFF - false
bool alert = false;                                                         // alert   state : ON - 1 OFF - 0
bool setON_status = false;                                                       // if the setON function is complete, set the status value to 1
bool setSLEEP_status = false;                                                    // if the setSLEEP function is complete, set the status value to 1
char code[CODE_MAX];        
long int  code_value = CODE;                                                 // 系統密碼 (預設密碼)
unsigned long int  count_t = 0, old_t = 0,  t = 0;                    // 時間與計時參數 (main函數)
unsigned long int count_tt = 0, old_tt = 0, tt = 0;                    // 時間與計時參數 (checkAlert函數)

// Define functions
int  unlock();
int  checkAlert();
void setON();
void setSLEEP();
void checkSET();
void setCODE();
void Buzzer(int number, int delay_time = 1000);                              
void Alert(char *school, char *number,char *event);
void GreenLED();
void RedLED();
char *append_str(char *here, char *s);
char *append_ul(char *here, unsigned long u);

void setup() {
  Serial.begin(9600);                                                          // (Hint:若不要在電腦中顯示程式碼說明，可註解掉此行)
  Serial.println(F("System Starting..."));
  pinMode(buzzerPin,     OUTPUT);         //Set buzzerPin as output
  pinMode(currentPin,    INPUT );         //Set current as input
  pinMode(redPin,        OUTPUT);         //Set buzzerPin as output
  pinMode(greenPin,      OUTPUT);         //Set buzzerPin as output
  pinMode(triggerPin_1,  INPUT );         //Set buzzerPin as input
  pinMode(triggerPin_2,  INPUT );         //Set buzzerPin as input
  pinMode(relayPin,      OUTPUT);         //Set buzzerPin as output
  digitalWrite(buzzerPin,HIGH  );         // Buzzer close
  digitalWrite(relayPin, LOW  );          // Commen close (通路)
  digitalWrite(greenPin, LOW   );         // green light off
  digitalWrite(redPin,   HIGH  );         // red light on
  delay(500);
  
  // 設定輸入鍵盤
  Serial.println(F("Setting code number..."));
  for (long int c = code_value ; c > 9 ; c /= 10) code_length ++;
  code_length ++;
  for (int n = code_length ; n > 0 ; n--) {
    code[n-1] = code_value % 10 + 48;
    if (n == 1) code_value = 0;
    else code_value /= 10;
  }
  Serial.print(F("Code length:"));
  Serial.println(code_length);
  Serial.print(F("Code : "));
  for (int n = 0 ; n < code_length ; n++)  Serial.print(code[n]);
  Serial.println();
  delay(500);

  // 設定網路模組
  Serial.println(F("Setting ethernet shield and connecting to server..."));
  if (Ethernet.begin(mac) == 0) Serial.println(F("Failed to configure Ethernet using DHCP"));
  else Serial.println(F("Connect to Etherent shield with MAC address"));
  delay(500);
  Serial.println(F("Connecting to server..."));
  if (client.connect(server,80)) Serial.println(F("connected"));
  else Serial.println(F("connection failed"));
  delay(500);
  
  // 初始化參數
  pc = true;           
  alert = false; 

  // 系統啟動完成訊息傳輸
  Alert(DATA1,DATA2,"Ethernet setup confirmed!");
  Buzzer(2,100);                                                           // 系統設定完成時，會發出2次嗶嗶聲 (Hint: Buzzer(a,b) a為嗶嗶聲之次數，b為每次聲音之間隔時間(單位為毫秒ms=0.001s))
  GreenLED();
  Serial.println(F("\nAll setup complete!\n"));
  Alert(DATA1,DATA2,"All setup complete");
}

void loop() {
  current = analogRead(currentPin);                                         // 偵測電腦電流
  /*************************** 監控視窗輸出數值 ****************************/
  if (pc) Serial.print(F("[PC ON ]  "));
  else    Serial.print(F("[PC OFF]  "));
  // 顯示電流數值
  if (CURRENT_PLOT) {
    Serial.print(F("Current: "));
    Serial.print(current);
    Serial.print(F(" "));
  }
  /***************************  偵測警報觸發器 ****************************/
  checkAlert();
  /*************************** 電腦電流控制系統 ****************************/
  if (pc) {                                                          //電腦醒著之動作
    t = millis();                                                           // 設定時間
    if (count_t == 0 && old_t == 0) old_t = t;                              // 初始化(舊)時間參數
    count_t = count_t + (t - old_t);                                        // 計時
    old_t = t;                                                              
    if (count_t/1000 >= SHUTDOWN_TIME) {                                    // 開始判斷是否達到睡眠標準
      if (count_num < SAMPLE_NUM) {                                       // 若計算點發生次數小於設定值，則關閉電腦電源
        //digitalWrite(relayPin,HIGH);                                     // 繼電器斷路
        Serial.print(F("PC Power Shutdown..."));                                // 電腦關閉訊息
        Alert(DATA1,DATA2,"Sleep Mode Confirmed...System Power Shutdown");
        pc = false;                                                     // 設定電腦狀態至false(關閉)
      }
      count_t = 0;
      old_t = 0;
    }
    else 
      if (current < HIGHCURRENT && current > LOWCURRENT) count_num++;         // 計算計算點發生次數
  }
  else {
    t = millis();                                                                         // 設定時間
    if (count_t == 0 && old_t == 0) old_t = t;                              // 初始化(舊)時間參數
    count_t = count_t + (t - old_t);                                        // 計時
    old_t = t;
    if (count_t >= RESTART_TIME) {
      // digitalWrite(relayPin,LOW);                                       // 繼電器通路
      Serial.print(F("Re-connect PC Power..."));                            // 電腦重新連接電源訊息 
      Alert(DATA1,DATA2,"Re-connect PC Power");     
      
      if (count_t/1000 >= SHUTDOWN_TIME) {                                    // 開始判斷是否達到啟動標準
        if (count_num > SAMPLE_NUM) {                                       // 若計算點發生次數大於設定值，確認電腦電源已開啟
          Serial.println(F("PC Power On..."));                                // 電腦關閉訊息
          Alert(DATA1,DATA2,"Operate Mode Confirmed...PC Power is On");
          pc = true;                                                     // 設定電腦狀態至false(關閉)
        }
        count_t = 0;
        old_t = 0;
      }
      else 
        if (current < HIGHCURRENT && current > LOWCURRENT) count_num++;         // 計算計算點發生次數
    }
  }
  /*************************** 讀取輸入鍵盤資料 ****************************/
  char key = Codepad.getKey();
  if (key == 'A') {                                                         // 點擊A按鈕，進入鎖定模式
    Serial.print(F("Alert System operating..."));                             // 系統上鎖訊息
    Buzzer(1,50);
    delay(LOCK_DELAY*1000);                                                   // 延遲LOCK_TIME啟動
    alert = true;                                                           // 啟動警報系統                                                         
    Buzzer(2,100);
    Serial.print(F("Alert System operated..."));                                // 系統上鎖訊息
    Alert(DATA1,DATA2,"Alert System operated");
  }
  if (key == 'B') {                                                         // 點擊B按鈕，進入解鎖模式 (Hint:若在解鎖時，觸發警鈴，將會回到鎖定模式)
    Serial.print(F("Unlocking the alert system..."));                          // 系統解鎖訊息
    Buzzer(1,50);
    Alert(DATA1,DATA2,"Unlocking the alert system");                            // 系統解鎖訊息
    unlock();                                                               // 進入解鎖程序
  }
  if (key == 'C') {                                                         // 點擊C按鈕，進入設定電腦開機時之電流 (Hint:必須在電腦開機時使用)
    Serial.print(F("Computer awake current status setting start..."));
    Buzzer(1,50);
    setON();                                                                // 設定開機時系統偵測之標準數值
  }
  if (key == 'D') {                                                         // 點擊D按鈕，進入設定電腦睡眠時之電流 (Hint:必須在電腦睡眠時使用)
    Serial.print(F("Computer sleep current status setting start..."));
    Buzzer(1,50);
    setSLEEP();                                                             // 設定睡眠時系統偵測之標準數值
  }
  if (key == '*') {                                                         // 點擊*按鈕，進入設定密碼程序
    Serial.print(F("Setting new code..."));
    Alert(DATA1,DATA2,"Setting new code");
    Buzzer(1,50);
    setCODE();                                                              // 設定新密碼
  }
}

/*  Function Definition  */
int checkAlert(){
  static bool alertON = false;
  tt = millis();
  
  // Alert delay caclulate
  if (alertON) {
    if (old_tt == 0) old_tt = tt;
    count_tt = count_tt + (tt - old_t);
    old_t = tt;
    if (count_tt >= (ALERT_DELAY*1000)) {
      if (TEST) Buzzer(1,500);
      else Buzzer(-1);
      alertON = false;
      count_tt = 0;
      old_tt = 0;
      Serial.println(F("\nWARNING: Door Opened!\n"));
      Alert(DATA1,DATA2,"WARNING: Door Open");  // trigger ifttt event
    }
  }
  
  // Door Trigger Sensor and Buzzer Alert
  if (alert == 0) {
    Buzzer(0);
    return 0;
  }
  if (TEST) {
    if (digitalRead(triggerPin_1) == LOW) {
      Serial.print(F("Trigger 1 Triggered"));
      Alert(DATA1,DATA2,"WARNING: Trigger 1 Triggered");  // trigger ifttt event
      digitalWrite(redPin,HIGH);    // red light on
      alertON = true;
      return 1;
    }
    else if (digitalRead(triggerPin_2) == LOW) {
      Serial.print(F("Trigger 2 Triggered"));
      Alert(DATA1,DATA2,"WARNING: Trigger 2 Triggered");  // trigger ifttt event
      digitalWrite(redPin,HIGH);    // red light on
      alertON = true;
      return 1;
    }
    else {
      digitalWrite(redPin,LOW);     // red light off
      return 0;
    }
  }
  else {
    if (digitalRead(triggerPin_1) == HIGH) {
      Serial.print(F("Trigger 1 Triggered"));
      Alert(DATA1,DATA2,"WARNING: Trigger 1 Triggered");  // trigger ifttt event
      digitalWrite(redPin,HIGH);    // red light on
      alertON = true;
      return 1;
    }
    else if (digitalRead(triggerPin_2) == HIGH) {
      Serial.print(F("Trigger 2 Triggered"));
      Alert(DATA1,DATA2,"WARNING: Trigger 2 Triggered");  // trigger ifttt event
      digitalWrite(redPin,HIGH);    // red light on
      alertON = true;
      return 1;
    }
    else {
      digitalWrite(redPin,LOW);     // red light off
      return 0;
    }
  }
}

// unlock the alert system
int unlock() {
  int  num = 0;
  char input[CODE_MAX];
  bool correct = false;

  if (alert == false) return 0;
  
  while(1) {                                                            // 讀取鍵盤輸入
    checkAlert();                                                       // 依然偵測警報
    char key = Codepad.getKey();
    if (key) {
      Buzzer(1,50);
      Serial.print(F("Key inserted : "));
      Serial.print(key);
      if (key == 'A') {                               // back
        Serial.print(F(" [Back] "));
        Serial.print(F("Inserted Code : "));
        if (num > 0) {
          for (int n = 0 ; n < num-1 ; n++)  Serial.print(input[n]);
          input[num-1] = 0;
          num --;
        }
      }
      else if (key == 'B') {                          // clear all
        for (; num > 0 ; num--) input[num] = 0;
        Serial.print(F(" [Clear all] "));
      }
      else if (key == 'C') {                          // cancel
        Serial.print(F(" [Unlock Cancel] "));
        return 0;
      }
      else {
        input[num] = key;
        if (num == (code_length-1)) break;
        else num ++;
      }
    }
    Serial.println();
  }
  for (int n = 0 ; n < code_length ; n++) {
    if (input[n] != code[n]) break;           
    if (n == code_length-1) correct = true;
  }
  if (!correct) {                              // incorrect code
    for (; num > 0 ; num--) input[num] = 0;
    Serial.println(F("\nWARNING: Incorrect password!\n"));
    Alert(DATA1,DATA2,"WARNING: Incorrect password!(Unlocking)");
    Buzzer(1,5000);                                                              // 密碼輸入錯誤時，會發出1次長嗶聲 (Hint: Buzzer(a,b) a為嗶嗶聲之次數，b為每次聲音之間隔時間(單位為毫秒ms=0.001s))
    return 0;
  }
  if (correct) {                               // code correct
      Serial.println(F("\nCorrect password!...System Unlock\n"));
      Alert(DATA1,DATA2,"Correct password...System Unlock)");
      alert = 0;                               // close the alert function
      Buzzer(0);                               // close the buzzer
      Buzzer(3,100);
  }
  
}

// set the current when computer awake
void setON() {
  old_t = 0;
  count_t = 0;
  count_num = 0;
  // 計算電腦開啟時之樣本數量
  while(1) {
    checkAlert();                                                         // 持續監控警報
    t = millis();                                                           // 設定時間
    if (count_t == 0 && old_t == 0) old_t = t;                              // 初始化(舊)時間參數
    count_t = count_t + (t - old_t);                                        // 計時
    old_t = t;                                                              
    if (count_t/1000 >= SHUTDOWN_TIME*SET_ON_MUTI) break;                                    // 開始判斷是否達到睡眠標準
    else 
      if (current < HIGHCURRENT && current > LOWCURRENT) count_num++;         // 計算計算點發生次數
    // 顯示訊號
    if (count_t%1000 > 500) digitalWrite(greenPin,HIGH);                    // 綠色指示燈開啟
    else digitalWrite(greenPin,LOW);                                      // 綠色指示燈關閉
  }
  digitalWrite(greenPin,HIGH);                    // 綠色指示燈開啟
  on_sample = count_num/SET_ON_MUTI;
  setON_status = true; // status update
  Buzzer(2,100);
  Serial.print(F("Computer awake status is updated! New sample number of PC on is "));
  Serial.println(on_sample);
  checkSET();
}

// set the current when computer sleep
void setSLEEP() {
  old_t = 0;
  count_t = 0;
  count_num = 0;
  // 計算電腦開啟時之樣本數量
  while(1) {
    checkAlert();                                                         // 持續監控警報
    t = millis();                                                           // 設定時間
    if (count_t == 0 && old_t == 0) old_t = t;                              // 初始化(舊)時間參數
    count_t = count_t + (t - old_t);                                        // 計時
    old_t = t;                                                              
    if (count_t/1000 >= SHUTDOWN_TIME*SET_ON_MUTI) break;                                    // 開始判斷是否達到睡眠標準
    else 
      if (current < HIGHCURRENT && current > LOWCURRENT) count_num++;         // 計算計算點發生次數
    // 顯示訊號
    if (count_t%1000 > 500) digitalWrite(greenPin,HIGH);                    // 綠色指示燈開啟
    else digitalWrite(greenPin,LOW);                                      // 綠色指示燈關閉
  }
  digitalWrite(greenPin,HIGH);                    // 綠色指示燈開啟
  sleep_sample = count_num/SET_ON_MUTI;
  setSLEEP_status = true; // status update
  Buzzer(2,100);
  Serial.print(F("Computer sleep status is updated! New sample number of PC sleep is "));
  Serial.println(sleep_sample);
  checkSET();
}

void checkSET() {
  if (setON_status && setSLEEP_status) {                                    // 判斷是否完成開機及睡眠之數據更新
    SAMPLE_NUM = (on_sample + sleep_sample)/2;                              // 更新參數
    setON_status = false;
    setSLEEP_status = false;
    Buzzer(1,300);                                                        // 傳遞訊息
    Buzzer(2,100);
    Serial.print(F("Sample Value Change : "));
    Serial.print(SAMPLE_NUM);
    Alert(DATA1,DATA2,"Setting new sample number value");
  }
  old_t = 0;                                                              // 初始化參數
  count_t = 0;
  count_num = 0;
}

void setCODE() {
  int  num = 0;
  char input[CODE_MAX];
  bool correct = false;
  
  // check the code
  Serial.print(F("Insert the old code : "));
  while(1) {
    checkAlert();                                     // still check the trigger
    char key = Codepad.getKey();
    if (key) {
      if (key == '*' || key == '#' || key == 'D') {
        Buzzer(2,50);
        Serial.print(F("Key inserted error: "));
        Serial.print(key);
        continue;
      }
      Buzzer(1,50);
      Serial.print(F("Key inserted : "));
      Serial.print(key);
      if (key == 'A') {                               // back
        Serial.print(F(" [Back] "));
        Serial.print(F("Inserted Code : "));
        if (num > 0) {
          for (int n = 0 ; n < num-1 ; n++)  Serial.print(input[n]);
          input[num-1] = 0;
          num --;
        }
      }
      else if (key == 'B') {                          // clear all
        for (; num > 0 ; num--) input[num] = 0;
        Serial.print(F(" [Clear all] "));
      }
      else if (key == 'C') {                          // cancel
        Serial.print(F(" [Set Code Cancel] "));
        return 0;
      }
      else {
        input[num] = key;
        if (num == (code_length-1)) break;
        num ++;
      }
    }
    Serial.println();
  }
  for (int n = 0 ; n < code_length ; n++) {
    if (input[n] != code[n]) break;           
    if (n == code_length-1) correct = true;
  }
  if (!correct) {                                      // incorrect code
    for (; num > 0 ; num--) input[num] = 0;
    Serial.println(F("\nWARNING: Incorrect password!\n"));
    Alert(DATA1,DATA2,"WARNING: Incorrect password!(Unlocking)");
    Buzzer(1,5000);                                                              // 密碼輸入錯誤時，會發出1次長嗶聲 (Hint: Buzzer(a,b) a為嗶嗶聲之次數，b為每次聲音之間隔時間(單位為毫秒ms=0.001s))
    return 0;
  }
  if (correct) {                                       // code correct
      Serial.println(F("\nCorrect password!...Setting new code:\n"));
      Buzzer(3,100);
  }
  
  // Read the inserted code
  Serial.print(F("Insert the new code : "));
  num = 0;
  while(1) {
    if (checkAlert()) break;                            // still check the trigger
    if (num >= CODE_MAX) {
      Serial.println(F("Code Setting Finish(MAX Length)"));
      code_length = num;
      break;
    }
    char key = Codepad.getKey();
    if (key) {
      if (key == '*' || key == 'D') {
        Buzzer(2,50);
        Serial.print(F("Key inserted error: "));
        Serial.print(key);
        continue;
      }
      Buzzer(1,50);
      Serial.print(F("Key inserted : "));
      Serial.print(key);
      if (key == 'A') {                               // back
        Serial.print(F(" [Back] "));
        Serial.print(F("Inserted Code : "));
        if (num > 0) {
          for (int n = 0 ; n < num-1 ; n++)  Serial.print(input[n]);
          input[num-1] = 0;
          num --;
        }
      }
      else if (key == 'B') {                          // clear all
        for (; num > 0 ; num--) input[num] = 0;
        Serial.print(F(" [Clear all] "));
      }
      else if (key == 'C') {                          // cancel
        Serial.print(F(" [Set Code Cancel]"));
        return 0;
      }
      else if (key == '#') {                          // cancel
        Serial.print(F(" [Code Setting Finish]"));
        code_length = num;
        break;
      }
      else {
        input[num] = key;
        Serial.print(input[num]);
        num ++;
      }
    }
    Serial.println();
  }
  Serial.print(F("New code:"));
  for (int n = 0 ; n < code_length ; n++) {
    code[n] = input[n];
    Serial.print(code[n]);
  }
  Serial.print(F(" ; "));
  Serial.print(F("New code length:"));
  Serial.println(code_length);
  Buzzer(3,100);
}

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
        if (n < (number-1)) delay(delay_time);
    }
}

void GreenLED(){
  digitalWrite(greenPin,HIGH);      
  digitalWrite(redPin  ,LOW );         
}
void RedLED(){
  digitalWrite(greenPin,LOW );             
  digitalWrite(redPin  ,HIGH);                 
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
