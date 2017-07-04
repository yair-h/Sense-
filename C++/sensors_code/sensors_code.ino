// **********************************************************************//
/* list of sensors
  temperature Sensor - SHT31 - https://www.sensirion.com/fileadmin/user_upload/customers/sensirion/Dokumente/2_Humidity_Sensors/Sensirion_Humidity_Sensors_SHT3x_Datasheet_digital.pdf
  humidity Sensor - SHT31
  uv Sensor - ML8511 - https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/ML8511_3-8-13.pdf
  proximity Sensor - VL6180X - http://www.st.com/content/ccc/resource/technical/document/datasheet/c4/11/28/86/e6/26/44/b3/DM00112632.pdf/files/DM00112632.pdf/jcr:content/translations/en.DM00112632.pdf
  barometric Sensor - BMP180 - https://cdn-shop.adafruit.com/datasheets/BST-BMP180-DS000-09.pdf
  heartRate Sensor -  MAX30102 https://datasheets.maximintegrated.com/en/ds/MAX30102.pdf
  alcohol Sensor -  MQ-3 https://www.sparkfun.com/datasheets/Sensors/MQ-3.pdf
  soil Moisture Sensor
  EC Sensor
  
*/
// **********************************************************************//
#include <Sense.h>

Sense sense("sense_s1"); // Here we define the name of this device.

void setup() {
  sense.begin(9600);
  if (!sense.isIdentified) sense.error(2); // this error tells that the app didn't recognize the device.
  delay(1000);
}

void loop() {
  if (!sense.sensorSelection()); sense.error(3);
}
