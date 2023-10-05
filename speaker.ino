#include <SoftwareSerial.h>
#include <TTS.h>
#include <Wire.h>
#include <ArduinoJson.h>

SoftwareSerial bluetooth(2, 3);
TTS tts(6, 5);

String objectName = "";
String objectMaterial = "";

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  tts.init();
}

void loop() {
  if (bluetooth.available()) {
    String receivedData = bluetooth.readStringUntil('}');

    if (receivedData == "1") {
      tts.speak("hot and be careful");
    } 

    if (receivedData == "2") {
      tts.speak("warning! Very hot, be careful of burns");
    }
    if (isString(receivedData)){
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, receivedData);
      
      objectName = doc["name"].as<String>();
      objectMaterial = doc["material"].as<String>();
      
      tts.speak("This is a " + objectName + ", and" + objectMaterial);
      
      if (objectMaterial == "glass") {
        tts.speak("Be careful not to break");
      }
      if (objectMaterial == "stainless") {
        tts.speak("It's hot so be careful");
      }
      if (objectMaterial == "aluminum") {
        tts.speak("Be careful of sharp");
      }
    }
  }
}
