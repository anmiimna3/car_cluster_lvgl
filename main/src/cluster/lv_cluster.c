#include <string.h>
#include "stdlib.h"
#include <math.h>
#include <stdio.h>
/**
 * @file lv_cluster.c
 * 
*/

/*********************
 *      INCLUDES
 *********************/
#include "lv_cluster.h"

static void set_angle(void * obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void set_speed(void *obj, int32_t v)
{
    char text[4];
    sprintf(text, "%d", v);
    printf("%d\n", v);
    lv_label_set_text(obj, text);
}

void lv_cluster(void)
{
    //background
    lv_disp_set_bg_color(NULL, lv_palette_main(LV_PALETTE_AMBER));
    static lv_style_t bg_style;
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, lv_palette_main(LV_PALETTE_BLUE_GREY));
    lv_style_set_bg_grad_color(&bg_style, lv_palette_main(LV_PALETTE_NONE));
    lv_style_set_bg_grad_dir(&bg_style, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_stop(&bg_style, 450);
    lv_obj_add_style(lv_scr_act(), &bg_style, LV_PART_MAIN);


    // //arc img (gradient)
    // LV_IMG_DECLARE(ring_transparent);
    // lv_obj_t *kkkkk;
    // kkkkk = lv_img_create(lv_scr_act());
    // lv_img_set_src(kkkkk, &ring_transparent);
    // lv_obj_set_pos(kkkkk, 20, 100);

    //arc gradient
    lv_obj_t * icon = lv_obj_create(lv_scr_act());
    static lv_style_t grad_style;
    lv_style_init(&grad_style);
    lv_style_set_radius(&grad_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(icon, &grad_style, LV_PART_MAIN);
    lv_color_t cyan = lv_color_make(1, 233, 189); 
    lv_style_set_bg_color(&grad_style, cyan);
    lv_style_set_bg_grad_color(&grad_style, lv_palette_darken(LV_PALETTE_BLUE, 3));
    lv_style_set_bg_grad_stop(&grad_style, 150);
    lv_style_set_bg_grad_dir(&grad_style, LV_GRAD_DIR_HOR);
    lv_obj_set_size(icon, 300, 300);
    lv_obj_set_pos(icon, 20, 100);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);

    lv_draw_mask_fade_param_t * fade = lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
    static lv_area_t area;
    // lv_draw_mask_fade_init(fade, );


    // inner circle
    lv_obj_t *inner_circle = lv_obj_create(icon);
    static lv_style_t inner_circle_style;
    lv_obj_remove_style(inner_circle, &inner_circle_style, LV_PART_MAIN);
    lv_style_init(&inner_circle_style);
    lv_style_set_bg_color(&inner_circle_style, lv_palette_main(LV_PALETTE_BLUE_GREY));
    lv_obj_add_style(inner_circle, &inner_circle_style, LV_PART_MAIN);
    lv_style_set_radius(&inner_circle_style, LV_RADIUS_CIRCLE);
    lv_obj_center(inner_circle);
    lv_obj_set_size(inner_circle, 240, 240);
    lv_style_set_outline_pad(&inner_circle_style, -2);
    lv_style_set_outline_color(&inner_circle_style, lv_palette_main(LV_PALETTE_BLUE_GREY));


    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_bg_color(&style_indic, lv_palette_lighten(LV_PALETTE_RED, 3));
    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);
    lv_style_set_arc_width(&style_indic, 30);
    lv_style_set_arc_rounded(&style_indic, false);


    lv_style_set_outline_width(&style_indic, 2);
    lv_style_set_outline_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE));
    lv_style_set_outline_pad(&style_indic, 0);
    lv_style_set_arc_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE_GREY));


    static lv_style_t style_indic_pr;
    lv_style_init(&style_indic_pr);
    lv_style_set_shadow_color(&style_indic_pr, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_shadow_width(&style_indic_pr, 10);
    lv_style_set_shadow_spread(&style_indic_pr, 3);

    //arc
    lv_obj_t * arc = lv_arc_create(icon);
    lv_obj_remove_style(arc, NULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_rotation(arc, 500);
    lv_obj_add_style(arc, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_style(arc, &style_indic_pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_arc_set_value(arc, 70);
    lv_obj_set_size(arc, 300, 300);
    lv_obj_center(arc);


    lv_obj_add_style(arc, &style_indic, LV_PART_INDICATOR);
    lv_obj_add_style(arc, &style_indic_pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
    lv_arc_set_value(arc, 100);
    lv_arc_set_mode(arc, LV_ARC_MODE_REVERSE);

    //arc border
    lv_obj_t * arc_border = lv_obj_create(icon);
    static lv_style_t arc_border_style;
    lv_style_init(&arc_border_style);
    lv_style_set_bg_opa(&arc_border_style, 0);
    lv_style_set_outline_width(&arc_border_style, 3);
    lv_style_set_outline_color(&arc_border_style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_outline_pad(&arc_border_style, 1);
    lv_style_set_radius(&arc_border_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(arc_border, &arc_border_style, LV_PART_MAIN);
    lv_obj_set_size(arc_border, 300, 300);
    lv_obj_center(arc_border);

    
    //speed border
    lv_obj_t * speed_border = lv_obj_create(icon);
    static lv_style_t speed_border_style;
    lv_style_init(&speed_border_style);
    lv_style_set_bg_opa(&speed_border_style, 0);
    lv_style_set_outline_width(&speed_border_style, 3);
    lv_style_set_outline_color(&speed_border_style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_outline_pad(&speed_border_style, 1);
    lv_style_set_radius(&speed_border_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(speed_border, &speed_border_style, LV_PART_MAIN);
    lv_obj_set_size(speed_border, 150, 150);
    lv_obj_center(speed_border);


    //arc counters style
    static lv_style_t counter_style;
    lv_style_init(&counter_style);
    lv_style_set_text_color(&counter_style, lv_palette_lighten(LV_PALETTE_BLUE, 5));
    lv_style_set_text_font(&counter_style, &lv_font_montserrat_20);


    // //arc counter 0
    // lv_obj_t * counter_0 = lv_label_create(icon);
    // lv_label_set_text(counter_0, "0");
    // lv_obj_set_pos(counter_0, 40, 170);
    // lv_obj_add_style(counter_0, &counter_style, LV_PART_MAIN);

    // //arc counter 50
    // lv_obj_t * counter_50 = lv_label_create(icon);
    // lv_label_set_text(counter_50, "50");
    // lv_obj_set_pos(counter_50, 30, 150);
    // lv_obj_add_style(counter_50, &counter_style, LV_PART_MAIN); 

    // //arc counter 100
    // lv_obj_t * counter_100 = lv_label_create(icon);
    // lv_label_set_text(counter_100, "100");
    // lv_obj_set_pos(counter_100, 100, 50);
    // lv_obj_add_style(counter_100, &counter_style, LV_PART_MAIN); 

    // //arc counter 150
    // lv_obj_t * counter_150 = lv_label_create(icon);
    // lv_label_set_text(counter_150, "150");
    // lv_obj_set_pos(counter_150, 230, 50);
    // lv_obj_add_style(counter_150, &counter_style, LV_PART_MAIN); 

    // //arc counter 200
    // lv_obj_t * counter_200 = lv_label_create(icon);
    // lv_label_set_text(counter_200, "200");
    // lv_obj_set_pos(counter_200, 300, 120);
    // lv_obj_add_style(counter_200, &counter_style, LV_PART_MAIN); 
    

    //speed number
    static lv_style_t speed_style;
    lv_style_init(&speed_style);
    lv_style_set_text_color(&speed_style, lv_palette_lighten(LV_PALETTE_GREEN, 5));
    lv_style_set_text_font(&speed_style, &lv_font_montserrat_48);
    lv_obj_t * speed = lv_label_create(icon);
    lv_label_set_text(speed, "100");
    lv_obj_center(speed);
    lv_obj_add_style(speed, &speed_style, LV_PART_MAIN);



    //arc animation
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 100, 45);
    lv_anim_start(&a);


    //speed text animation
    lv_anim_t b ;
    lv_anim_init(&b);
    lv_anim_set_var(&b, speed);
    lv_anim_set_exec_cb(&b, set_speed);
    lv_anim_set_time(&b, 3000);
    lv_anim_set_repeat_count(&b, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&b, 500);
    lv_anim_set_values(&b, 0, 200);
    lv_anim_start(&b);
}