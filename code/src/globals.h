#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <U8g2lib.h>
#include <Tween.h>
#include "display/ui_framework/components_manager.hpp"


extern TwoWire I2C_BUS_0;
extern TwoWire I2C_BUS_1;
extern Adafruit_BMP280 bmp;
extern U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI display_0;
extern volatile double bmp280_temp, bmp280_pressure, bmp280_altitude, dht11_temp, dht11_humidity;

extern uint32_t timestamp_calib_offset;
extern bool rtc_calibrated;

extern ComponentsManager<U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI*> *components_manager;


#endif