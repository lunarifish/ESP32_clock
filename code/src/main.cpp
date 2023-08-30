
#include <Arduino.h>
#include <TaskManagerIO.h>

#include "config.h"
#include "globals.h"
#include "hardware/devices_init.h"
#include "hardware/led_utils.h"
#include "display/layout.h"
#include "display/animations.h"
#include "display/misc_functions.h"
#include "multitasking/async_tasks.h"

bool I2C_BUS_0_BUSY;
bool I2C_BUS_1_BUSY;
bool timer_mode = true;


void loop1(void *param) {
    while (true) taskManager.runLoop();
}


void setup() {
    Serial.begin(MONITOR_SPEED);
    initDevices();
    UIregisterComponents();
    UIsetup();

    LEDblink(2, 100);
    Animations::startup();
    initRepeatTasks();
    xTaskCreatePinnedToCore(loop1, "backend", 10000, nullptr, 1, nullptr, 0);
}


uint64_t frame_counter = 0;


void loop() {
    display_0.clearDisplay();
    display_1.clearDisplay();

    updateStrings();

    components_manager->updateFrame();

    if (!I2C_BUS_0_BUSY)
        display_1.display();
    display_0.display();

    ++frame_counter;
}
