#include <math.h> // atan2(), sqrt()
#include <stdlib.h> // abs()
#include <stdio.h> // sprintf

#include "raylib.h"
#include "../Include/main.h" // weight, height
#include "../Include/camera.h"

extern const int weight;
extern const int height;

// https://www.desmos.com/calculator/lcv3rxceql

void control_camera(Camera *camera) {
        Vector3 *ppos = &(camera->position), *ttar = &(camera->target);

        // need to apply some x and z to both position and target
        float diff_x = ppos->x - ttar->x;
        float diff_z = ppos->z - ttar->z;
        float diff_y = ppos->y - ttar->y;
        float fly_x = diff_x * 0.02f;
        float fly_z = diff_z * 0.02f;
        float fly_y = 0.2f;
        

        int reset_pos = 10, reset_tar = 0;
        if (IsKeyDown(KEY_Z)) {
                ppos->x = reset_pos; ttar->x = reset_tar;
                ppos->y = reset_pos; ttar->y = reset_tar;
                ppos->z = reset_pos; ttar->z = reset_tar;
        }
        
        // generic move
        if (IsKeyDown(KEY_W)) {
                ppos->x -= fly_x; ttar->x -= fly_x;
                ppos->z -= fly_z; ttar->z -= fly_z;
        } if (IsKeyDown(KEY_S)) {
                ppos->x += fly_x; ttar->x += fly_x;
                ppos->z += fly_z; ttar->z += fly_z;
        } if (IsKeyDown(KEY_A)) {
                // note to self, currently only works on one axis
                // breaks if rotation occurs
                ppos->x -= fly_x; ttar->x -= fly_x;
                ppos->z += fly_z; ttar->z += fly_z;
        } if (IsKeyDown(KEY_D)) {
                ppos->x += fly_x; ttar->x += fly_x;
                ppos->z -= fly_z; ttar->z -= fly_z;
        }
        
        if (IsKeyDown(KEY_SPACE)) {
                ppos->y += fly_y; ttar->y += fly_y;
        } else if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                ppos->y -= fly_y; ttar->y -= fly_y;
        }

        Vector2 mouse_deltas = GetMouseDelta(); 
        float mouse_scrolling = GetMouseWheelMove();
        float cam_radius = sqrt(diff_x*diff_x + diff_z*diff_z);
        float cam_angle = atan2(diff_z, diff_x);
        float change = 0.016;
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                ttar->y -= (mouse_deltas.y / 30);
                
                /*
                if (mouse_deltas.x > 0.5) {
                        ttar->x = cam_radius * cos(cam_angle + change) + ppos->x;
                        ttar->z = cam_radius * sin(cam_angle + change) + ppos->z;
                } else if (mouse_deltas.x < -0.5) {
                        ttar->x = cam_radius * cos(cam_angle - change) + ppos->x;
                        ttar->z = cam_radius * sin(cam_angle - change) + ppos->z;
                }
                seriously, why does this freak out? */

        } if (mouse_scrolling > 0) {
                // within 2x2x2
        } if (mouse_scrolling < 0) {
        }

}
