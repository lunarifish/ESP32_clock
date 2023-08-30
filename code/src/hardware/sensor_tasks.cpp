
#include <Arduino.h>
#include "sensor_tasks.h"
#include "globals.h"


volatile double bmp280_temp(0.),
                bmp280_pressure(0.),
                bmp280_altitude(0.),
                dht11_temp(0.),
                dht11_humidity(0.),
                heat_index(0.);


void updateBMP280() {
    // must call this to wake sensor up and get new measurement data
    // it blocks until measurement is complete
    I2C_BUS_0_BUSY = true;
    if (bmp.takeForcedMeasurement()) {
        bmp280_temp = bmp.readTemperature();
        bmp280_pressure = bmp.readPressure();
        bmp280_altitude = bmp.readAltitude(1011.3);
    } else {
        Serial.println("BMP280: Forced measurement failed!");
    }
    I2C_BUS_0_BUSY = false;
}

void updateDHT11() {
    // TODO: sometimes this function will cause the system to crash
    //      maybe change a DHT11 library will solve this

    double t, h;
    h = dht11.readHumidity();
    t = dht11.readTemperature();
    if (!isnan(h) && !isnan(t)) {
        dht11_temp = t;
        dht11_humidity = h;
    }
}

void updateSensors() {
    updateBMP280();
    updateDHT11();
    heat_index = dht11.computeHeatIndex(bmp280_temp, dht11_humidity, true);
}


