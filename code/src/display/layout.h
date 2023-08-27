
#pragma once

#ifndef CODE_LAYOUT_H
#define CODE_LAYOUT_H

#include "ui_framework/components_manager.hpp"
#include "ui_framework/components.hpp"
#include <U8g2lib.h>

typedef U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI* display;

extern TextBox<display> *main_date;
extern TextBox<display> *main_time;
extern TextBox<display> *temp_press;
extern TextBox<display> *fps;

extern Bitmap<display>  *rtc_indicator_false;
extern Bitmap<display>  *rtc_indicator_check;


void UIregisterComponents();

#endif //CODE_LAYOUT_H
