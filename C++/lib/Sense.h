#pragma once
#include <Arduino.h>
class Sense
{
  public:
    Sense(char *apiName);
    ~Sense();
    int begin(int baudRate);
    bool isConnected = false;
    bool isIdentified = false;
    int repeats = 120; // one minute to response by default
    void error(uint8_t errorNum); 
    int debugRedLed = 13 , debugBlueLed = 12;
  private:
    char *apiName_;
    byte ack;
    int sendWhoAmI();
};


