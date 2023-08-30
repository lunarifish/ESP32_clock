
#include <Arduino.h>
#include <DHTesp.h>
#include "sensor_tasks.h"
#include "globals.h"


volatile double bmp280_temp(0.),
                bmp280_pressure(0.),
                bmp280_altitude(0.),
                dht11_temp(0.),
                dht11_humidity(0.),
                heat_index(0.);

ComfortState dht11_comfort_state;
TempAndHumidity dht11_temp_humidity;


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
    dht11_temp_humidity = dht11.getTempAndHumidity();

    if (dht11.getStatus() != 0) {
        Serial.println("dht11: error status: " + String(dht11.getStatusString()));
        return;
    }
    dht11_temp = dht11_temp_humidity.temperature;
    dht11_humidity = dht11_temp_humidity.humidity;
    heat_index = dht11.computeHeatIndex((float)bmp280_temp,
                                        dht11_temp_humidity.humidity);
    dht11.getComfortRatio(dht11_comfort_state,
                          (float)bmp280_temp,
                          dht11_temp_humidity.humidity);
}

void updateSensors() {
    updateBMP280();
    updateDHT11();
    heat_index = dht11.computeHeatIndex(bmp280_temp, dht11_humidity, true);
}


