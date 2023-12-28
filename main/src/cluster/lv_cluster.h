/**
 * @file lv_cluster.h
 *
 */

#ifndef CLUSTER_H
#define CLUSTER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_cluster(void);
void lv_cluster_close(void);
static void cl_draw_background(void);
static lv_obj_t * cl_create_speed_circle(lv_obj_t*);
static lv_obj_t * cl_create_speed_arc(lv_obj_t *);
static lv_obj_t * cl_create_speed_label(lv_obj_t *);
static lv_obj_t * cl_create_power_circle(lv_obj_t *);
static lv_obj_t * cl_create_power_arc(lv_obj_t *);
static lv_obj_t * cl_create_power_label(lv_obj_t *);
static lv_obj_t * cl_create_middle_part(lv_obj_t *);
static lv_obj_t * cl_create_line(lv_obj_t *, lv_coord_t, lv_coord_t, lv_point_t[2]);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_WIDGETS_H*/
