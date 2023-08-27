
#include "devices_init.h"
#include "config.h"
#include <Adafruit_BMP280.h>
#include <DHT.h>



TwoWire I2C_BUS_0(0);
TwoWire I2C_BUS_1(1);
Adafruit_BMP280 bmp(&I2C_BUS_1);
// DHT dht11(DHT11_DATA, DHT11);
// U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2_SW(U8G2_R0, SSD1306_SCLK, SSD1306_MOSI, SSD1306_CS, SSD1306_DC, SSD1306_RST);
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI display_0(U8G2_R0, SSD1306_CS, SSD1306_DC, SSD1306_RST);


void initBMP280() {
    while (!bmp.begin(BMP280_ADDRESS_ALTER)) {
        Serial.println(F("BMP280: Could not find a valid BMP280 sensor, check_circle wiring or "
                         "try a different address!"));
        delay(1000);
    }

    /* Default settings from datasheet. */
    bmp.setSampling(Adafruit_BMP280::MODE_FORCED,     /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}


void initSSD1306() {
    display_0.begin();
    display_0.enableUTF8Print();
    display_0.setFont(u8g2_font_10x20_tf);
    display_0.setFontDirection(0);
    display_0.clear();
}


void initI2CBus() {
    I2C_BUS_0.setPins(I2C_BUS_0_SDA, I2C_BUS_0_SCL);
    I2C_BUS_0.begin();
    I2C_BUS_1.setPins(I2C_BUS_1_SDA, I2C_BUS_1_SCL);
    I2C_BUS_1.begin();
}


void initDevices() {
    pinMode(LED_BUILTIN, OUTPUT);
    initBMP280();
    initSSD1306();
}