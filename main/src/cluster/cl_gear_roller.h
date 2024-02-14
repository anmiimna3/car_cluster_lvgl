/**
 * @file cl_gear_roller.h
 *
 */

#ifndef CL_GEAR_ROLLER_H
#define CL_GEAR_ROLLER_H


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <stdlib.h>
// #include "../lv_conf_internal.h"
#include "lvgl/src/core/lv_obj.h"
#include "lvgl/src/widgets/lv_label.h"


/**********************
 *      TYPEDEFS
 **********************/

typedef struct{
    lv_obj_t * parent;
    lv_obj_t * left;
    lv_obj_t * mid;
    lv_obj_t * right;
    int selected;

} cl_gear_roller_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************
 */

cl_gear_roller_t * cl_gear_roller_create(lv_obj_t *, lv_coord_t, lv_coord_t);
void cl_gear_roller_set_selected(cl_gear_roller_t *, int);

#endif