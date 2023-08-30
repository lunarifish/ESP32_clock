
#pragma once

#ifndef ESP32_CLOCK_CONFIG_H
#define ESP32_CLOCK_CONFIG_H

#include <cstdint>


const uint32_t MONITOR_SPEED             = 115200;

const uint16_t SENSOR_UPDATE_INTERVAL    = 300;

const uint8_t  I2C_BUS_0_SCL             = 26;
const uint8_t  I2C_BUS_0_SDA             = 27;
const uint32_t I2C_BUS_0_CLOCK           = 3400000;
const uint8_t  I2C_BUS_1_SCL             = 0;
const uint8_t  I2C_BUS_1_SDA             = 15;
const uint32_t I2C_BUS_1_CLOCK           = 3400000;

const uint8_t  DHT11_DATA                = 4;

const uint8_t  SSD1306_ADDRESS           = 0x3C;
const uint8_t  BMP280_ADDRESS_ALTER      = 0x76;

const uint8_t  RTC_CALIB_MAX_RETRYS      = 20;
const uint8_t  RTC_CALIB_RETRY_INTERVAL  = 1;

#endif