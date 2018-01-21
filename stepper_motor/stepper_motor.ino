/*     Simple Stepper Motor Control Exaple Code
 *      
 * 
 *  
 */
// defines pins numbers
const int stepPin = 53; 
const int dirPin  = 51;
const int onoff  = 52; 
const int led    = 23;
int start;
 
void setup() {
  Serial.begin(9600);
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(onoff,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}
void loop() {
  digitalWrite(dirPin,LOW); // Enables the motor to move in a particular direction
  start = digitalRead(onoff);
  
  //if (start == 0) {
      /* 2. 開#1繼電器(TTL訊號)10秒  *
    Serial.println("Mode A --- Step 2");
    digitalWrite(led,HIGH);
    delay(6000);                                        // 6 sec
      /* 3.#1繼電器開啟時序第6秒，轉動#1步進馬達4圈(與第1步驟轉向相反) *
    Serial.println("Mode A --- Step 3");
    digitalWrite(dirPin,HIGH);                    // inverse SM#1 direction
    unsigned long time_record = millis();
    unsigned long time_record_2 = millis();
    for (int i = 0,j = 0; i < 4*200; i++) {           // four cycle
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000);
      time_record_2 = millis();
    }
    delay(4000-(time_record_2-time_record));
    digitalWrite(led,LOW);
  }
  */
  
  if (start == 0) {
    digitalWrite(led,HIGH);
    digitalWrite(dirPin,LOW);
    for (int x = 0; x < 200 ; x ++ )
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000); 
    }
    digitalWrite(led,LOW);
    digitalWrite(dirPin,HIGH);
    for (int x = 0; x < 200 ; x ++ )
    {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(2000);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(2000); 
    }
  }
  if (start == 1) {
    digitalWrite(led,LOW);
    digitalWrite(stepPin,LOW); 
  }
}
