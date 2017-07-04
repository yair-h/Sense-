#include "Sense.h"
#include <Arduino.h>


Sense::Sense(char *apiName) {
  apiName_ = apiName;
}

Sense::~Sense() {}

int Sense::begin(uint8_t baudRate) {
  pinMode (debugRedLed,OUTPUT);pinMode (debugBlueLed,OUTPUT);
  Serial.begin(baudRate);
  while (!isConnected) {
    if (Serial.available() > 0)  ack = Serial.read();
    if (ack == '1') {
      Serial.flush();
      ack = NULL;
      int answer = sendWhoAmI();
      if (answer == 1) isConnected = true;
      if (answer == 0) return 0;
      if (answer == -1) return -1;
    }
  }
  return true;
}

int Sense::sendWhoAmI() {
  uint8_t counter = 0;
  while (counter <= repeats) {
    if (Serial.available() == 0) Serial.println(apiName_);
    if (Serial.available() > 0) ack = Serial.read();
    switch (ack) {
      case ('1'): // we've got OK msg from app.
        isIdentified = true;
        return 1;
        break;
      case ('2'): // we've got a unrecognizable hardware ack message.
        isIdentified = false;
        return -1;
        break;
      default:
        break;
    }
    delay(500);
    counter++;
  }
  return 0;
}

void Sense::error(uint8_t errorNum) {
  switch (errorNum) {
    case (2):
      while (true) {
        digitalWrite(debugRedLed, HIGH);
        delay(1000);
        digitalWrite(debugRedLed, LOW);
        delay(1000);
      }
      break;
    case (1):
      break;
  }
}

bool Sense::begin(){
  
}



