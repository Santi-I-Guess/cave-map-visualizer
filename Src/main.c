#include <stdbool.h>
#include <stdio.h> // printf(), tmpfile()
#include <unistd.h> // access()

#include "raylib.h"
#include "../Include/main.h" // get_data_file()
#include "../Include/camera.h" // control_camera()
#include "../Include/nodes.h" // draw_checkpoints()

#define MAX_CHECKPOINTS 1024
#define DEBUG

// don't think this is best practice

int main(int argc, char *argv[]) {
        FILE *data_file = get_data_file(argc, argv);
        if (!data_file)
                return 1;

        const int width = 1280;
        const int height = 800;
        const char title[80] = "Cave Mapping Visualizer";
        Font dtm = LoadFont("/usr/share/fonts/EnvyCodeR/EnvyCodeRNerdFont-Regular.ttf");

        InitWindow(width, height, title);
        Color Background = LIGHTGRAY;
        
        Camera3D camera = {
                .position = (Vector3){ 10.0f, 10.0f, 10.0f },
                .target   = (Vector3){ 0.0f, 0.0f, 0.0f },
                .up       = (Vector3){ 0.0f, 1.0f, 0.0f },
                .fovy = 45.0f,
                .projection = CAMERA_PERSPECTIVE
        };

        bool exit_window_requested = false;
        Rectangle exit_button = { 10, 10, 50, 50 };
        SetExitKey(KEY_NULL);

        SetTargetFPS(60);
        UpdateCamera(&camera, CAMERA_CUSTOM);
        while (!exit_window_requested) {
                // exit logic
                if (WindowShouldClose() || 
                        (CheckCollisionPointRec(GetMousePosition(), exit_button)
                        && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
                ))
                        exit_window_requested = true;
                else
                        exit_window_requested = false;

                if (exit_window_requested)
                        break;

                // usual
                BeginDrawing(); 
                ClearBackground(Background);
                DrawRectangleRec(exit_button, DARKGRAY); 
                control_camera(&camera);
                BeginMode3D(camera);
                        DrawCube((Vector3){0, 0, 0}, 10, 0, 10, DARKGREEN);
                        DrawGrid(10, 1.0f);
                        draw_checkpoints(data_file);
                EndMode3D();
                
                // draw cam and target pos
                char cam_buffer[80], tar_buffer[80];
                sprintf(cam_buffer, "cam: %.01f, %.01f, %.01f",
                        camera.position.x, camera.position.y, camera.position.z
                );
                sprintf(tar_buffer, "tar: %.01f, %.01f, %.01f",
                        camera.target.x, camera.target.y, camera.target
                );
                DrawTextEx(dtm, cam_buffer, (Vector2){width-200, 10}, 17.0, 1.0, BLACK);
                DrawTextEx(dtm, tar_buffer, (Vector2){width-200, 25}, 17.0, 1.0, BLACK);
                EndDrawing();
        }
        
        UnloadFont(dtm);
        CloseWindow();
        fclose(data_file);
        return 0;
}

FILE *get_data_file(int argc, char *argv[]) {
        FILE *data_file;
        if (argc == 1) {
                printf("\e[35mStarting with raw file\n\e[0m");
                data_file = tmpfile();
                if (!data_file) {
                        printf("\e[31mFailed to make temp file\n\e[0m");
                        return NULL;
                }
        } else if (argc == 2) {
                if (access(argv[1], R_OK | W_OK) == -1) {
                        printf("\e[31mFile can't be accessed\n\3[0m");
                        return NULL;
                }
                data_file = fopen(argv[1], "r+");
                if (!data_file) {
                        printf("\e[31mFile couldn't be opened\n\e[0m");
                        return NULL;
                }
                printf("\e[35mWorking with %s\e[0m\n", argv[1]);
        } else {
                printf("\e[31Given wrong amount of arguments (>1)\n\e[0m");
                return NULL;
        }
        return data_file;
}
