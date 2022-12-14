#pragma once

#include "ui_screen.h"

class ui_boot_screen final : public ui_screen
{
public:
    using ui_screen::ui_screen;
    
    void init() override
    {
        ui_screen::init();
        lv_obj_clear_flag(screen, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_scrollbar_mode(screen, LV_SCROLLBAR_MODE_OFF);
        lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_bg_opa(screen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

        LV_IMG_DECLARE(ui_img_logo);
        boot_logo = lv_img_create(screen);
        lv_img_set_src(boot_logo, &ui_img_logo);
        lv_obj_set_size(boot_logo, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_align(boot_logo, LV_ALIGN_CENTER, 0, -20);

        boot_message = lv_label_create(screen);
        lv_obj_set_size(boot_message, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
        lv_obj_align(boot_message, LV_ALIGN_CENTER, 0, 60);
        lv_label_set_text_static(boot_message, "Starting");
        lv_obj_set_style_text_color(boot_message, lv_color_hex(0xFCFEFC), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(boot_message, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    void set_boot_message(const String &message)
    {
        lv_label_set_text(boot_message, message.c_str());
    }

    void set_boot_message(const char *message)
    {
        lv_label_set_text_static(boot_message, message);
    }

    void show_screen()
    {
        lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, false);
    }

private:
    lv_obj_t *boot_message;
    lv_obj_t *boot_logo;
};