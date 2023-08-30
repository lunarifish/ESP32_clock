
#include <Arduino.h>
#include <rtc.h>

#include "..\hardware\rtc_utils.h"
#include "misc_functions.h"
#include "bitmaps.h"
#include "layout.h"


double fps_update_timer = 0.;
uint8_t fps_frame_counter = 0;


void updateFPS() {
    ++fps_frame_counter;
    if (millis() - fps_update_timer > 1000) {
        fps_update_timer = millis();
        UIComponents::fps->setText("fps:" + String(fps_frame_counter));
        fps_frame_counter = 0;
    }
}


void updateDateTime() {
    if ((esp_rtc_get_time_us() / 100000 % 10) < 5)
        UIComponents::main_time->setText(strftime_us(esp_rtc_get_time_us(), "%H:%M:%S"));
    else
        UIComponents::main_time->setText(strftime_us(esp_rtc_get_time_us(), "%H:%M %S"));

    if (timer_mode)
        UIComponents::main_date->setText("Timer Mode");
    else
        UIComponents::main_date->setText(strftime_us(esp_rtc_get_time_us(), "%Y-%m-%d"));
}


void updateTempPressHumid() {
    UIComponents::temp->setText(String(bmp280_temp, 1) + "/" + String(heat_index, 1) + ".C");
    UIComponents::press->setText(String((uint8_t)dht11_humidity) + "%RH");
    // press->setText(String(bmp280_pressure / 100) + "hPa");
}


void updateTempIndicator() {
    switch (dht11_comfort_state) {
        case Comfort_OK:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_HALF), 16, 16);
            break;
        case Comfort_TooHot:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_SUN), 16, 16);
            break;
        case Comfort_TooCold:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_SNOW), 16, 16);
            break;
        case Comfort_TooDry:
            break;
        case Comfort_TooHumid:
            break;
        case Comfort_HotAndHumid:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_HIGH), 16, 16);
            break;
        case Comfort_HotAndDry:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_HIGH), 16, 16);
            break;
        case Comfort_ColdAndHumid:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_LOW), 16, 16);
            break;
        case Comfort_ColdAndDry:
            UIComponents::thermometer->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_LOW), 16, 16);
            break;
    }
}


void updateComponents() {
    updateFPS();
    updateDateTime();
    updateTempPressHumid();
    updateTempIndicator();
}

