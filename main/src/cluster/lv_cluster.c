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



/*********************
 *      DEFINES
 *********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void set_angle(void * obj, int32_t v);
static void set_speed(void * obj, int32_t v);
static lv_obj_t * cl_create_speed_circle(lv_obj_t * parent);
static lv_obj_t * cl_create_speed_arc(lv_obj_t * parent);
static lv_obj_t * cl_create_speed_label(lv_obj_t * parent);
static lv_obj_t * cl_create_power_circle(lv_obj_t * parent);
static lv_obj_t * cl_create_power_arc(lv_obj_t * parent);
static lv_obj_t * cl_create_power_label(lv_obj_t * parent);
static lv_obj_t * cl_create_middle_part(lv_obj_t * parent);
static lv_obj_t * cl_create_line(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_point_t points[2]);

/**********************
 * TODO
 **********************/
static lv_obj_t * cl_create_line_animation(lv_obj_t * parent);
static lv_obj_t * cl_create_clock(lv_obj_t * parent);
static lv_obj_t * cl_create_gear_mode(lv_obj_t * parent);
static lv_obj_t * cl_create_driving_mode(lv_obj_t * parent);


/**********************
 *  STATIC VARIABLES
 **********************/
static int32_t cl_speed_arc_size = 300;
static int32_t cl_speed_arc_inner_cirle_size = 240;
static int32_t cl_speed_arc_width = 30;



/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void cl_speed_arc_set_angle(void * obj, int32_t v)
{
    lv_arc_set_value(obj, v);
}

static void cl_speed_arc_set_speed(void *obj, int32_t v)
{
    char text[4];
    sprintf(text, "%d", v);
    lv_label_set_text(obj, text);
}

static void cl_line_movement(void * obj, int32_t v)
{
    lv_obj_set_pos(obj, 175 + v, 10 * v);
}

static void cl_line_movement2(void * obj, int32_t v)
{
    lv_obj_set_pos(obj, 95 - v, 10 * v);
}


// creating the speed arc and returns the base obj pointer
static lv_obj_t * cl_create_speed_circle(lv_obj_t * parent)
{
    //background circle
    lv_color_t cyan = lv_color_make(1, 233, 189);
    lv_obj_t * bg_grad = lv_obj_create(lv_scr_act());
    static lv_style_t bg_grad_style;
    lv_style_init(&bg_grad_style);
    lv_style_set_radius(&bg_grad_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(bg_grad, &bg_grad_style, LV_PART_MAIN);
    lv_style_set_bg_color(&bg_grad_style, cyan);
    lv_style_set_bg_grad_color(&bg_grad_style, lv_palette_darken(LV_PALETTE_BLUE, 3));
    lv_style_set_bg_grad_stop(&bg_grad_style, (cl_speed_arc_size / 2));
    lv_style_set_bg_grad_dir(&bg_grad_style, LV_GRAD_DIR_HOR);
    lv_obj_set_size(bg_grad, cl_speed_arc_size, cl_speed_arc_size);
    lv_obj_set_pos(bg_grad, 50, 150);
    lv_obj_clear_flag(bg_grad, LV_OBJ_FLAG_SCROLLABLE);

    // inner circle
    lv_obj_t *inner_circle = lv_obj_create(bg_grad);
    static lv_style_t inner_circle_style;
    lv_obj_remove_style(inner_circle, &inner_circle_style, LV_PART_MAIN);
    lv_style_init(&inner_circle_style);
    lv_style_set_bg_color(&inner_circle_style, lv_palette_main(LV_PALETTE_BLUE_GREY));
    lv_obj_add_style(inner_circle, &inner_circle_style, LV_PART_MAIN);
    lv_style_set_radius(&inner_circle_style, LV_RADIUS_CIRCLE);
    lv_obj_center(inner_circle);
    lv_obj_set_size(inner_circle, cl_speed_arc_inner_cirle_size, cl_speed_arc_inner_cirle_size);
    lv_style_set_outline_pad(&inner_circle_style, -2);
    lv_style_set_outline_color(&inner_circle_style, lv_palette_main(LV_PALETTE_BLUE_GREY));

    return bg_grad;
}


static lv_obj_t * cl_create_speed_arc(lv_obj_t * parent)
{
    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_arc_width(&style_indic, cl_speed_arc_width);
    lv_style_set_arc_rounded(&style_indic, false);
    lv_style_set_arc_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE_GREY));

    lv_obj_t * arc = lv_arc_create(parent);
    lv_obj_remove_style(arc, NULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_rotation(arc, 500);
    lv_obj_add_style(arc, &style_indic, LV_PART_INDICATOR);
    lv_arc_set_value(arc, 70);
    lv_obj_set_size(arc, cl_speed_arc_size, cl_speed_arc_size);
    lv_obj_center(arc);
    lv_arc_set_value(arc, 100);
    lv_arc_set_mode(arc, LV_ARC_MODE_REVERSE);

    //arc border
    lv_obj_t * arc_border = lv_obj_create(parent);
    static lv_style_t arc_border_style;
    lv_style_init(&arc_border_style);
    lv_style_set_bg_opa(&arc_border_style, 0);
    lv_style_set_outline_width(&arc_border_style, 3);
    lv_style_set_outline_color(&arc_border_style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_outline_pad(&arc_border_style, 1);
    lv_style_set_radius(&arc_border_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(arc_border, &arc_border_style, LV_PART_MAIN);
    lv_obj_set_size(arc_border, cl_speed_arc_size, cl_speed_arc_size);
    lv_obj_center(arc_border);


    //arc counters style
    static lv_style_t counter_style;
    lv_style_init(&counter_style);
    lv_style_set_text_color(&counter_style, lv_palette_lighten(LV_PALETTE_BLUE, 5));
    lv_style_set_text_font(&counter_style, &lv_font_montserrat_16);


    //arc counter 0
    lv_obj_t * counter_0 = lv_label_create(parent);
    lv_label_set_text(counter_0, "0");
    lv_obj_set_pos(counter_0, 40, 185);
    lv_obj_add_style(counter_0, &counter_style, LV_PART_MAIN);

    // //arc counter 50
    lv_obj_t * counter_50 = lv_label_create(parent);
    lv_label_set_text(counter_50, "50");
    lv_obj_set_pos(counter_50, 20, 95);
    lv_obj_add_style(counter_50, &counter_style, LV_PART_MAIN); 

    // //arc counter 100
    lv_obj_t * counter_100 = lv_label_create(parent);
    lv_label_set_text(counter_100, "100");
    lv_obj_set_pos(counter_100, 70, 30);
    lv_obj_add_style(counter_100, &counter_style, LV_PART_MAIN); 

    // //arc counter 150
    lv_obj_t * counter_150 = lv_label_create(parent);
    lv_label_set_text(counter_150, "150");
    lv_obj_set_pos(counter_150, 160, 30);
    lv_obj_add_style(counter_150, &counter_style, LV_PART_MAIN); 

    // //arc counter 200
    lv_obj_t * counter_200 = lv_label_create(parent);
    lv_label_set_text(counter_200, "200");
    lv_obj_set_pos(counter_200, 210, 95);
    lv_obj_add_style(counter_200, &counter_style, LV_PART_MAIN); 
    
    return arc;
}


static lv_obj_t * cl_create_speed_label(lv_obj_t * parent)
{
    //speed border
    lv_obj_t * speed_border = lv_obj_create(parent);
    static lv_style_t speed_border_style;
    lv_style_init(&speed_border_style);
    lv_style_set_bg_opa(&speed_border_style, 0);
    lv_style_set_outline_width(&speed_border_style, 3);
    lv_style_set_outline_color(&speed_border_style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_outline_pad(&speed_border_style, 1);
    lv_style_set_radius(&speed_border_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(speed_border, &speed_border_style, LV_PART_MAIN);
    lv_obj_set_size(speed_border, cl_speed_arc_size / 2, cl_speed_arc_size / 2);
    lv_obj_center(speed_border);

    //speed number
    static lv_style_t speed_style;
    lv_style_init(&speed_style);
    lv_style_set_text_color(&speed_style, lv_palette_lighten(LV_PALETTE_GREEN, 5));
    lv_style_set_text_font(&speed_style, &lv_font_montserrat_48);
    lv_obj_t * speed = lv_label_create(parent);
    lv_label_set_text(speed, "100");
    lv_obj_center(speed);
    lv_obj_add_style(speed, &speed_style, LV_PART_MAIN);

    return speed;
}


static lv_obj_t * cl_create_power_circle(lv_obj_t * parent)
{
    //background circle
    lv_color_t cyan = lv_color_make(1, 233, 189);
    lv_obj_t * bg_grad = lv_obj_create(lv_scr_act());
    static lv_style_t bg_grad_style;
    lv_style_init(&bg_grad_style);
    lv_style_set_radius(&bg_grad_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(bg_grad, &bg_grad_style, LV_PART_MAIN);
    lv_style_set_bg_color(&bg_grad_style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_grad_color(&bg_grad_style, lv_palette_main(LV_PALETTE_YELLOW));
    lv_style_set_bg_grad_stop(&bg_grad_style, 250);
    lv_style_set_bg_grad_dir(&bg_grad_style, LV_GRAD_DIR_HOR);
    lv_obj_set_size(bg_grad, cl_speed_arc_size, cl_speed_arc_size);
    lv_obj_set_pos(bg_grad, 680, 150);
    lv_obj_clear_flag(bg_grad, LV_OBJ_FLAG_SCROLLABLE);

    // inner circle
    lv_obj_t *inner_circle = lv_obj_create(bg_grad);
    static lv_style_t inner_circle_style;
    lv_obj_remove_style(inner_circle, &inner_circle_style, LV_PART_MAIN);
    lv_style_init(&inner_circle_style);
    lv_style_set_bg_color(&inner_circle_style, lv_palette_main(LV_PALETTE_BLUE_GREY));
    lv_obj_add_style(inner_circle, &inner_circle_style, LV_PART_MAIN);
    lv_style_set_radius(&inner_circle_style, LV_RADIUS_CIRCLE);
    lv_obj_center(inner_circle);
    lv_obj_set_size(inner_circle, cl_speed_arc_inner_cirle_size, cl_speed_arc_inner_cirle_size);
    lv_style_set_outline_pad(&inner_circle_style, -2);
    lv_style_set_outline_color(&inner_circle_style, lv_palette_main(LV_PALETTE_BLUE_GREY));

    return bg_grad;
}

static lv_obj_t * cl_create_power_arc(lv_obj_t * parent)
{
    static lv_style_t style_indic;
    lv_style_init(&style_indic);
    lv_style_set_arc_width(&style_indic, cl_speed_arc_width);
    lv_style_set_arc_rounded(&style_indic, false);
    lv_style_set_arc_color(&style_indic, lv_palette_main(LV_PALETTE_BLUE_GREY));

    lv_obj_t * arc = lv_arc_create(parent);
    lv_obj_remove_style(arc, NULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_rotation(arc, 400);
    lv_obj_add_style(arc, &style_indic, LV_PART_INDICATOR);
    lv_obj_set_size(arc, cl_speed_arc_size, cl_speed_arc_size);
    lv_obj_center(arc);
    lv_arc_set_value(arc, 100);

    //arc border
    lv_obj_t * arc_border = lv_obj_create(parent);
    static lv_style_t arc_border_style;
    lv_style_init(&arc_border_style);
    lv_style_set_bg_opa(&arc_border_style, 0);
    lv_style_set_outline_width(&arc_border_style, 3);
    lv_style_set_outline_color(&arc_border_style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_outline_pad(&arc_border_style, 1);
    lv_style_set_radius(&arc_border_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(arc_border, &arc_border_style, LV_PART_MAIN);
    lv_obj_set_size(arc_border, cl_speed_arc_size, cl_speed_arc_size);
    lv_obj_center(arc_border);

    return arc;
}


static lv_obj_t * cl_create_power_label(lv_obj_t * parent)
{
    //power border
    lv_obj_t * power_border = lv_obj_create(parent);
    static lv_style_t power_border_style;
    lv_style_init(&power_border_style);
    lv_style_set_bg_opa(&power_border_style, 0);
    lv_style_set_outline_width(&power_border_style, 3);
    lv_style_set_outline_color(&power_border_style, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_outline_pad(&power_border_style, 1);
    lv_style_set_radius(&power_border_style, LV_RADIUS_CIRCLE);
    lv_obj_add_style(power_border, &power_border_style, LV_PART_MAIN);
    lv_obj_set_size(power_border, cl_speed_arc_size / 2, cl_speed_arc_size / 2);
    lv_obj_center(power_border);

    //speed number
    static lv_style_t power_style;
    lv_style_init(&power_style);
    lv_style_set_text_color(&power_style, lv_palette_lighten(LV_PALETTE_GREEN, 5));
    lv_style_set_text_font(&power_style, &lv_font_montserrat_48);
    lv_obj_t * power = lv_label_create(parent);
    lv_label_set_text(power, "100");
    lv_obj_center(power);
    lv_obj_add_style(power, &power_style, LV_PART_MAIN);

    return power;
}


static lv_obj_t * cl_create_middle_part(lv_obj_t * parent)
{
    static lv_style_t back_ground_style;
    lv_style_init(&back_ground_style);
    lv_style_set_bg_opa(&back_ground_style, LV_OPA_TRANSP);

    lv_obj_t * back_ground = lv_obj_create(lv_scr_act());
    lv_obj_clear_flag(back_ground, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_remove_style_all(back_ground);
    lv_obj_add_style(back_ground, &back_ground_style, LV_PART_MAIN);
    lv_obj_set_size(back_ground, 280, 280);
    lv_obj_center(back_ground);

    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_lighten(LV_PALETTE_BLUE, 5));
    lv_style_set_line_rounded(&style_line, true);

    static lv_point_t line_points1[] = {{60, 0}, {0, 280}};
    lv_obj_t * line1 = lv_line_create(back_ground);
    lv_line_set_points(line1, line_points1, 2);
    lv_obj_add_style(line1, &style_line, LV_PART_MAIN);

    static lv_point_t line_points2[] = {{215, 0}, {275, 280}};
    lv_obj_t * line2 = lv_line_create(back_ground);
    lv_line_set_points(line2, line_points2, 2);
    lv_obj_add_style(line2, &style_line, LV_PART_MAIN);

    
    LV_IMG_DECLARE(car);
    lv_obj_t * car_pic = lv_img_create(back_ground);
    lv_img_set_src(car_pic, &car);
    lv_obj_center(car_pic);
    return back_ground;
}


static lv_obj_t * cl_create_line(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_point_t points[2])
{
    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_lighten(LV_PALETTE_BLUE, 5));
    lv_style_set_line_rounded(&style_line, true);

    /*Create a line and apply the new style*/
    lv_obj_t * line;
    line = lv_line_create(parent);
    lv_line_set_points(line, points, 2);     /*Set the points*/
    lv_obj_add_style(line, &style_line, LV_PART_MAIN);     /*Set the points*/
    lv_obj_set_pos(line, x, y);

    return line;
}


// setting background color and gradient
void cl_draw_background(void)
{
    static lv_style_t bg_style;
    lv_style_init(&bg_style);
    lv_style_set_bg_color(&bg_style, lv_palette_main(LV_PALETTE_BLUE_GREY));
    lv_style_set_bg_grad_color(&bg_style, lv_palette_main(LV_PALETTE_NONE));
    lv_style_set_bg_grad_dir(&bg_style, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_stop(&bg_style, 450);
    lv_obj_add_style(lv_scr_act(), &bg_style, 0);
}



void lv_cluster(void)
{
    //background
    cl_draw_background();

    //arc gradient
    lv_obj_t * speed_bg = cl_create_speed_circle(lv_scr_act());
    lv_obj_t * speed_arc = cl_create_speed_arc(speed_bg);
    lv_obj_t * speed_label = cl_create_speed_label(speed_bg);
    lv_obj_t * power_bg = cl_create_power_circle(lv_scr_act());
    lv_obj_t * power_arc = cl_create_power_arc(power_bg);
    lv_obj_t * power_label = cl_create_power_label(power_bg);
    lv_obj_t * middle_part = cl_create_middle_part(lv_scr_act());

    static lv_point_t line_points[] = { {0, 0}, {5, 50}};
    static lv_point_t line_points2[] = {{5, 0}, {0, 50}};
    lv_obj_t * line1 = cl_create_line(middle_part, 160, 0, line_points);
    lv_obj_t * line2 = cl_create_line(middle_part, 80, 0, line_points2);
    lv_obj_t * line3 = cl_create_line(middle_part, 160, 0, line_points);
    lv_obj_t * line4 = cl_create_line(middle_part, 80, 0, line_points2);


    // //arc img (gradient)
    // LV_IMG_DECLARE(ring_transparent);
    // lv_obj_t *kkkkk;
    // kkkkk = lv_img_create(lv_scr_act());
    // lv_img_set_src(kkkkk, &ring_transparent);
    // lv_obj_set_pos(kkkkk, 20, 100);

    // lv_draw_mask_fade_param_t * fade = lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
    // static lv_area_t area;
    // lv_draw_mask_fade_init(fade, );


    /*Create style*/
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_palette_lighten(LV_PALETTE_BLUE, 5));
    lv_style_set_line_rounded(&style_line, true);

    // /*Create a line and apply the new style*/
    // lv_obj_t * line1;
    // line1 = lv_line_create(lv_scr_act());
    // lv_line_set_points(line1, line_points, 2);     /*Set the points*/
    // lv_obj_add_style(line1, &style_line, LV_PART_MAIN);     /*Set the points*/
    // lv_obj_set_pos(line1, 500, 100);

    
    // lv_obj_t * line2;
    // line2 = lv_line_create(lv_scr_act());
    // lv_line_set_points(line2, line_points2, 2);
    // lv_obj_add_style(line2, &style_line, LV_PART_MAIN);
    // lv_obj_set_pos(line2, 450, 100);

    // lv_area_t area;
    // lv_obj_get_coords(speed_arc, &area);
    // lv_draw_mask_fade_param_t *mask_param = lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
    // lv_draw_mask_fade_init(mask_param, &area, LV_OPA_20, area.y1, LV_OPA_90, area.y2);
    // int mask_id = lv_draw_mask_add(mask_param, NULL);

    // lv_area_t roller_coords;
    // lv_obj_get_coords(power_label, &roller_coords);

    // lv_area_t rect_area;
    // rect_area.x1 = 1;
    // rect_area.x2 = 1;
    // rect_area.y1 = 4;
    // // rect_area.y2 = roller_coords.y1 + (lv_obj_get_height(obj) - font_h - line_space) / 2;
    // rect_area.y2 = 4;

    // int32_t mask_top_id = -1;
    // lv_draw_mask_fade_param_t * fade_mask_top = lv_mem_buf_get(sizeof(lv_draw_mask_fade_param_t));
    // lv_draw_mask_fade_init(fade_mask_top, &rect_area, LV_OPA_TRANSP, rect_area.y1, LV_OPA_COVER, rect_area.y2);
    // mask_top_id = lv_draw_mask_add(fade_mask_top, NULL);



    // fade_mask_top = lv_draw_mask_remove_id(mask_top_id);
    // lv_draw_mask_free_param(fade_mask_top);
    // lv_mem_buf_release(fade_mask_top);

    //speed arc animation
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, speed_arc);
    lv_anim_set_exec_cb(&a, cl_speed_arc_set_angle);
    lv_anim_set_time(&a, 3000);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&a, 500);
    lv_anim_set_values(&a, 100, 42);
    lv_anim_start(&a);

    //power arc animation
    lv_anim_t c;
    lv_anim_init(&c);
    lv_anim_set_var(&c, power_arc);
    lv_anim_set_exec_cb(&c, cl_speed_arc_set_angle);
    lv_anim_set_time(&c, 3000);
    lv_anim_set_repeat_count(&c, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&c, 500);
    lv_anim_set_values(&c, 100, 42);
    lv_anim_start(&c);


    //speed text animation
    lv_anim_t b ;
    lv_anim_init(&b);
    lv_anim_set_var(&b, speed_label);
    lv_anim_set_exec_cb(&b, cl_speed_arc_set_speed);
    lv_anim_set_time(&b, 3000);
    lv_anim_set_repeat_count(&b, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&b, 500);
    lv_anim_set_values(&b, 0, 200);
    lv_anim_start(&b);

    //power text animation
    lv_anim_t d;
    lv_anim_init(&d);
    lv_anim_set_var(&d, power_label);
    lv_anim_set_exec_cb(&d, cl_speed_arc_set_speed);
    lv_anim_set_time(&d, 3000);
    lv_anim_set_repeat_count(&d, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&d, 500);
    lv_anim_set_values(&d, 0, 120);
    lv_anim_start(&d);

    //line1 animation
    lv_anim_t f;
    lv_anim_init(&f);
    lv_anim_set_var(&f, line1);
    lv_anim_set_exec_cb(&f, cl_line_movement);
    lv_anim_set_time(&f, 1500);
    lv_anim_set_repeat_count(&f, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&f, 0);
    lv_anim_set_values(&f, 0, 40);
    lv_anim_start(&f);

    //line2 animation
    lv_anim_t s;
    lv_anim_init(&s);
    lv_anim_set_var(&s, line2);
    lv_anim_set_exec_cb(&s, cl_line_movement2);
    lv_anim_set_time(&s, 1500);
    lv_anim_set_repeat_count(&s, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&s, 0);
    lv_anim_set_values(&s, 0, 40);
    lv_anim_start(&s);


    //line3 animation
    lv_anim_t g;
    lv_anim_init(&g);
    lv_anim_set_var(&g, line3);
    lv_anim_set_exec_cb(&g, cl_line_movement);
    lv_anim_set_time(&g, 1500);
    lv_anim_set_repeat_count(&g, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&g, 0);
    lv_anim_set_values(&g, -20, 20);
    lv_anim_set_playback_delay(&g, 500);
    lv_anim_start(&g);

    //line4 animation
    lv_anim_t h;
    lv_anim_init(&h);
    lv_anim_set_var(&h, line4);
    lv_anim_set_exec_cb(&h, cl_line_movement2);
    lv_anim_set_time(&h, 1500);
    lv_anim_set_repeat_count(&h, LV_ANIM_REPEAT_INFINITE);    /*Just for the demo*/
    lv_anim_set_repeat_delay(&h, 0);
    lv_anim_set_values(&h, -20, 20);
    lv_anim_set_playback_delay(&h, 500);
    lv_anim_start(&h);
}