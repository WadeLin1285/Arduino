#include <LiquidCrystal_I2C.h>
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  // initialize the LCD
  lcd.begin();


  

  // Turn on the blacklight and print a message.
  lcd.backlight();
lcd.noBacklight();
  lcd.print("Hello, world!");
}

void loop()
{
  // Do nothing here...
}
