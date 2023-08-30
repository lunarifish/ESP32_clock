
#include "led_utils.h"

#include <Arduino.h>


void LEDblink(uint8_t times, uint16_t interval_ms) {
    for (int i = 0; i < times; ++i) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(interval_ms / 2);
        digitalWrite(LED_BUILTIN, LOW);
        delay(interval_ms / 2);
    }
}