#include <stdlib.h> // abs()
#include <math.h>

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

        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                double curr_theta = (camera->target.z - camera->position.z)
                        / (camera->target.x - camera->position.x);
                double curr_radius = sqrt(
                        pow(camera->target.z - camera->position.z, 2) +
                        pow(camera->target.x - camera->position.x, 2)
                );
                
                // rectangular -> polar -> rectangular
                // wow, this is very fucked rn
                Vector2 mouse_deltas = GetMouseDelta();
                float change = 0.1;
                if (mouse_deltas.x > 0) {
                        camera->target.z = curr_radius * sin(curr_theta + change) + camera->target.z;
                        camera->target.x = curr_radius * cos(curr_theta + change) + camera->target.x;
                } if (mouse_deltas.x < 0) {
                        camera->target.z = curr_radius * sin(curr_theta - change) + camera->target.z;
                        camera->target.x = curr_radius * cos(curr_theta - change) + camera->target.x;
                }
        } else if (mouse_scrolling > 0) {
                // zoom in, slightly add or sub to bring camera within 2x2x2 of camera
        } else if (mouse_scrolling < 0) {
                // zoom out
        }

}
