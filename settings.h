#pragma once

#include <Arduino.h>

// AM2315
static const uint8_t AM2315Data = A4;  // YELLOW
static const uint8_t AM2315Clock = A5; // WHITE

// DS18B20
static const uint8_t DS18B20Pin = A1;
static const uint8_t DS18B20Ground = A2;
static const uint8_t DS18B20Power = A3;
static const uint8_t DS18B20OneWireBus = 10;
static const uint8_t DS18B20TempPower = 8;
static const uint8_t DS18B20TempGround = 9;

// pH
static const uint8_t pHPin = A0;
