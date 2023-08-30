
#include <TaskManagerIO.h>

#include "animations.h"
#include "bitmaps.h"
#include "globals.h"

namespace Animations {
    void startup() {
        main_time->moveTo(27, 48, 1100);
        main_date->moveTo(27, 25, 1100);
        temp->moveTo(27, 40, 1100);
        press->moveTo(27, 60, 1200);
        rtc_indicator_false->moveTo(5, 24, 1450);
        thermometer->moveTo(5, 27, 1100);
    }
    void rtcCalibrate() {
        rtc_calibrated = true;
        rtc_indicator_check->setVisible(true);
        rtc_indicator_false->moveTo(5, 70, 1800);
        rtc_indicator_check->moveTo(5, 25, 1000);
        taskManager.schedule(onceSeconds(2), []{
            rtc_indicator_check->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_CALENDAR), 16, 16);
        });
    }
    void wifiConnected() {
        wifi_indicator->moveTo(0, -20, 1000);
        wifi_indicator->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_WIFI), 16, 16);
        taskManager.schedule(onceMillis(700), []{
            wifi_indicator->moveTo(0, 0, 1000);
        });
    }
    void wifiDisconnected() {
        wifi_indicator->moveTo(0, -20, 1000);
        wifi_indicator->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_WIFI_OFF), 16, 16);
        taskManager.schedule(onceMillis(700), []{
            wifi_indicator->moveTo(0, 0, 1000);
        });
    }
    void serverConnected() {
        server_indicator->moveTo(18, 0, 1000);
    }
    void serverDisconnected() {
        server_indicator->moveTo(18, -20, 1000);
    }
}
