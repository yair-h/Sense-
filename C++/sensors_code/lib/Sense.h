#pragma once
#include <Arduino.h>
class Sense
{
public:
	Sense(char *apiName);
	~Sense();
	int begin(uint16_t baudRate);
	bool isConnected = false;
	bool isIdentified = false;
	int repeats = 120; // one minute to response by default
	void error(uint8_t errorNum);
	int debugRedLed = 3, debugBlueLed = 2;
	int sensorSelection();
	bool tempSensorbegin(uint16_t *rate);
	bool humiditySensorbegin(uint16_t *rate);
	bool uvSensorbegin(uint16_t *rate);
	bool proximitySensorbegin(uint16_t *rate);
	bool barometricSensorbegin(uint16_t *rate);
	bool heartRateSensorbegin(uint16_t *rate);
	bool alcoholSensorbegin(uint16_t *rate);
	bool soilMoistureSensorbegin(uint16_t *rate);
	bool ECSensorbegin(uint16_t *rate);

private:
	char *apiName_;
	byte ack;
	int sendWhoAmI();
	uint16_t  samplingRate;
	uint8_t sensorNum;
	String msg = "";
	bool newMsg = false;
	void blink(uint16_t delay,unsigned long *lastTime);
};


