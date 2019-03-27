#include <Arduino.h>

int incomingByte;

void loopSerial() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == 'A') {
      digitalWrite(4, LOW);
    }

    if (incomingByte == 'B') {
      digitalWrite(4, HIGH);
    }

    if (incomingByte == 'C') {
      digitalWrite(13, LOW);
    }

    if (incomingByte == 'D') {
      digitalWrite(13, HIGH);
    }
  }
}
