
#pragma once
#ifndef ESP32_CLOCK_CONFIG_H
#define ESP32_CLOCK_CONFIG_H

#include <cstdint>
#include <U8g2lib.h>


const uint32_t MONITOR_SPEED       = 115200;

const uint8_t I2C_BUS_0_SCL        = 26;
const uint8_t I2C_BUS_0_SDA        = 27;
const uint8_t I2C_BUS_1_SCL        = 0;
const uint8_t I2C_BUS_1_SDA        = 15;

const uint8_t DHT11_DATA           = 4;

const uint8_t BMP280_ADDRESS_ALTER = 0x76;

const uint8_t SSD1306_CS           = 26;
const uint8_t SSD1306_RST          = 4;
const uint8_t SSD1306_DC           = 12;
const uint8_t SSD1306_SCLK         = 16;
const uint8_t SSD1306_MOSI         = 25;

const uint8_t SSD1306_0_SCL        = 0;
const uint8_t SSD1306_0_SDA        = 0;

const uint8_t SSD1306_1_SCL        = 0;
const uint8_t SSD1306_1_SDA        = 0;

#endif