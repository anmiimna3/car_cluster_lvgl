/**
 * @file cl_gear_roller.c
 *
**/

/*********************
 *      INCLUDES
 *********************/

#include "cl_gear_roller.h"



/*********************
 *      DEFINES
 *********************/



/**********************
 *  STATIC PROTOTYPES
 **********************/



/**********************
 *  STATIC VARIABLES
 **********************/




/**********************
 *   GLOBAL FUNCTIONS
 **********************/

cl_gear_roller_t * cl_gear_roller_create(lv_obj_t * parent, lv_coord_t x, lv_coord_t y)
{
    cl_gear_roller_t * obj = malloc(sizeof(cl_gear_roller_t));

    //base background obj
    lv_obj_t * base = lv_obj_create(parent);
    lv_obj_remove_style_all(base);
    lv_obj_set_size(base, x, y);

    lv_obj_t * R_label = lv_label_create(base);
    lv_label_set_text(R_label, "R");
    lv_obj_center(R_label);
    lv_obj_set_pos(R_label, -80, 0);
    lv_obj_set_style_text_color(R_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(R_label, &lv_font_montserrat_48, LV_PART_MAIN);

    lv_obj_t * D_label = lv_label_create(base);
    lv_label_set_text(D_label, "D");
    // int D_x = (x / 2) - (40 / 2);
    // lv_obj_set_pos(D_label, D_x, 0);
    lv_obj_center(D_label);
    lv_obj_set_style_text_color(D_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(D_label, &lv_font_montserrat_48, LV_PART_MAIN);



    lv_obj_t * N_label = lv_label_create(base);
    lv_label_set_text(N_label, "N");
    lv_obj_set_align(N_label, LV_ALIGN_CENTER);
    lv_obj_center(N_label);
    lv_obj_set_pos(N_label, 80, 0);
    lv_obj_set_style_text_color(N_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(N_label, &lv_font_montserrat_48, LV_PART_MAIN);


    obj->R = R_label;
    obj->D = D_label;
    obj->N = N_label;
    obj->selected = 0;
    obj->parent = base;

    return obj;
}