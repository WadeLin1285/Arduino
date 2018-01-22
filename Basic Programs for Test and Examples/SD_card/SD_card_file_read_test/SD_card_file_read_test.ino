#include <SPI.h>
#include "SdFat.h"        // alternative library for <SD.h>

char school[10];
char number[5];
int nn;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  // setting SD card and defining machine data
  SdFat SD;
  File Machine_document;
  Serial.println(F("Setting SD card..."));
  if (!SD.begin(4)) Serial.println(F("initialization failed!"));
  else Serial.println(F("initialization done."));
  Machine_document = SD.open("machine.txt");
  if (Machine_document) {
    Serial.println(F("Reading Machine document file..."));
    // read the SD card information
    char line[1];
    while(Machine_document.read(line,sizeof(line))) {
      Serial.print(line[0]);
      if (line[0] == '*') {
        while(Machine_document.read(line,sizeof(line))) {
          if (line[0] == '*') break;
          Serial.print(line[0]);
        }
      }
      else if (line[0] == '-') {
        Machine_document.read(line,sizeof(line));
        Serial.print(line[0]);
        if (line[0] == 's') {// school name data
          while(Machine_document.read(line,sizeof(line))) {
            Serial.println(line[0]);
            if (line[0] == '-') break;
          }
          for (int n = 0; n < 2 ; n++) Machine_document.read(line,sizeof(line));
          nn = 0;
          while(Machine_document.read(line,sizeof(line))) {
            Serial.println(line[0]);
            
            if (line[0] == '-') break;
            school[nn] = line[0];
            nn++;
          }
        }
        else if (line[0] == 'n') {// machine number
          while(Machine_document.read(line,sizeof(line))) {
            Serial.print(line[0]);
            if (line[0] == '-') break;
          }
          for (int n = 0; n < 2 ; n++) Machine_document.read(line,sizeof(line));
          nn = 0;
          while(Machine_document.read(line,sizeof(line))) {
            Serial.print(line[0]);
            if (line[0] == '-') break;
            int n = 0;
            number[nn] = line[0];
            nn++;
          }
        }
      }
    }
    Machine_document.close(); // close the file
  } else {
    // if the file didn't open, print an error:
    Serial.println(F("error opening Machine_document.txt"));
  }
  Serial.println("\nEND");
  Serial.print("School: ");
  for (int n = 0; n < 10; n++) Serial.print(school[n]);
  Serial.println();
  Serial.print("Number: ");
  for (int n = 0; n < 5; n++)  Serial.print(number[n]);
  Serial.println();
}

void loop() {
  // nothing happens after setup
}
