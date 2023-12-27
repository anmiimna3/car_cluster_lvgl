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

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_WIDGETS_H*/
