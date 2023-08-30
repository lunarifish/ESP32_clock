#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Tween.h>
#include "display/ui_framework/components_manager.hpp"
#include "network/wifi_manager.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHTesp.h>


typedef Adafruit_SSD1306* display;

extern bool timer_mode;

extern Adafruit_BMP280 bmp;
extern Adafruit_SSD1306 display_0;
extern Adafruit_SSD1306 display_1;

extern DHTesp dht11;

extern volatile double bmp280_temp,
                       bmp280_pressure,
                       bmp280_altitude,
                       dht11_temp,
                       dht11_humidity,
                       heat_index;
extern ComfortState dht11_comfort_state;

extern uint32_t timestamp_calib_offset;
extern bool rtc_calibrated;

extern ComponentsManager<display> *components_manager;

extern bool I2C_BUS_0_BUSY;
extern bool I2C_BUS_1_BUSY;

extern WiFiManager wifi_manager;

#endif