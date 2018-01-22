const int pin_A  = 67;
const int pin_B  = 66;
const int pin_C  = 65;
const int pin_D  = 62;
const int pin_E  = 63;
const int pin_F  = 68;
const int pin_G  = 69;
const int pin_DP = 64;

void number(char n);

void setup() {              
  pinMode(pin_A, OUTPUT); 
  pinMode(pin_B, OUTPUT);
  pinMode(pin_C, OUTPUT);
  pinMode(pin_D, OUTPUT);
  pinMode(pin_E, OUTPUT);
  pinMode(pin_F, OUTPUT);
  pinMode(pin_G, OUTPUT);
  pinMode(pin_DP, OUTPUT);
  digitalWrite(pin_DP, HIGH);  // 關閉小數點
}

void loop() {
  for (char i = '0';i <= '9';i++) {
    number(i);
    delay(500);
  }
}

void number(char n){
  switch (n) {
    case '1':
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, HIGH);
      break;
    case '2':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, HIGH);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '3':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '4':
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '5':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '6':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '7':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, HIGH);
      break;
    case '8':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '9':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case '0':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, HIGH);
      break;
    case '.':
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, HIGH);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, LOW);
      break;
    case '-':
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, HIGH);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 'E':
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, HIGH);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
  }
}

