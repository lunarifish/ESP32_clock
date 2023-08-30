
#include <Arduino.h>
#include <rtc.h>

#include "misc_functions.h"
#include "..\hardware\rtc_utils.h"
#include "layout.h"


double fps_update_timer = 0.;
uint8_t fps_frame_counter = 0;


void updateFPS() {
    ++fps_frame_counter;
    if (millis() - fps_update_timer > 1000) {
        fps_update_timer = millis();
        fps->setText("fps:" + String(fps_frame_counter));
        fps_frame_counter = 0;
    }
}


void updateDateTime() {
    if ((esp_rtc_get_time_us() / 100000 % 10) < 5)
        main_time->setText(strftime_us(esp_rtc_get_time_us(), "%H:%M:%S"));
    else
        main_time->setText(strftime_us(esp_rtc_get_time_us(), "%H:%M %S"));

    if (timer_mode)
        main_date->setText("Timer Mode");
    else
        main_date->setText(strftime_us(esp_rtc_get_time_us(), "%Y-%m-%d"));
}


void updateTempPressHumid() {
    temp->setText(String(bmp280_temp, 1) + "/" + String(heat_index, 1) + ".C");
    press->setText(String((uint8_t)dht11_humidity) + "%RH");
    // press->setText(String(bmp280_pressure / 100) + "hPa");
}


void updateStrings() {
    updateFPS();
    updateDateTime();
    updateTempPressHumid();
}

