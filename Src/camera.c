#include <math.h> // atan2(), sqrt()
#include <stdlib.h> // abs()
#include <stdio.h> // sprintf

#include "raylib.h"
#include "../Include/camera.h"

// https://www.desmos.com/calculator/rku5gn10np

void control_camera(Camera *camera) {

        // need to apply some x and z to both position and target
        float delta_x = camera->position.x - camera->target.x;
        float delta_y = camera->position.y - camera->target.y;
        float delta_z = camera->position.z - camera->target.z;
        float fly_x = delta_x * 0.02, fly_y = 0.2, fly_z = delta_z * 0.02;
        float mouse_scrolling = GetMouseWheelMove();
        
        
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
        } 

        // note to self, currently only works on one axis
        // breaks if rotation occurs
        if (IsKeyDown(KEY_A)) {
                camera->position.x -= fly_x; camera->target.x -= fly_x;
                camera->position.z += fly_z; camera->target.z += fly_z;
        } if (IsKeyDown(KEY_D)) {
                camera->position.x += fly_x; camera->target.x += fly_x;
                camera->position.z -= fly_z; camera->target.z -= fly_z;
        }
        
        if (IsKeyDown(KEY_SPACE)) {
                camera->position.y += fly_y; camera->target.y += fly_y;
        } if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                camera->position.y -= fly_y; camera->target.y -= fly_y;
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                float angle = atan2(
                        camera->position.z - camera->target.z,
                        camera->position.x - camera->target.x
                );
                char angle_buffer[80];
                sprintf(angle_buffer, "angle: %.01f", angle);
                DrawText(angle_buffer, 1280-200, 40, 17.0, BLACK);

                float radius = sqrt(
                        pow(camera->target.z - camera->position.z, 2) +
                        pow(camera->target.x - camera->position.x, 2)
                );

                Vector2 mouse_deltas = GetMouseDelta();
                float change_xz = 0.03;
                float change_y = 0.5;
                printf("\e[35mx:%.01f y:%.01f\n\e[0m", mouse_deltas.x, mouse_deltas.y);
                if (mouse_deltas.x > 2) {
                        camera->target.x = radius * cos(angle + change_xz) + camera->position.x;
                        camera->target.z = radius * sin(angle + change_xz) + camera->position.z;
                } if (mouse_deltas.x < -2) {
                        camera->target.x = radius * cos(angle - change_xz) + camera->position.x;
                        camera->target.z = radius * sin(angle - change_xz) + camera->position.z;
                } if (mouse_deltas.y > 1) {
                        camera->target.y -= change_y;
                } if (mouse_deltas.y < -1) {
                        camera->target.y += change_y;
                }
        } if (mouse_scrolling > 0) {
                // zoom in, slightly add or sub to bring camera within 2x2x2 of camera
        } if (mouse_scrolling < 0) {
                // zoom out
        }

}
