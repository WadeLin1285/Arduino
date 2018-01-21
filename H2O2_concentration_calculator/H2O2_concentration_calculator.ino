/*************************************************
 * Project : H2O2 concentration calculator
 * Author  : Wade Lin
 * Detail  :   Ρ(gm/cc) = 1.0479 + 2.455 x (10^-3)W + 1.781 x( 10^-5)W^2 
 *                       - 6.76 x (10^-4 )T(C) - 2.4 x (10^-7)T(C) 2 
 *                       - 3.98 x (10^-6)WT(C)
 *          where W is weight percent H2O2.
 *          Enter value of temperature and weight percent
 * Devices : Arduino uno *1
 *          4x3 Keypad  *1
 *          16x2 LCD    *1 (with Matrix Orbital)
 *          9V Battery  *1
 *          Jumpers & Wires
 *************************************************/

#include <Keypad.h>
#include <Wire.h>
#define FLOATNUM 10000000

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
const int address = 40; // LCD address
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 8, 9, 10, 11};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {  12,  13 ˇㄇㄧㄛ,  7}; 

// Data Storeage
static int stage = 1,keyCounter = 0;
double temp = 0.00;
double weight = 0.00;
double result = 0.00;
static bool floatNum = false;

// LCD functions
double Calculation(double T, double W);
void CleanAll();
void NextLine();
void PrintResult();
void Enter(int num);
void LCDprint(int num);

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
  Wire.begin();
  // LCD setting
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);  // clean all
  Wire.write(254);
  Wire.write(74);  // underline on
  Wire.write(254);
  Wire.write(83);  // blinking on
  Wire.endTransmission();
  // Starting
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.write("Starting");
  Wire.endTransmission();
  delay(500);
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.write("Starting.");
  Wire.endTransmission();
  delay(400);
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.write("Starting..");
  Wire.endTransmission();
  delay(300);
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.write("Starting...");
  Wire.endTransmission();
  delay(200);
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.endTransmission();
  delay(100);
}

void loop()
{
  /*Serial.print("Temp:");
  Serial.print(temp);
  Serial.print("  Weight:");
  Serial.println(weight);*/
  
  if (stage == 1){
    Wire.beginTransmission(address);
    Wire.write("Temperature:");
    Wire.endTransmission();
    NextLine();
    stage = 2;
  }
  else if (stage == 3){
    Wire.beginTransmission(address);
    Wire.write("Weight Percent:");
    Wire.endTransmission();
    NextLine();
    stage = 4;
  }
  else if (stage == 5){
    Wire.beginTransmission(address);
    Wire.write("Result:");
    Wire.endTransmission();
    NextLine();
    PrintResult();
    stage = 6;
  }
  else ;

  // determine key pressed 
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    keyCounter++;
    if (key != '#' && keyCounter >= 17) Serial.println("exceed");
    else {
      // key pressed
      switch (key)
      {
        case '1':
          Serial.println("1");
          if (stage == 2 || stage == 4) LCDprint(1);
          Enter(1);
          break;
          
        case '2':
          Serial.println("2");
          if (stage == 2 || stage == 4) LCDprint(2);
          Enter(2);
          break;
          
        case '3':
          Serial.println("3");
          if (stage == 2 || stage == 4) LCDprint(3);
          Enter(3);
          break;
          
        case '4':
          Serial.println("4");
          if (stage == 2 || stage == 4) LCDprint(4);
          Enter(4);
          break;
          
        case '5':
          Serial.println("5");
          if (stage == 2 || stage == 4) LCDprint(5);
          Enter(5);
          break;
          
        case '6':
          Serial.println("6");
          if (stage == 2 || stage == 4) LCDprint(6);
          Enter(6);
          break;
          
        case '7':
          Serial.println("7");
          if (stage == 2 || stage == 4) LCDprint(7);
          Enter(7);
          break;
          
        case '8':
          Serial.println("8");
          if (stage == 2 || stage == 4) LCDprint(8);
          Enter(8);
          break;
          
        case '9':
          Serial.println("9");
          if (stage == 2 || stage == 4) LCDprint(9);
          Enter(9);
          break;
          
        case '*':
          if (floatNum) break;
          Serial.println("*");
          if (stage == 2 || stage == 4)
          {
            Wire.beginTransmission(address);
            Wire.write(".");
            Wire.endTransmission();
          }
          Enter(-1);
          break;
          
        case '0':
          Serial.println("0");
          if (stage == 2 || stage == 4) LCDprint(0);
          Enter(0);
          break;
          
        case '#':
          Serial.println("#");
          CleanAll();
          keyCounter = 0;
          if (stage == 2)     stage = 3;
          else if (stage == 4) stage = 5;
          else if (stage == 6) {
            stage = 1;
            temp = 0;
            weight = 0;
          }
          break;
          
        default:
          Serial.println(key);
      }
    }
  }
}

double Calculation(double T, double W){
  /* Ρ(gm/cc) = 1.0479 + 2.455 x (10^-3)W + 1.781 x( 10^-5)W^2 
  *                       - 6.76 x (10^-4 )T(C) - 2.4 x (10^-7)T(C) 2 
  *                       - 3.98 x (10^-6)WT(C) */
  double a = 0.00001781;
  double b = -0.00000389*T+0.002455;
  double c = 1.0479-0.000667*T-0.00000024*T*T-W ;
  double P = (-b+sqrt(b*b-4*a*c))/(2*a);
  Serial.print("a = ");
  Serial.println(a,10);
  Serial.print("b = ");
  Serial.println(b,10);
  Serial.print("c = ");
  Serial.println(c,10);
  Serial.print("P = ");
  Serial.println(P,10);
  return P;
}

void CleanAll(){
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(88);
  Wire.endTransmission();
  Enter(10);
}

void NextLine(){
  Wire.beginTransmission(address);
  Wire.write(254);
  Wire.write(71);
  Wire.write(1);
  Wire.write(2);
  Wire.endTransmission();
}

void PrintResult(){
  result = Calculation(temp,weight);
  long front = (long)result;
  long back = (result-(double)front)*FLOATNUM;
  long i = 1,j = 1;
  Serial.print("Temp:");
  Serial.println(temp);
  Serial.print("Weight:");
  Serial.println(weight);
  Serial.print("Result:");
  Serial.println(result,10);
  Serial.print("Front:");
  Serial.println(front);
  Serial.print("Back:");
  Serial.println(back);
  // LCD show front data
  if (front == 0)
  {
    Wire.beginTransmission(address);
    Wire.write("0");
    Wire.endTransmission();
  }
  else {
    while (front >= i) i *= 10;
    for (long n = i/10 ; n >= 1 ; n/=10)
    {
      long data = front / n;
      LCDprint(data);
      front -= data*n;
    }
  }
  // LCD show back data
  if (back == 0) return;
  else {
    Wire.beginTransmission(address);
    Wire.write(".");
    Wire.endTransmission();

    for (long n = FLOATNUM/10 ; n >= 1 ; n/=10)
    {
      long data = back / n;
      LCDprint(data);
      back -= data*n;
    }
  }
}

void Enter(int num){
  static int count = 1;
  if (num == -1){
    floatNum = true;
    return;
  }
  if (num == 10){
    floatNum = false;
    count = 1;
    return;
  }

  if (floatNum){
    if     (stage == 2) temp = temp + ((float)num)/(pow(10,count)); 
    else if (stage == 4) weight = weight + ((float)num)/(pow(10,count));
    count ++;
  }
  else{
    if     (stage == 2) temp = temp * 10 + num; 
    else if (stage == 4) weight = weight * 10 + num;
  }
}

void LCDprint(int num){
  switch(num)
  {
    case 1:
      Wire.beginTransmission(address);
      Wire.write("1");
      Wire.endTransmission();
      break;
    case 2:
      Wire.beginTransmission(address);
      Wire.write("2");
      Wire.endTransmission();
      break;
    case 3:
      Wire.beginTransmission(address);
      Wire.write("3");
      Wire.endTransmission();
      break;
    case 4:
      Wire.beginTransmission(address);
      Wire.write("4");
      Wire.endTransmission();
      break;
    case 5:
      Wire.beginTransmission(address);
      Wire.write("5");
      Wire.endTransmission();
      break;
    case 6:
      Wire.beginTransmission(address);
      Wire.write("6");
      Wire.endTransmission();
      break;
    case 7:
      Wire.beginTransmission(address);
      Wire.write("7");
      Wire.endTransmission();
      break;
    case 8:
      Wire.beginTransmission(address);
      Wire.write("8");
      Wire.endTransmission();
      break;
    case 9:
      Wire.beginTransmission(address);
      Wire.write("9");
      Wire.endTransmission();
      break;
    case 0:
      Wire.beginTransmission(address);
      Wire.write("0");
      Wire.endTransmission();
      break;
    default:
      break;
  }
}

