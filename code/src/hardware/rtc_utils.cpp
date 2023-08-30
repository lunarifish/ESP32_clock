
#include "rtc_utils.h"

#include <ctime>


uint32_t timestamp_calib_offset = 0;
bool rtc_calibrated = false;

String strftime_us(uint64_t timestamp_us, const char *fmt) {
    time_t rtc_current = (time_t)(timestamp_us / 1000000 + timestamp_calib_offset);
    struct tm *current_tm = localtime(&rtc_current);

    char now_str[64];
    strftime(now_str, 64, fmt, current_tm);

    return String(now_str);
}
