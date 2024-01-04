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

static void cl_gear_roller_move_cb(cl_gear_roller_t * obj, int32_t v)
{
    if (v > -40)
        lv_obj_set_pos(obj->left, -80 + v, 0);
    else if (v == -40)
        lv_obj_set_pos(obj->left, 120, 0);
    else
        lv_obj_set_pos(obj->left, 160 + v, 0);
    
    lv_obj_set_pos(obj->mid, v, 0);
    
    if (v < 40)
        lv_obj_set_pos(obj->right, 80 + v, 0);
    else if (v == 40)
        lv_obj_set_pos(obj->right, -120, 0);
    else
        lv_obj_set_pos(obj->right, -160 + v, 0);

    if (v == -80){
        cl_gear_roller_t * temp = obj->left;
        obj->left = obj->mid;
        obj->mid = obj->right;
        obj->right = temp;
    }

    if (v == 80){
        cl_gear_roller_t * temp = obj->right;
        obj->right = obj->mid;
        obj->mid = obj->left;
        obj->left = temp;
    }
    if (v == 80 || v == -80){
        lv_obj_set_style_text_color(obj->left, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
        lv_obj_set_style_text_color(obj->right, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
        lv_obj_set_style_text_color(obj->mid, lv_color_white(), LV_PART_MAIN);

        lv_obj_set_style_text_font(obj->left, &lv_font_montserrat_34, LV_PART_MAIN);
        lv_obj_set_style_text_font(obj->right, &lv_font_montserrat_34, LV_PART_MAIN);
        lv_obj_set_style_text_font(obj->mid, &lv_font_montserrat_48, LV_PART_MAIN);

    }
}



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
    lv_obj_set_style_text_color(R_label, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_obj_set_style_text_font(R_label, &lv_font_montserrat_34, LV_PART_MAIN);

    lv_obj_t * D_label = lv_label_create(base);
    lv_label_set_text(D_label, "D");
    lv_obj_center(D_label);
    lv_obj_set_style_text_color(D_label, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(D_label, &lv_font_montserrat_48, LV_PART_MAIN);

    lv_obj_t * N_label = lv_label_create(base);
    lv_label_set_text(N_label, "N");
    lv_obj_set_align(N_label, LV_ALIGN_CENTER);
    lv_obj_center(N_label);
    lv_obj_set_pos(N_label, 80, 0);
    lv_obj_set_style_text_color(N_label, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_obj_set_style_text_font(N_label, &lv_font_montserrat_34, LV_PART_MAIN);

    lv_obj_t * selected_border = lv_obj_create(base);
    lv_obj_remove_style_all(selected_border);
    lv_obj_set_style_border_width(selected_border, 2, LV_PART_MAIN);
    lv_obj_set_style_border_color(selected_border, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_size(selected_border, 55, 55);
    lv_obj_center(selected_border);


    obj->left = R_label;
    obj->mid = D_label;
    obj->right = N_label;
    obj->selected = 1;
    obj->parent = base;

    return obj;
}


void cl_gear_roller_set_selected(cl_gear_roller_t * gear_roller, int i)
{
    if (i > 2 || i < 0){
        printf("not in range!\n");
        return;
    }
    int selected = gear_roller->selected;

    if (i == selected){
        printf("we are there!\n");
        return;
    }


    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, cl_gear_roller_move_cb);
    lv_anim_set_var(&a, gear_roller);
    lv_anim_set_time(&a, 1000);
    
    lv_obj_set_style_text_color(gear_roller->mid, lv_palette_main(LV_PALETTE_GREY), LV_PART_MAIN);
    lv_obj_set_style_text_font(gear_roller->mid, &lv_font_montserrat_34, LV_PART_MAIN);

    if ( (selected - i) % 3 == 1 ){
        lv_anim_set_values(&a, 0, 80);
        lv_anim_start(&a);
    }

    else{
        lv_anim_set_values(&a, 0, -80);
        lv_anim_start(&a);
    }
    
    gear_roller->selected = i;
}