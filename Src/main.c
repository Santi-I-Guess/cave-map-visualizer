#include <stdbool.h>
#include <stdio.h> // printf(), tmpfile()
#include <math.h> // atan2()

#include "raylib.h"
#include "../Include/main.h" // get_data_file()
#include "../Include/camera.h" // control_camera()
#include "../Include/nodes.h"
#include "../Include/sqlite3.h" 

const int width = 1280;
const int height = 800;

int main(int argc, char **argv) { 
        sqlite3 *db = database_open(argc, argv);

        // check if no file or database
        const char title[80] = "Cave Mapping Visualizer";
        InitWindow(width, height, title);
        Font dtm = LoadFont("/usr/share/fonts/JetBrains/JetBrainsMonoNerdFont-Medium.ttf");
        Camera3D camera = {
                .position = (Vector3){ 10.0f, 10.0f, 10.0f },
                .target   = (Vector3){ 0.0f, 0.0f, 0.0f },
                .up       = (Vector3){ 0.0f, 1.0f, 0.0f },
                .fovy = 45.0f,
                .projection = CAMERA_PERSPECTIVE
        };

        // same as GREEN, but half transparent
        Color SEMIGREEN = { 0, 228, 48, 128 };

        bool exit_window_requested = false;
        Rectangle exit_button = { 10, 10, 30, 30 };
        SetExitKey(KEY_NULL);
        SetTargetFPS(60);
        UpdateCamera(&camera, CAMERA_CUSTOM);
        while (!exit_window_requested) {
                exit_window_requested = WindowShouldClose() || 
                        (CheckCollisionPointRec(GetMousePosition(), exit_button)
                        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
                if (exit_window_requested)
                        break;

                BeginDrawing(); 
                ClearBackground(LIGHTGRAY);
                control_camera(&camera);
                BeginMode3D(camera);
                        DrawCube((Vector3){0, 0, 0}, 100, 0, 100, SEMIGREEN);
                        DrawGrid(100, 1.0f);
                EndMode3D(); 
                DrawRectangleRec(exit_button, DARKGRAY); 
                draw_stats(&camera, &dtm); // keep last
                EndDrawing();
        }
        
        UnloadFont(dtm);
        CloseWindow();
        sqlite3_close(db);
        return 0;
}

void draw_stats(Camera *camera, Font *le_font) {
        // ttar and ppos just to stay within 80 chars as possible
        Vector3 *ppos = &(camera->position), *ttar = &(camera->target);
        float diff_x = camera->position.x - camera->target.x;
        float diff_z = camera->position.z - camera->target.z;

        char cam_buffer[80], tar_buffer[80], ang_buffer[80];
        sprintf(cam_buffer, "camera: %.01f, %.01f, %.01f", ppos->x, ppos->y, ppos->z);
        sprintf(tar_buffer, "target: %.01f, %.01f, %.01f", ttar->x, ttar->y, ttar->z);
        sprintf(ang_buffer, "angle: %.3f", atan2(diff_z, diff_x));
        DrawTextEx(*le_font, cam_buffer, (Vector2){width-270, 10}, 18.0, 1.0, BLACK);
        DrawTextEx(*le_font, tar_buffer, (Vector2){width-270, 25}, 18.0, 1.0, BLACK);
        DrawTextEx(*le_font, ang_buffer, (Vector2){width-270, 40}, 18.0, 1.0, BLACK);
}
