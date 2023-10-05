#include <SoftwareSerial.h>
#include <RFID.h>
#include <SPI.h>
#include <Wire.h>

SoftwareSerial bluetooth(2, 3);
RFID rfid(10, 9);

int temperaturePin = A0;

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  rfid.init();
}

void loop() {
  int temperature = (((analogRead(temperaturePin) * 5) / 1024.0) - 0.5) x 100;

  if (temperature >= 45) {
    bluetooth.println("1");
    delay(2000);
  }

  if (temperature >= 70) {
    bluetooth.println("2");
    delay(2000);
  }  

  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      String tagData = "{";
      tagData += "\"name\":\"";
      tagData += rfid.serNumDec[0];
      tagData += "\",\"material\":\"";
      tagData += rfid.serNumDec[1];
      tagData += "\"}";
      
      bluetooth.println(tagData);
    }
    rfid.halt();
  }
}
