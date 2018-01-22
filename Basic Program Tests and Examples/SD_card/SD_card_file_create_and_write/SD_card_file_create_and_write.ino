#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("number.txt")) {                      // 
    Serial.println("file exists.");
    SD.remove("number.txt");                         //
    Serial.println("file have been removed.");
  } else {
    Serial.println("file doesn't exist.");
  }

  // open a new file and immediately close it:
  Serial.println("Creating file...");
  myFile = SD.open("number.txt", FILE_WRITE);          //
  myFile.close();

  // Check to see if the file exists:
  if (SD.exists("number.txt")) {                      //
    Serial.println("file exists.");
  } else {
    Serial.println("file doesn't exist.");
  }

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("number.txt", FILE_WRITE);            //

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to file...");
    myFile.println("001");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
  
  myFile = SD.open("number.txt");                      //
  if (myFile) {
    Serial.println("file context:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening file");
  }
}

void loop() {
  // nothing happens after setup finishes.
}
