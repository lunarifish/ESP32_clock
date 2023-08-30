
#pragma once

#ifndef CODE_LAYOUT_H
#define CODE_LAYOUT_H

#include "ui_framework/components_manager.hpp"
#include "ui_framework/components.hpp"
#include "globals.h"


namespace UIComponents {
    extern TextBox<display> *main_date;
    extern TextBox<display> *main_time;
    extern TextBox<display> *temp;
    extern TextBox<display> *press;
    extern TextBox<display> *humidity;
    extern TextBox<display> *fps;

    extern Bitmap<display>  *rtc_indicator_false;
    extern Bitmap<display>  *rtc_indicator_check;
    extern Bitmap<display>  *wifi_indicator;
    extern Bitmap<display>  *server_indicator;
    extern Bitmap<display>  *thermometer;
    extern Bitmap<display>  *humidity_indicator;
}


void UIregisterComponents();
void UIsetup();

#endif //CODE_LAYOUT_H
