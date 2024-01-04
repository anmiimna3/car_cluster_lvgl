/**
 * @file cl_gear_roller.h
 *
 */

#ifndef CL_GEAR_ROLLER_H
#define CL_GEAR_ROLLER_H


/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
// #include "../lv_conf_internal.h"
#include "lvgl/src/core/lv_obj.h"
#include "lvgl/src/widgets/lv_label.h"


/**********************
 *      TYPEDEFS
 **********************/

typedef struct{
    lv_obj_t * parent;
    lv_obj_t * R;
    lv_obj_t * D;
    lv_obj_t * N;
    int selected;

} cl_gear_roller_t;


/**********************
 * GLOBAL PROTOTYPES
 **********************
 */

cl_gear_roller_t * cl_gear_roller_create(lv_obj_t *, lv_coord_t, lv_coord_t);

#endif CL_GEAR_ROLLER_H