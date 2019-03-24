#include "sensorAM2315.h"
#include "sensorpH.h"
#include "sensorDS18B20.h"

void setup() {
  Serial.begin(115200);
  Serial.println("*** Plantrix IO ***");

  setupSensorAM2315();
  setupSensorpH();
  setupSensorDS18B20();
}

void loop() {
  loopSensorAM2315();
  delay(1000);

  loopSensorpH();
  delay(800);

  loopSensorDS18B20();
  // Measurments at 5's Second intervals (Dont read Ec morre than once every 5 seconds).  
  delay(5000);  
}
