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
  loopSensorpH();
  loopSensorDS18B20();  
}
