
/***************************************************
  This is an example for the BMP085 Barometric Pressure & Temp Sensor

  Designed specifically to work with the Adafruit BMP085 Breakout
  ----> https://www.adafruit.com/products/391

  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Sense.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>


Sense::Sense(char *apiName) {
  apiName_ = apiName;
}

Sense::~Sense() {}

int Sense::begin(uint16_t baudRate) {
  unsigned long lastTime = millis();
  bool lastAct = true;
  pinMode(debugRedLed, OUTPUT); pinMode(debugBlueLed, OUTPUT);
  digitalWrite(debugRedLed, LOW); digitalWrite(debugBlueLed, HIGH);
  Serial.begin(baudRate);
  while (!isConnected) {
    if (millis() - lastTime >= 400) {
      if (!lastAct) {
        digitalWrite(debugBlueLed, HIGH);
        lastAct = true;
      }
      else {
        digitalWrite(debugBlueLed, LOW);
        lastAct = false;
      }
      lastTime = millis();
    }
    if (Serial.available() > 0)  ack = Serial.read();
    if (ack == '1') {
      Serial.flush();
      ack = NULL;
      int answer = sendWhoAmI();
      Serial.flush();
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
        digitalWrite(debugBlueLed, LOW);
        return 1;
        break;
      case ('2'): // we've got an unrecognizable hardware ack message.
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

int Sense::sensorSelection() {
  bool procces = true;
  Serial.flush();
  while (procces) {
    if (Serial.available() > 0) {
      msg = Serial.readStringUntil('\n');
      newMsg = true;
    }
    if ((newMsg) && (msg.length() > 4)) {
      msg.trim();
      sensorNum = (msg.substring(0, msg.indexOf("#"))).toInt();
      samplingRate = (msg.substring((msg.indexOf("#") + 1))).toInt();
      newMsg = false;
      msg = "";
      //Serial.println(String(sensorNum) + "*" + String(samplingRate)); //ack
      switch (sensorNum) {
        case (0):
          tempSensorbegin(&samplingRate);
          break;
        case (1):
          humiditySensorbegin(&samplingRate);
          break;
        case (2):
          uvSensorbegin(&samplingRate);
          break;
        case (3):
          proximitySensorbegin(&samplingRate);
          break;
        case (4):
          barometricSensorbegin(&samplingRate);
          break;
        case (5):
          heartRateSensorbegin(&samplingRate);
          break;
        case (6):
          alcoholSensorbegin(&samplingRate);
          break;
        case (7):
          soilMoistureSensorbegin(&samplingRate);
          break;
        case (8):
          ECSensorbegin(&samplingRate);
          break;
        default:
          return -1;
          break;
      }
    }
  }
}



bool Sense::tempSensorbegin(uint16_t *rate) {
  unsigned long startTime = millis();
  Adafruit_BMP085 bmp;
  bmp.begin();
  Serial.flush();
  while (!newMsg) {
    digitalWrite(debugBlueLed, HIGH);
    Serial.println(bmp.readTemperature(),1);
    digitalWrite(debugBlueLed, LOW);
    unsigned long endTime;
    endTime = *rate + millis();
    while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
  }
}
bool Sense::barometricSensorbegin(uint16_t*rate) {
  Adafruit_BMP085 bmp;
  bmp.begin();
  Serial.flush();
  while (!newMsg) {
    digitalWrite(debugBlueLed, HIGH);
    Serial.println(bmp.readAltitude((101500)-86),1);
    digitalWrite(debugBlueLed, LOW);
    unsigned long endTime;
    endTime = *rate + millis();
    while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
  }

}
bool Sense::humiditySensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}
bool Sense::uvSensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}
bool Sense::proximitySensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}

bool Sense::heartRateSensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}
bool Sense::alcoholSensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}
bool Sense::soilMoistureSensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}
bool Sense::ECSensorbegin(uint16_t*rate) {
  unsigned long endTime;
  endTime = *rate + millis();
  while (millis()<= endTime) if (Serial.available() > 0) sensorSelection();
}

void Sense::error(uint8_t errorNum) {
  switch (errorNum) {
    case (2):
      digitalWrite(debugBlueLed, LOW);
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


