#pragma once

#ifndef RTC_H
#define RTC_H

#include <Arduino.h>
#include <rtc.h>

String strftime_us(uint64_t timestamp_us, const char *fmt);

#endif