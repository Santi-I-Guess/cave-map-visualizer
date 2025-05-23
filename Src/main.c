#include <stdbool.h>
#include <stdio.h> // printf(), tmpfile()
#include <unistd.h> // access()

#include "raylib.h"
#include "../Include/aux_camera.h" // control_camera()
#include "../Include/checkpoints.h"

#define MAX_CHECKPOINTS 1024

int main(int argc, char *argv[]) {

        FILE *data_file;
        if (argc == 1) {
                printf("\e[35mStarting without file\n\e[0m");
                data_file = tmpfile();
                if (!data_file) {
                        printf("\e[31mFailed to make temp file\n\e[0m");
                        return 1;
                }
        } else if (argc == 2) {
                if (access(argv[1], R_OK | W_OK) == -1) {
                        printf("\e[31mFile can't be accessed\n\3[0m");
                }
                data_file = fopen(argv[1], "r+");
                if (!data_file) {
                        printf("\e[31mFile couldn't be opened\n\e[0m");
                        return 1;
                }
                printf("\e[35mWorking with %s\e[0m\n", argv[1]);
        } else {
                printf("\e[31Given wrong amount of arguments (>1)\n\e[0m");
                return 1;
        }

        const int width = 1280, height = 800;
        const char title[80] = "Cave Mapping Visualizer";

        InitWindow(width, height, title);
        Color Background = LIGHTGRAY;
        
        Camera3D camera = {
                .position = (Vector3){ 10.0f, 10.0f, 10.0f },
                .target   = (Vector3){ 0.0f, 0.0f, 0.0f },
                .up       = (Vector3){ 0.0f, 1.0f, 0.0f },
                .fovy = 45.0f,
                .projection = CAMERA_PERSPECTIVE
        };
        
        SetTargetFPS(60);
        UpdateCamera(&camera, CAMERA_CUSTOM);
        while (!WindowShouldClose()) { BeginDrawing(); 
                ClearBackground(Background);
                BeginMode3D(camera);
                        DrawCube((Vector3){0, 0, 0}, 10, 0, 10, DARKGREEN);
                        // UpdateCamera(&camera, CAMERA_FREE);
                        control_camera(&camera);
                        draw_checkpoints(data_file);
                EndMode3D();
                EndDrawing();
        }
        
        CloseWindow();
        fclose(data_file);
        return 0;
}
