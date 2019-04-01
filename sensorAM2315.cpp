#include <Adafruit_AM2315.h>
#include "settings.h"

Adafruit_AM2315 sensorAM2315;

bool canReadSensorAM2315 = false;

unsigned long previousMillisSensorAM2315 = 0;
const long intervalSensorAM2315 = 1000;

void setupSensorAM2315() {
  Serial.print("AM2315 ");

  if (!sensorAM2315.begin()) {
    Serial.println(" fail.");
  } else {
    Serial.println(" done.");
    canReadSensorAM2315 = true;
  }
}

void loopSensorAM2315() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensorAM2315 >= intervalSensorAM2315) {
    previousMillisSensorAM2315 = currentMillis;

    if (canReadSensorAM2315) {
      Serial.print("AM2315 Hum: "); Serial.println(sensorAM2315.readHumidity());
      Serial.print("AM2315 Temp: "); Serial.println(sensorAM2315.readTemperature());
    } else {
      Serial.println("AM2315 ignored");
    }
  }
}
