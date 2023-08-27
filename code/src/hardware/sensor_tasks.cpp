
#include <Arduino.h>
#include "sensor_tasks.h"
#include "globals.h"
#include "hardware/led_utils.h"



volatile double bmp280_temp(0.), bmp280_pressure(0.), bmp280_altitude(0.), dht11_temp(0.), dht11_humidity(0.);


void updateBMP280() {
    // must call this to wake sensor up and get new measurement data
    // it blocks until measurement is complete
    if (bmp.takeForcedMeasurement()) {
        bmp280_temp = bmp.readTemperature();
        bmp280_pressure = bmp.readPressure();
        bmp280_altitude = bmp.readAltitude(1011.3);
    } else {
        Serial.println("BMP280: Forced measurement failed!");
    }
}

void updateDHT11() {

}

void updateSensors(void *param) {
    while (true) {
        updateBMP280();
        updateDHT11();
        // LEDblink(1, 100);
        delay(100);
    }
}


