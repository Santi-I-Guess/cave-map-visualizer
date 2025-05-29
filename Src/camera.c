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

        float diff_x = ppos->x - ttar->x, diff_z = ppos->z - ttar->z;
        float cam_radius = sqrt(pow(diff_x, 2) + pow(diff_z, 2));
        float cam_angle = atan2(diff_z, diff_x);

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {
                float change = (IsKeyDown(KEY_W)) ? -1 : 1;
                delta_cam.x += diff_x * change;
                delta_cam.z += diff_x * change;
                delta_tar.x += diff_z * change;
                delta_tar.z += diff_z * change;
        } if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {
                float x_sign = (IsKeyDown(KEY_A)) ? -1.0 : 1.0;
                float z_sign = (IsKeyDown(KEY_A)) ? 1.0 : -1.0;
                float sin_change = cam_radius * sin(cam_angle);
                float cos_change = cam_radius * cos(cam_angle); 
                delta_cam.x += sin_change * x_sign;
                delta_cam.z += cos_change * z_sign;
                delta_tar.x += sin_change * x_sign;
                delta_tar.z += cos_change * z_sign;
        }

        if (IsKeyDown(KEY_SPACE)) {
                delta_cam.y += 0.1;
                delta_tar.y += 0.1;
        } else if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                delta_cam.y -= 0.1;
                delta_tar.y -= 0.1;
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
