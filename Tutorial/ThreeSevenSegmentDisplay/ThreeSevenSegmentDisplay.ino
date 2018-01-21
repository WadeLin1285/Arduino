const int pin_1  = 24;
const int pin_2  = 26;
const int pin_3  = 28;
const int pin_A  = 30;
const int pin_B  = 32;
const int pin_C  = 34;
const int pin_D  = 36;
const int pin_E  = 38;
const int pin_F  = 40;
const int pin_G  = 42;
const int pin_DP = 44;

void setNum(int n);
void number(char n);

void setup() {
  pinMode(pin_1, OUTPUT); 
  pinMode(pin_2, OUTPUT); 
  pinMode(pin_3, OUTPUT); 
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
  for (int i = 0;i < 999;i++) {
    setNum(i);
  }
}

void setNum(int n){
  // Find values of each bit
  int n1,n2,n3;
  n3 = n / 100;
  n %= 100;
  n2 = n / 10;
  n %= 10;
  n1 = n;
  // Set the number display
  digitalWrite(pin_1, HIGH);
  digitalWrite(pin_2, LOW);
  digitalWrite(pin_3, LOW);
  number(n1);
  delay(5);
  digitalWrite(pin_1, LOW);
  digitalWrite(pin_2, HIGH);
  digitalWrite(pin_3, LOW);
  number(n2);
  delay(5);
  digitalWrite(pin_1, LOW);
  digitalWrite(pin_2, LOW);
  digitalWrite(pin_3, HIGH);
  number(n3);
  delay(5);
}

void number(char n){
  switch (n) {
    case 1:
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, HIGH);
      break;
    case 2:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, HIGH);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 3:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, HIGH);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 4:
      digitalWrite(pin_A, HIGH);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 5:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 6:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, HIGH);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 7:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, HIGH);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, HIGH);
      break;
    case 8:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 9:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, HIGH);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, LOW);
      digitalWrite(pin_DP, HIGH);
      break;
    case 0:
      digitalWrite(pin_A, LOW);
      digitalWrite(pin_B, LOW);
      digitalWrite(pin_C, LOW);
      digitalWrite(pin_D, LOW);
      digitalWrite(pin_E, LOW);
      digitalWrite(pin_F, LOW);
      digitalWrite(pin_G, HIGH);
      digitalWrite(pin_DP, HIGH);
      break;
  }
}
