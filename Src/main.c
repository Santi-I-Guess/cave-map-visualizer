#include <stdbool.h>
#include <stdio.h> // printf(), tmpfile()
#include <unistd.h> // access()
#include <math.h> // atan2()

#include "raylib.h"
#include "../Include/main.h" // get_data_file()
#include "../Include/camera.h" // control_camera()
#include "../Include/nodes.h" // draw_checkpoints()
#include "../Include/sqlite3.h"

#define MAX_CHECKPOINTS 1024

const int width = 1280;
const int height = 800;

int main(int argc, char *argv[]) {
        FILE *data_file = get_data_file(argc, argv);
        if (!data_file)
                return 1;

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

        // shits and giggles
        Vector3 sphere = { 5, 3, 0 };

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
                        DrawCube((Vector3){0, 0, 0}, 100, 0, 100, DARKGREEN);
                        DrawGrid(100, 1.0f);
                        // draw_checkpoints(data_file);
                EndMode3D(); 
                DrawRectangleRec(exit_button, DARKGRAY); 
                draw_stats(&camera, &dtm); // keep last
                EndDrawing();
        }
        
        UnloadFont(dtm);
        CloseWindow();
        fclose(data_file);
        return 0;
}

FILE *get_data_file(int argc, char *argv[]) {
        FILE *data_file;

        if (argc > 2 || argc < 1) { // prevents -Wmaybe-uninitialized
                printf("\e[31mGiven wrong amount of arguments (>1)\n\e[0m");
                return NULL;
        }

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
        }
        return data_file;
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
