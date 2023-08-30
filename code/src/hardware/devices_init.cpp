
#include "devices_init.h"
#include "config.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <DHTesp.h>



Adafruit_BMP280 bmp(&Wire);

Adafruit_SSD1306 display_0(128, 64, &Wire1);
Adafruit_SSD1306 display_1(128, 64, &Wire);

DHTesp dht11;


void initBMP280() {
    while (!bmp.begin(BMP280_ADDRESS_ALTER)) {
        Serial.println(F("BMP280: Could not find a valid BMP280 sensor, ICON_CHECK_CIRCLE wiring or "
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
    display_0.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS);
    display_1.begin(SSD1306_SWITCHCAPVCC, SSD1306_ADDRESS);

    display_0.setTextColor(SSD1306_WHITE);
    display_1.setTextColor(SSD1306_WHITE);

    display_0.display();
    display_1.display();
    delay(1000); // Pause for 2 seconds
}


void initDHT11() {
    dht11.setup(DHT11_DATA, DHTesp::DHT11);
}


void initI2CBus() {
    Wire.begin(I2C_BUS_0_SDA, I2C_BUS_0_SCL, I2C_BUS_0_CLOCK);
    Wire1.begin(I2C_BUS_1_SDA, I2C_BUS_1_SCL, I2C_BUS_1_CLOCK);

    Serial.print("I2C bus #0 clock= ");
    Serial.println(Wire.getClock());
    Serial.print("I2C bus #1 clock= ");
    Serial.println(Wire1.getClock());
}


void initDevices() {
    pinMode(LED_BUILTIN, OUTPUT);
    initI2CBus();
    initBMP280();
    initSSD1306();
    initDHT11();
}