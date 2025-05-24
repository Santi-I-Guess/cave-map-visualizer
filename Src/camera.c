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
        // need to apply some x and z to both position and target
        float diff_x = camera->position.x - camera->target.x;
        float diff_z = camera->position.z - camera->target.z;
        float diff_y = camera->position.y - camera->target.y;
        float fly_x = diff_x * 0.02f;
        float fly_z = diff_z * 0.02f;
        float fly_y = 0.2f;
        Vector2 mouse_deltas = GetMouseDelta(); 
        float mouse_scrolling = GetMouseWheelMove();
        float cam_radius = sqrt(diff_x*diff_x + diff_z*diff_z);
        float cam_angle = atan2(diff_z, diff_x);
        float change = 0.1f;

        int reset_pos = 10, reset_tar = 0;
        if (IsKeyDown(KEY_Z)) {
                camera->position.x = reset_pos; camera->target.x = reset_tar;
                camera->position.y = reset_pos; camera->target.y = reset_tar;
                camera->position.z = reset_pos; camera->target.z = reset_tar;
        }
        
        // generic move
        if (IsKeyDown(KEY_W)) {
                camera->position.x -= fly_x; camera->target.x -= fly_x;
                camera->position.z -= fly_z; camera->target.z -= fly_z;
        } if (IsKeyDown(KEY_S)) {
                camera->position.x += fly_x; camera->target.x += fly_x;
                camera->position.z += fly_z; camera->target.z += fly_z;
        } if (IsKeyDown(KEY_A)) {
                // note to self, currently only works on one axis
                // breaks if rotation occurs
                camera->position.x -= fly_x; camera->target.x -= fly_x;
                camera->position.z += fly_z; camera->target.z += fly_z;
        } if (IsKeyDown(KEY_D)) {
                camera->position.x += fly_x; camera->target.x += fly_x;
                camera->position.z -= fly_z; camera->target.z -= fly_z;
        }
        
        if (IsKeyDown(KEY_SPACE)) {
                camera->position.y += fly_y; camera->target.y += fly_y;
        } else if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                camera->position.y -= fly_y; camera->target.y -= fly_y;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                camera->target.y -= (mouse_deltas.y / 30);

                if (mouse_deltas.x > 0.5) {
                } else if (mouse_deltas.x < -0.5) {
                }
        } if (mouse_scrolling > 0) {
                // within 2x2x2
        } if (mouse_scrolling < 0) {
        }

}
