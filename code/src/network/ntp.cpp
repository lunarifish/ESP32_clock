
#include "ntp.h"

#include <Arduino.h>
#include <ctime>
#include <WiFi.h>

#include "..\config.h"
#include "..\globals.h"
#include "..\display\animations.h"


const char *NTP1 = "ntp1.aliyun.com";
const char *NTP2 = "ntp2.aliyun.com";
const char *NTP3 = "ntp3.aliyun.com";


void setClock() {
    if (rtc_calibrated) return;

    Animations::serverConnected();

    struct tm timeInfo;
    for (uint8_t i = 0; i < RTC_CALIB_MAX_RETRYS; ++i) {
        if (!WiFi.isConnected()) continue;

        Serial.println("rtc: calibrating");
        configTime(0, 0, NTP1, NTP2, NTP3);

        // if failed
        if (!getLocalTime(&timeInfo)) {
            Serial.println("rtc: Failed to obtain time");
            sleep(RTC_CALIB_RETRY_INTERVAL);
            continue;
        }

        // success
        timestamp_calib_offset = mktime(&timeInfo) + 3600 * 8;
        rtc_calibrated = true;
        timer_mode = false;
        Serial.println("rtc: calibrated");

        Animations::rtcCalibrate();
        break;
    }
    Animations::serverDisconnected();
}
