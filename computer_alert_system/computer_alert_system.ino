#define LOWCURRENT 495
#define HIGHCURRENT 525

const int buzzerPin = 2;   // Define buzzer pin number 
const int currentPin = A5; // Define current sensor pin number 
const int redPin = 6;     // Define red LED pin number 
const int greenPin = 5;   // Define green LED pin number 
const int triggerPin = 4; // Define door trigger pin number 
const int relayPin = 3;   // Define relay control pin number 
int current;
int computer = 1;        // computer state : ON - 1 OFF - 0
unsigned long int count = 0; 

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);  //Set buzzerPin as output
  pinMode(currentPin, INPUT);  //Set current as input
  pinMode(redPin, OUTPUT);     //Set buzzerPin as output
  pinMode(greenPin, OUTPUT);   //Set buzzerPin as output
  pinMode(triggerPin, INPUT);  //Set buzzerPin as input
  pinMode(relayPin, OUTPUT);   //Set buzzerPin as output
  digitalWrite(buzzerPin,HIGH); // Buzzer close
  digitalWrite(relayPin,HIGH);  // AC current close (通路)
}

void loop() {
  
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
  }

  if (digitalRead(triggerPin) == HIGH){ // close
    digitalWrite(redPin,HIGH);
    digitalWrite(greenPin,LOW);
    digitalWrite(buzzerPin,HIGH);      //Setting buzzer pin to high (buzzer close)
  }
  if (digitalRead(triggerPin) == LOW){ // open
    digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH);
    digitalWrite(buzzerPin,LOW);      //Setting buzzer pin to low (buzzer open)
  }
}

