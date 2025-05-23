#include <stdlib.h> // abs()

#include "raylib.h"
#include "../Include/aux_camera.h"

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
        } if (IsKeyDown(KEY_A)) {
                camera->position.x -= fly_x; camera->target.x -= fly_x;
                camera->position.z += fly_z; camera->target.z += fly_z;
        } if (IsKeyDown(KEY_D)) {
                camera->position.x += fly_x; camera->target.x += fly_x;
                camera->position.z -= fly_z; camera->target.z -= fly_z;
        }
        
        if (IsKeyDown(KEY_SPACE)) {
                camera->position.y += fly_y; camera->target.y += fly_y;
        } if (IsKeyDown(KEY_LEFT_SHIFT)) {
                camera->position.y -= fly_y; camera->target.y -= fly_y;
        }

        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                Vector2 mouse_deltas = GetMouseDelta();
                if (mouse_deltas.x > 0) {
                } if (mouse_deltas.x < 0) {
                }
        } else if (mouse_scrolling > 0) {
                // zoom in, slightly add or sub to bring camera within 2x2x2 of camera
        } else if (mouse_scrolling < 0) {
                // zoom out
        }

}
