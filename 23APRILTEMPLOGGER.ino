#include <dht.h>
#include <SPI.h>
#include <SD.h>
dht DHT;
File myLog;

//Set up.
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  // Initiate the SD Card.
  if (SD.begin(10))  {
    Serial.println("SD card initiated.");
    delay(2000);
  }  else {
    Serial.println("SD Card failed to initiate");
    while (1);
  }

  // Erase previous log file.
  if (SD.exists("mylog.txt")) {
    Serial.println("Log file detected.");
    delay(2000);
    //Serial.println("WARNING: SD.REMOVE IS ENABLED. LOG FILE WILL BE REMOVED.");
    //delay(5000);
    //SD.remove("mylog.txt");
    //Serial.println("Log file has been deleted.");
    //delay(2000);
  }

  // Create new log file.
  if (!SD.exists("mylog.txt")) {
    myLog = SD.open("mylog.txt", FILE_WRITE);
    myLog.println("System is writing to SD Card");
    Serial.println("New log file created.");
    delay(2000);
    myLog.close();
  }

  // Checks if system is writing to SD card.
  myLog = SD.open("mylog.txt");
  Serial.println("=====CONTENTS OF LOG FILE=====");
  while (myLog.available()) {
    Serial.write(myLog.read());

  }

  // End of set up.
  Serial.println("=====END OF LOG FILE=====");
  delay(5000);
  myLog.close();
}

// Loop.
void loop() {

  // Activates sensor.
  DHT.read11(A0);

  // Writes sensor data onto the SD card.
  myLog = SD.open("mylog.txt", FILE_WRITE);
  myLog.print("Temperature = ");
  myLog.println(DHT.temperature);
  myLog.print("Humidity = ");
  myLog.println(DHT.humidity);
  myLog.close();

  // Prints out sensor data to serial.
  Serial.println("");
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.print("  Humidity = ");
  Serial.println(DHT.humidity);
  delay(5000);
}

