
#pragma once

#ifndef CODE_RTC_UTILS_H
#define CODE_RTC_UTILS_H

#include <Arduino.h>
#include <rtc.h>

String strftime_us(uint64_t timestamp_us, const char *fmt);

#endif