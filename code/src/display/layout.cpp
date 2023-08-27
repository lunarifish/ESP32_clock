
#include "layout.h"
#include "globals.h"
#include "bitmaps.h"


ComponentsManager<display> *components_manager = new ComponentsManager<display>();

TextBox<display> *main_date = new TextBox<display>("", 27, 0, u8g2_font_Wizzard_tr, &display_0);
TextBox<display> *main_time = new TextBox<display>("", 27, 0, u8g2_font_10x20_tf, &display_0);
TextBox<display> *temp_press = new TextBox<display>("", 27, 0, u8g2_font_Wizzard_tr, &display_0);
TextBox<display> *fps = new TextBox<display>("", 0, 60, u8g2_font_Wizzard_tr, &display_0);

Bitmap<display>  *rtc_indicator_false = new Bitmap<display>(const_cast<uint8_t *>(bitmaps::calendar_X), 5, 0, 16, 16, &display_0);
Bitmap<display>  *rtc_indicator_check = new Bitmap<display>(const_cast<uint8_t *>(bitmaps::check_circle), 5, 0, 16, 16, &display_0);


void UIregisterComponents() {
    components_manager->register_component(main_date);
    components_manager->register_component(main_time);
    components_manager->register_component(temp_press);
    components_manager->register_component(fps);
    components_manager->register_component(rtc_indicator_false);
    components_manager->register_component(rtc_indicator_check);
}