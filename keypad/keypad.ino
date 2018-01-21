#include <Keypad.h>

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 7, 8, 9,10};
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = {11,12,13}; 

// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting...");
}

void loop()
{
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
    Serial.println(key);
    /*
    switch (key)
    {
      case '1':
        Serial.println("1");
        break;
      case '2':
        Serial.println("2");
        break;
      case '3':
        Serial.println("3");
        break;
      case '4':
        Serial.println("4");
        break;
      case '5':
        Serial.println("5");
        break;
      case '6':
        Serial.println("6");
        break;
      case '7':
        Serial.println("7");
        break;
      case '8':
        Serial.println("8");
        break;
      case '9':
        Serial.println("9");
        break;
      case '*':
        Serial.println("*");
        break;
      case '0':
        Serial.println("0");
        break;
      case '#':
        Serial.println("#");
        break;
      default:
        Serial.println(key);
    }
    */
  }
}
