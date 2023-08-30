
#include "ntp.h"

#include <Arduino.h>
#include <ctime>
#include <WiFi.h>

#include "..\config.h"
#include "..\display\animations.h"


const char *NTP1 = "ntp1.aliyun.com";
const char *NTP2 = "ntp2.aliyun.com";
const char *NTP3 = "ntp3.aliyun.com";


void setClock() {
    if (rtc_calibrated) return;

    uint8_t retrys = 1;
    while (!WiFi.isConnected()) {
        if (retrys == RTC_CALIB_MAX_RETRYS) return;
        sleep(RTC_CALIB_RETRY_INTERVAL);
        ++retrys;
    }

    Animations::serverConnected();
    Serial.println("rtc: calibrating");
    configTime(0, 0, NTP1, NTP2, NTP3);
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo)) {
        Serial.println("rtc: Failed to obtain time");
        Animations::serverDisconnected();
        return;
    }
    timestamp_calib_offset = mktime(&timeInfo) + 3600 * 8;
    Animations::serverDisconnected();
    Animations::rtcCalibrate();

    rtc_calibrated = true;
    timer_mode = false;
    Serial.println("rtc: calibrated");
}


