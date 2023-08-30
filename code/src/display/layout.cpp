
#include "layout.h"

#include "bitmaps.h"
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSans9pt7b.h>

#include <Fonts/FreeSansBold12pt7b.h>



ComponentsManager<display> *components_manager = new ComponentsManager<display>();

namespace UIComponents {
    TextBox<display> *main_date           = new TextBox<display>("", 27, 0, 1, &FreeSans9pt7b, &display_0);
    TextBox<display> *main_time           = new TextBox<display>("", 27, 0, 1, &FreeSansBold12pt7b, &display_0);
    TextBox<display> *temp                = new TextBox<display>("", 27, 0, 1, &FreeSans9pt7b, &display_1);
    TextBox<display> *press               = new TextBox<display>("", 27, 0, 1, &FreeSans9pt7b, &display_1);

    TextBox<display> *fps                 = new TextBox<display>("", 0, 20, 1, &FreeSans9pt7b, &display_1);

    Bitmap<display>  *rtc_indicator_false = new Bitmap<display> (const_cast<uint8_t *>(Bitmaps::ICON_CALENDAR_X), 5, 0, 16, 16, &display_0);
    Bitmap<display>  *rtc_indicator_check = new Bitmap<display> (const_cast<uint8_t *>(Bitmaps::ICON_CHECK_CIRCLE), 5, 0, 16, 16, &display_0);
    Bitmap<display>  *wifi_indicator      = new Bitmap<display> (const_cast<uint8_t *>(Bitmaps::ICON_WIFI_OFF), 0, 0, 16, 16, &display_1);
    Bitmap<display>  *server_indicator    = new Bitmap<display> (const_cast<uint8_t *>(Bitmaps::ICON_SERVER), 18, -20, 16, 16, &display_1);
    Bitmap<display>  *thermometer         = new Bitmap<display> (const_cast<uint8_t *>(Bitmaps::ICON_THERMOMETER_HALF), 5, 0, 16, 16, &display_1);
    Bitmap<display>  *humidity_indicator  = new Bitmap<display> (const_cast<uint8_t *>(Bitmaps::ICON_HUMIDITY), 4, 0, 16, 16, &display_1);

}

void UIregisterComponents() {
    components_manager->register_component(UIComponents::main_date);
    components_manager->register_component(UIComponents::main_time);
    components_manager->register_component(UIComponents::temp);
    components_manager->register_component(UIComponents::press);
    components_manager->register_component(UIComponents::fps);

    components_manager->register_component(UIComponents::rtc_indicator_false);
    components_manager->register_component(UIComponents::rtc_indicator_check);
    components_manager->register_component(UIComponents::wifi_indicator);
    components_manager->register_component(UIComponents::server_indicator);
    components_manager->register_component(UIComponents::thermometer);
    components_manager->register_component(UIComponents::humidity_indicator);
}

void UIsetup() {
    UIComponents::fps->setVisible(false);
    UIComponents::rtc_indicator_check->setVisible(false);
}