#include <math.h> // atan2(), sqrt()
#include <stdbool.h>
#include <stdlib.h> // abs()
#include <stdio.h> // sprintf

#include "raylib.h"
#include "raymath.h"
#include "../Include/main.h" // weight, height
#include "../Include/camera.h"

extern const int weight;
extern const int height;

void control_camera(Camera *camera) {
        Vector3 *ppos = &(camera->position), *ttar = &(camera->target);
        Vector3 delta_cam = { 0, 0, 0 }, delta_tar = { 0, 0, 0 };

        // common calculations
        float diff_x = ppos->x - ttar->x, diff_z = ppos->z - ttar->z;
        float cam_radius = sqrt(pow(diff_x, 2) + pow(diff_z, 2));
        float cam_angle = atan2(diff_z, diff_x);
        float sin_change = cam_radius * sin(cam_angle);
        float cos_change = cam_radius * cos(cam_angle); 

        if (IsKeyDown(KEY_W)) {
                delta_cam.x -= diff_x; delta_cam.z -= diff_z;
                delta_tar.x -= diff_x; delta_tar.z -= diff_z;
        } if (IsKeyDown(KEY_S)) {
                delta_cam.x += diff_x; delta_cam.z += diff_z;
                delta_tar.x += diff_x; delta_tar.z += diff_z;
        } if (IsKeyDown(KEY_A)) {
                delta_cam.x -= sin_change; delta_cam.z += cos_change;
                delta_tar.x -= sin_change; delta_tar.z += cos_change;
        } if (IsKeyDown(KEY_D)) {
                delta_cam.x += sin_change; delta_cam.z -= cos_change;
                delta_tar.x += sin_change; delta_tar.z -= cos_change;
        }

        if (IsKeyDown(KEY_SPACE)) {
                ppos->y += 0.3;
                ttar->y += 0.3;
        } else if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                ppos->y -= 0.3;
                ttar->y -= 0.3;
        }
        
        Vector2 mouse_deltas = GetMouseDelta();
        float angle_change = 0.1;
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                // mouse velocity gets ignored in normalization
                ttar->y -= mouse_deltas.y / 30.0;

                // now, for the fated and fucking hated xz rotations
                // what the fuck is messing me up?
                // it's either the math, the implementation, or the library
                // without change, it just turns ttar x and z into cam's...
        }

        int reset_pos = 20, reset_tar = 0;
        if (IsKeyDown(KEY_Z)) {
                ppos->x = reset_pos; ttar->x = reset_tar;
                ppos->y = reset_pos; ttar->y = reset_tar;
                ppos->z = reset_pos; ttar->z = reset_tar;
        } else {
                Vector3 normalized_cam = Vector3Normalize(delta_cam);
                Vector3 normalized_tar = Vector3Normalize(delta_tar);
                float slow_down_rate = 0.4;
                ppos->x += normalized_cam.x * slow_down_rate;
                ppos->y += normalized_cam.y * slow_down_rate;
                ppos->z += normalized_cam.z * slow_down_rate;
                ttar->x += normalized_tar.x * slow_down_rate;
                ttar->y += normalized_tar.y * slow_down_rate;
                ttar->z += normalized_tar.z * slow_down_rate;
        }
}
