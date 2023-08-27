
#include <Arduino.h>
#include <Wire.h>


#include "globals.h"
#include "config.h"
#include "hardware/devices_init.h"
#include "hardware/sensor_tasks.h"
#include "hardware/rtc.h"
#include "display/layout.h"
#include "display/bitmaps.h"



uint64_t frame_counter = 0;
uint8_t fps_frame_counter = 0;
double fps_update_timer = 0.;



void setup() {
    Serial.begin(MONITOR_SPEED);
    initI2CBus();
    initDevices();
    UIregisterComponents();


    fps->setVisible(false);
    rtc_indicator_check->setVisible(false);

    xTaskCreatePinnedToCore(updateSensors, "Sensor Updater", 10000, nullptr, 1, nullptr, 0);
}


void loop() {
    if (millis() - fps_update_timer > 1000) {
        fps_update_timer = millis();
        fps->setText("fps:" + String(fps_frame_counter));
        fps_frame_counter = 0;
    }

    display_0.clearBuffer();


    if (frame_counter == 100) {
        main_time->moveTo(27, 40, 1100);
        main_date->moveTo(27, 21, 1100);
        temp_press->moveTo(27, 56, 1100);
        rtc_indicator_false->moveTo(5, 25, 1450);
    }
    if (frame_counter == 1000) {
        rtc_calibrated = true;
        rtc_indicator_check->setVisible(true);
        rtc_indicator_false->moveTo(5, 70, 1800);
        rtc_indicator_check->moveTo(5, 25, 1000);
    }
    if (frame_counter == 1750) {
        rtc_indicator_check->setBitmap(const_cast<uint8_t *>(bitmaps::calendar), 16, 16);
    }


    main_time->setText(strftime_us(esp_rtc_get_time_us(), "%H:%M:%S"));
    temp_press->setText(String(bmp280_temp) + "°C / " + String(bmp280_pressure / 100) + "hPa");

    if (rtc_calibrated) {
        main_date->setText(strftime_us(esp_rtc_get_time_us(), "%Y-%m-%d"));
    } else {
        main_date->setText("RTC not calibrated");
    }


    components_manager->updateFrame();
    display_0.sendBuffer();

    ++fps_frame_counter;
    ++frame_counter;
}