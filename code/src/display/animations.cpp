
#include <TaskManagerIO.h>

#include "animations.h"
#include "bitmaps.h"


namespace Animations {
    void startup() {
        UIComponents::main_time->moveTo(27, 48, 1100);
        UIComponents::main_date->moveTo(27, 25, 1100);
        UIComponents::temp->moveTo(27, 40, 1100);
        UIComponents::press->moveTo(27, 60, 1200);
        UIComponents::rtc_indicator_false->moveTo(5, 24, 1450);
        UIComponents::thermometer->moveTo(5, 27, 1100);
        UIComponents::humidity_indicator->moveTo(4, 47, 1200);
    }
    void rtcCalibrate() {
        UIComponents::rtc_indicator_check->setVisible(true);
        UIComponents::rtc_indicator_false->moveTo(5, 70, 1800);
        UIComponents::rtc_indicator_check->moveTo(5, 25, 1000);
        taskManager.schedule(onceSeconds(2), []{
            UIComponents::rtc_indicator_check->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_CALENDAR), 16, 16);
        });
    }
    void wifiConnected() {
        UIComponents::wifi_indicator->moveTo(0, -20, 1000);
        UIComponents::wifi_indicator->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_WIFI), 16, 16);
        taskManager.schedule(onceMillis(700), []{
            UIComponents::wifi_indicator->moveTo(0, 0, 1000);
        });
    }
    void wifiDisconnected() {
        UIComponents::wifi_indicator->moveTo(0, -20, 1000);
        UIComponents::wifi_indicator->setBitmap(const_cast<uint8_t *>(Bitmaps::ICON_WIFI_OFF), 16, 16);
        taskManager.schedule(onceMillis(700), []{
            UIComponents::wifi_indicator->moveTo(0, 0, 1000);
        });
    }
    void serverConnected() {
        UIComponents::server_indicator->moveTo(18, 0, 1000);
    }
    void serverDisconnected() {
        UIComponents::server_indicator->moveTo(18, -20, 1000);
    }
}
