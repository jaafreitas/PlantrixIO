#include <Adafruit_AM2315.h>

Adafruit_AM2315 sensorAM2315;

bool canReadSensorAM2315 = false;

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
  if (canReadSensorAM2315) {
    Serial.print("AM2315 Hum: "); Serial.println(sensorAM2315.readHumidity());
    Serial.print("AM2315 Temp: "); Serial.println(sensorAM2315.readTemperature());
  } else {
    Serial.println("AM2315 ignored");
  }
}
