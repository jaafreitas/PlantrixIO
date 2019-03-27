#include <Arduino.h>

#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
#define Offset 20.40            //deviation compensate

unsigned long int avgValue;     //Store the average value of the sensor feedback

unsigned long previousMillisSensorpH = 0;
const long intervalSensorpH = 800;

void setupSensorpH() {
  Serial.print("pH done");
}

void loopSensorpH() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillisSensorpH >= intervalSensorpH) {
    previousMillisSensorpH = currentMillis;
    
    // buffer for read analog
    int buf[10];
  
    // Get 10 sample value from the sensor for smooth the value
    for (int i = 0; i < 10; i++) {
      buf[i] = analogRead(SensorPin);
      delay(10);
    }
    
    // sort the analog from small to large
    for (int i = 0; i < 9; i++) {
      for (int j = i + 1; j < 10; j++) {
        if (buf[i] > buf[j]) {
          int temp = buf[i];
          buf[i] = buf[j];
          buf[j] = temp;
        }
      }
    }
    
    avgValue = 0;
    //take the average value of 6 center sample
    for (int i = 2; i < 8; i++) {
      avgValue += buf[i];
    }
  
    //convert the analog into millivolt
    float phValue = (float)avgValue * 5.0 / 1024 / 6;
    
    // para calibrar comentar a linha abaixo e ler os valores de milivolts
    // cruzar com a leitura de ph, plottar a reta e usar a inclinação e o 
    // deslocamento da reta na equação abaixo. 
    // valor de offset é o deslocamento da reta, vai lá no início do código como variável
    
    //convert the millivolt into pH value
    phValue = -5.41 * phValue + Offset;
    Serial.print("pH: ");
    Serial.println(phValue, 2);
  }
}
