
#include "async_tasks.h"
#include <TaskManagerIO.h>

#include "..\globals.h"
#include "..\hardware\sensor_tasks.h"
#include "..\network\ntp.h"


void initRepeatTasks() {
    Serial.println("task manager: background tasks assign start");
    taskid_t wifi        = taskManager.schedule(repeatSeconds(5), &wifi_manager);
    taskid_t ntp         = taskManager.schedule(repeatSeconds(10),setClock);
    taskid_t sensor      = taskManager.schedule(repeatMillis(900),updateSensors);

    taskid_t ntp_refresh = taskManager.schedule(repeatSeconds(1800), []{
        rtc_calibrated = false;
    });
    Serial.println("task manager: background tasks assign end");
}

